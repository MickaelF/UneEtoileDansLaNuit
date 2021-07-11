#include <UneEtoile/imgui/widget/controlschemewidget.h>
#include <UneEtoile/input/abstractactionmap.h>
#include <UneEtoile/input/abstractcontrolscheme.h>
#include <UneEtoile/input/inputhandler.h>

#include "imgui.h"


ControlSchemeWidget::ControlSchemeWidget()
    : IImGuiUserInterface("Control schemes")
{
}

void ControlSchemeWidget::render()
{
    auto& inputHandler = InputHandler::instance();
    // if (ImGui::Begin(name))
    // {
    //     if (ImGui::TreeNode("Control Schemes"))
    //     {
    //         for (auto* scheme : inputHandler.m_controlScheme)
    //         {
    //             if (ImGui::TreeNode(scheme->name))
    //             {
    //                 if (ImGui::TreeNode("Action maps"))
    //                 {
    //                     // for (auto* actionMap : scheme->actionsMaps())
    //                     // {
    //                     //     if (ImGui::TreeNode(actionMap->name))
    //                     //     {
    //                     //         ImGui::Text("Hello");
    //                     //         ImGui::TreePop();
    //                     //     }
    //                     // }

    //                     ImGui::TreePop();
    //                 }
    //                 ImGui::TreePop();
    //             }
    //         }
    //         ImGui::TreePop();
    //     }
    // }
    // ImGui::End();
}