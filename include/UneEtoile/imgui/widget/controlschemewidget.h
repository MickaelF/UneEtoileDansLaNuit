#pragma once

#include <UneEtoile/imgui/iimguiuserinterface.h>

class ControlSchemeWidget : public IImGuiUserInterface
{
public:
    ControlSchemeWidget();
    void render() override;

private:
};
