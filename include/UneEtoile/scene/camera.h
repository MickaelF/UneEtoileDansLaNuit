#pragma once

#include <UneEtoile/imgui/widget/camerawidget.h>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Camera
{
public:
    Camera();
    glm::mat4 viewMatrix() const;

    void restorePosition(const glm::vec3& position, const glm::vec3& front,
                         const glm::vec3& up);

    void handleMouseMove(int deltaX, int deltaY);

protected:
    void renderCommunWidgetPart();

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;

    friend CameraWidget;
    CameraWidget m_widget;
};