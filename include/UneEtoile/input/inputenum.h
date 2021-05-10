#pragma once
#include <pttk/log.h>

#include <array>

enum class InputEnum
{
    None = 0,
    Keyboard = 0x1,
    Mouse = 0x2,
    Gamepad = 0x4,
    All = 0x7
};

inline InputEnum operator|(InputEnum lhs, InputEnum rhs)
{
    return static_cast<InputEnum>(

        static_cast<std::underlying_type<InputEnum>::type>(lhs) |
        static_cast<std::underlying_type<InputEnum>::type>(rhs));
}

inline InputEnum operator&(InputEnum lhs, InputEnum rhs)
{
    return static_cast<InputEnum>(
        static_cast<std::underlying_type<InputEnum>::type>(lhs) &
        static_cast<std::underlying_type<InputEnum>::type>(rhs));
}

struct InputData
{
public:
    InputEnum id {InputEnum::None};
    bool contains(int32_t id) const
    {
        return std::find(padIds.cbegin(), padIds.cend(), id) != padIds.cend();
    }

    void set(int32_t id)
    {
        auto it = std::find(padIds.begin(), padIds.end(), 0);
        if (it == padIds.end())
        {
            lWarning << "Trying to add a gamepad id in an array that is "
                        "already full.";
            return;
        }
        *it = id;
    }

    void clear()
    {
        id = InputEnum::None;
        padIds.fill(0);
    }

private:
    std::array<int32_t, 4> padIds {};
};