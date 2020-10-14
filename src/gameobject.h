#pragma once
#include <vector>
#include <string>
#include "transform.h"

class GameObject 
{
public: 
    explicit GameObject() = default;
    ~GameObject();

    const std::string& name() const { return m_name; };
    void setName(const std::string& name);
    void setParent(GameObject * parent); 

    Transform& transform() { return m_transform; }

private:
    void addChild(GameObject* child); 
    void removeChild(GameObject* child);

    Transform m_transform;
    GameObject* m_parent {nullptr};
    std::vector<GameObject*> m_children;
    std::string m_name; 
    int m_depthLevel = 0;
};