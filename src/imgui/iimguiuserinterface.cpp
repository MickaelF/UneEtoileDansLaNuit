#include "iimguiuserinterface.h"

#include "imguihandler.h"

IImGuiUserInterface::IImGuiUserInterface(const char* name) : name(name)
{
    ImGuiHandler::instance().addUI(this);
}

IImGuiUserInterface::~IImGuiUserInterface()
{
    ImGuiHandler::instance().removeUI(this);
}
