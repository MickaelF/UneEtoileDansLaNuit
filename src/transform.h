#pragma once 
#include <glm/glm.hpp>

class Transform
{
public:
    explicit Transform() {}
    glm::mat4 model() const; 
    const glm::vec3& position() const { return m_position; }
    const glm::vec3& rotation() const { return m_rotation; }
    const glm::vec3& scale() const { return m_scale; }
    
private:
    glm::vec3 m_position; 
    glm::vec3 m_rotation; 
    glm::vec3 m_scale; 
};