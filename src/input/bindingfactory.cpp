#include <UneEtoile/input/binding.h>
#include <UneEtoile/input/bindingfactory.h>

std::vector<BindingFactory::TypeKeyBinding::KeyBinding>&
BindingFactory::TypeKeyBinding::keyBinding(InputType type)
{
    switch (type)
    {
        case InputType::MouseWheel: return m_mouseWheel;
        case InputType::MouseButton: return m_mouseButton;
        case InputType::GamepadAxis: return m_gamepadAxis;
        case InputType::GamepadButton: return m_gamepadButton;
        case InputType::Keyboard: return m_keyboard;
        default: throw std::runtime_error("Binding not existing");
    }
}

void BindingFactory::TypeKeyBinding::addKeyBinding(InputType type, int key,
                                                   int bindingId)
{
    auto& kb {keyBinding(type)};
    auto it = std::find_if(kb.begin(), kb.end(),
                           [key](auto& kb) { return key == kb.key(); });
    if (it == kb.end())
    {
        kb.push_back({key});
        it = kb.end() - 1;
    }
    it->addBinding(bindingId);
}

void BindingFactory::TypeKeyBinding::removeKeyBinding(InputType type, int key,
                                                      int bindingId)
{
    auto& kb {keyBinding(type)};
    auto it = std::find_if(kb.begin(), kb.end(),
                           [key](auto& kb) { return key == kb.key(); });
    if (it == kb.end()) return;
    it->removeBinding(bindingId);
    if (it->isEmpty()) kb.erase(it);
}

std::vector<int> BindingFactory::TypeKeyBinding::bindingIds(InputType type,
                                                            int key)
{
    const auto& kb {keyBinding(type)};
    auto it = std::find_if(kb.begin(), kb.end(),

                           [key](auto& kb) { return key == kb.key(); });

    if (it == kb.end()) return {};
    return it->bindings();
}

int BindingFactory::createBinaryBinding(InputType type, int key,
                                        const char* name)
{
    BinaryBinding* binding = new BinaryBinding(type, key, name);
    m_bindings.push_back(binding);
    m_indexes.addKeyBinding(type, key, binding->id);
    return binding->id;
}

int BindingFactory::createRangeBinding(InputType type, int minimumKey,
                                       int maximumKey, bool isFullRange,
                                       const char* name)
{
    RangeBinding* binding =
        new RangeBinding(type, minimumKey, type, maximumKey, name);
    m_indexes.addKeyBinding(type, minimumKey, binding->id);
    m_indexes.addKeyBinding(type, maximumKey, binding->id);
    m_bindings.push_back(binding);
    return binding->id;
}

int BindingFactory::createRangeBinding(InputType type, int rangeKey,
                                       bool isFullRange, const char* name)
{
    RangeBinding* binding = new RangeBinding(type, rangeKey, name);
    m_bindings.push_back(binding);
    m_indexes.addKeyBinding(type, rangeKey, binding->id);
    return binding->id;
}

int BindingFactory::createVector2Binding(InputType type, int minValXKey,
                                         int maxValXKey, int minValYKey,
                                         int maxValYKey, const char* name)
{
    Vector2Binding* binding =
        new Vector2Binding(type, minValXKey, type, maxValXKey, type, minValYKey,
                           type, maxValYKey, name);
    m_bindings.push_back(binding);
    m_indexes.addKeyBinding(type, minValXKey, binding->id);
    m_indexes.addKeyBinding(type, maxValXKey, binding->id);
    m_indexes.addKeyBinding(type, minValYKey, binding->id);
    m_indexes.addKeyBinding(type, maxValYKey, binding->id);
    return binding->id;
}

int BindingFactory::createVector2Binding(InputType type, int xValKey,
                                         int yValKey, const char* name)
{
    Vector2Binding* binding =
        new Vector2Binding(type, xValKey, type, yValKey, name);
    m_bindings.push_back(binding);
    m_indexes.addKeyBinding(type, xValKey, binding->id);
    m_indexes.addKeyBinding(type, yValKey, binding->id);
    return binding->id;
}

std::vector<Binding*> BindingFactory::bindingsFromIds(
    const std::vector<int>& ids)
{
    std::vector<Binding*> out;
    out.reserve(ids.size());
    std::copy_if(m_bindings.begin(), m_bindings.end(), std::back_inserter(out),
                 [ids](const auto& b) {
                     return std::find(ids.cbegin(), ids.cend(), b->id) !=
                            ids.cend();
                 });
    return out;
}

void BindingFactory::updateBindings(const std::vector<Input>& inputs)
{
    for (auto& input : inputs)
    {
        for (auto& binding :
             bindingsFromIds(m_indexes.bindingIds(input.type, input.key)))
        {
            int32_t gamepadId = 0;
            InputEnum controllerType;
            int value {};
            switch (input.value.index())
            {
                case 0:
                    controllerType = InputEnum::Gamepad;
                    gamepadId = std::get<GamepadValue>(input.value).padId;
                    value = std::get<GamepadValue>(input.value).value;
                    break;
                case 1:
                    controllerType = InputEnum::Keyboard;
                    value = std::get<KeyboardValue>(input.value).value;
                    break;
                case 2:
                    controllerType = InputEnum::Mouse;
                    value = std::get<MouseValue>(input.value).value;
                    break;
                case 3: continue;
            }
            binding->addUsedController(controllerType, gamepadId);
            if (input.type == InputType::GamepadAxis)
                binding->setValue(input.type, input.key,
                                  static_cast<float>(value) /
                                      std::numeric_limits<int16_t>().max());
            else
                binding->setValue(input.type, input.key, value);
        }
    }
}