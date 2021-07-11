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
    glm::mat4 projectionMatrix() const;

    void restorePosition(const glm::vec3& position, const glm::vec3& front,
                         const glm::vec3& up);

    void handleMouseMove(int deltaX, int deltaY);

    bool hasViewChanged() const { return m_viewChanged; }
    void setHasViewChangedFalse() { m_viewChanged = false; }
    bool hasProjectionChanged() const { return m_projectionChanged; }
    void setHasProjectionChangedFalse() { m_projectionChanged = false; }

protected:
    void renderCommunWidgetPart();

    glm::vec3 m_position {0.0f, 0.0f, -10.0f};
    glm::vec3 m_front {0.0f, 0.0f, 1.0f};
    glm::vec3 m_up {0.0f, 1.0f, 0.0f};
    float m_fov {90.0f};

    friend CameraWidget;
    CameraWidget m_widget;
    bool m_viewChanged {true};
    bool m_projectionChanged {true};
};