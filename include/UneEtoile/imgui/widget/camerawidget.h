#pragma once

#include <UneEtoile/imgui/iimguiuserinterface.h>

class Camera;

class CameraWidget : public IImGuiUserInterface
{
public:
    CameraWidget(Camera* obj);
    void render() override;

private:
    Camera* m_ptr;
};
