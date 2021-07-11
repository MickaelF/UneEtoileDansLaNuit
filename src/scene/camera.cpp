#include <UneEtoile/scene/camera.h>

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : m_widget(this) {}

glm::mat4 Camera::viewMatrix() const
{
    return glm::lookAt(m_position, m_front, m_up);
}

glm::mat4 Camera::projectionMatrix() const
{
    return glm::perspectiveFov(glm::radians(m_fov), 1280.0f, 720.0f, 0.1f,
                               1000.0f);
}

void Camera::restorePosition(const glm::vec3& position, const glm::vec3& front,
                             const glm::vec3& up)
{
    if (m_position != position) m_position = position;
    if (m_front != front) m_front = front;
    if (m_up != up) m_up = up;
}
void Camera::handleMouseMove(int deltaX, int deltaY) {}
