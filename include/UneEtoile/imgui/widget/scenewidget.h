#pragma once

#include <UneEtoile/imgui/iimguiuserinterface.h>

class IScene;
class GameObject;

class SceneWidget : public IImGuiUserInterface
{
public:
    explicit SceneWidget(IScene& scene)
        : IImGuiUserInterface("Scene"),
          m_scene(scene) {};
    void render() override;

private:
    void treeNode(GameObject* go);
    IScene& m_scene;
    GameObject* m_selectedObj {nullptr};
};