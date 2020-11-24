#pragma once

struct ActionContext;

class IActionListener
{
public:
    IActionListener() = default;

    virtual void onAction(ActionContext ctx) = 0;
};