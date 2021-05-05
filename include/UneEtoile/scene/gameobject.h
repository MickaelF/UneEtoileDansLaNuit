#pragma once
#include <string>
#include <vector>

#include <UneEtoile/scene/transform.h>

class GameObject
{
public:
    explicit GameObject() = default;
    virtual ~GameObject();

    const std::string& name() const { return m_name; };
    void setName(const std::string& name);
    void setParent(GameObject* parent);

    Transform& transform() { return m_transform; }
    virtual bool isMesh() { return false; }

private:
    void addChild(GameObject* child);
    void removeChild(GameObject* child);

    Transform m_transform;
    GameObject* m_parent {nullptr};
    std::vector<GameObject*> m_children;
    std::string m_name;
    int m_depthLevel = 0;
};