#include <UneEtoile/imgui/iimguiuserinterface.h>

#include <UneEtoile/imgui/imguihandler.h>

IImGuiUserInterface::IImGuiUserInterface(const char* name) : name(name)
{
    ImGuiHandler::instance().addUI(this);
}

IImGuiUserInterface::~IImGuiUserInterface()
{
    ImGuiHandler::instance().removeUI(this);
}
