#pragma once

#include <UneEtoile/imgui/widget/freeflycamerawidget.h>
#include <UneEtoile/scene/camera.h>

class FreeFlyCamera : public Camera
{
public:
    FreeFlyCamera();
    void handleMouseMove(int deltaX, int deltaY) override;
    Type type() override { return Type::FreeFly; }

private:
    friend FreeFlyCameraWidget;
    FreeFlyCameraWidget m_widget;
};
