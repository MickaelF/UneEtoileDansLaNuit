#pragma once
#include <UneEtoile/scene/transform.h>

#include <string>
#include <vector>

class IRenderIDCard;

class GameObject
{
public:
    explicit GameObject() = default;
    virtual ~GameObject();

    const std::string& name() const { return m_name; };
    void setName(const std::string& name);
    void setParent(GameObject* parent);

    Transform& transform() { return m_transform; }
    virtual IRenderIDCard* renderCard() const { return nullptr; }
    const std::vector<GameObject*>& children() const { return m_children; }

    glm::mat4 modelMatrix() const { return m_transform.model(); }

private:
    void addChild(GameObject* child);
    void removeChild(GameObject* child);

    Transform m_transform;
    GameObject* m_parent {nullptr};
    std::vector<GameObject*> m_children;
    std::string m_name;
    int m_depthLevel {0};
};