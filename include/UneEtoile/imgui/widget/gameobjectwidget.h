#pragma once

#include <UneEtoile/imgui/iimguiuserinterface.h>

class GameObject;

class GameObjectWidget : public IImGuiUserInterface
{
public:
    void render() override;
    static void changeGameObject(GameObject* obj);

private:
    static GameObjectWidget* m_widget;
    explicit GameObjectWidget(GameObject* obj);
    GameObject* m_obj;
};