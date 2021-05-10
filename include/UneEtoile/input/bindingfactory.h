#pragma once
#include <UneEtoile/input/inputtype.h>

#include <map>

class Binding;

class BindingFactory
{
public:
    static int createBinaryBinding(InputType type, int key,
                                   const char* name = nullptr);
    static int createRangeBinding(InputType type, int minimumKey,
                                  int maximumKey, bool isFullRange = true,
                                  const char* name = nullptr);
    static int createRangeBinding(InputType type, int rangeKey,
                                  bool isFullRange = true,
                                  const char* name = nullptr);
    static int createVector2Binding(InputType type, int minValXKey,
                                    int maxValXKey, int minValYKey,
                                    int maxValYKey, const char* name = nullptr);
    static int createVector2Binding(InputType type, int xValKey, int yValKey,
                                    const char* name = nullptr);

    static void updateBindings(const std::vector<Input>& inputs);

private:
    class TypeKeyBinding
    {
    public:
        TypeKeyBinding() = default;

        void addKeyBinding(InputType type, int key, int bindingId);

        void removeKeyBinding(InputType type, int key, int bindingId);

        std::vector<int> bindingIds(InputType type, int key);

    private:
        class KeyBinding
        {
        public:
            KeyBinding(int key) : m_key {key} {}

            void addBinding(int bind) { m_bindings.push_back(bind); }
            void removeBinding(int bind)
            {
                m_bindings.erase(
                    std::find(m_bindings.begin(), m_bindings.end(), bind));
            }
            bool isEmpty() const { return m_bindings.empty(); }
            int key() const { return m_key; }
            const std::vector<int>& bindings() const { return m_bindings; }

        private:
            int m_key;
            std::vector<int> m_bindings;
        };

        std::vector<KeyBinding>& keyBinding(InputType type);
        std::vector<KeyBinding> m_mouseWheel;
        std::vector<KeyBinding> m_mouseButton;
        std::vector<KeyBinding> m_keyboard;
        std::vector<KeyBinding> m_gamepadButton;
        std::vector<KeyBinding> m_gamepadAxis;
    };

    static std::vector<Binding*> bindingsFromIds(const std::vector<int>& ids);
    static TypeKeyBinding m_indexes;

    static std::vector<Binding*> m_bindings;
};
