#pragma once

class Action;

class IActionListener
{
public:
    IActionListener() = default;

    virtual void onAction(Action* action) = 0;
};