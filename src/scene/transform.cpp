#include <UneEtoile/scene/transform.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

glm::mat4 Transform::model() const
{
    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix =
        glm::rotate(rotationMatrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix =
        glm::rotate(rotationMatrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix =
        glm::rotate(rotationMatrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    auto position {glm::translate(m_position)};
    auto scale {glm::scale(m_scale)};
    return glm::translate(m_position) * rotationMatrix * glm::scale(m_scale);
}