#include <UneEtoile/scene/gameobject.h>
#include <pttk/log.h>

#include <stdexcept>


GameObject::~GameObject()
{
    if (m_parent != nullptr) m_parent->removeChild(this);
}

void GameObject::setName(const std::string& name)
{
    if (!m_name.empty())
        lDebug << "Changing name of game object from " << m_name << " to "
               << name << ".";
    if (m_name != name) m_name = name;
}

void GameObject::setParent(GameObject* parent)
{
    if (m_parent == parent) return;
    lDebug << "Setting new parent for game object named " << m_name;
    if (m_parent) m_parent->removeChild(this);
    m_parent = parent;

    if (m_parent)
    {
        m_parent->addChild(this);
        m_depthLevel = m_parent->m_depthLevel + 1;
    }
    else
    {
        m_depthLevel = 0;
    }
}

void GameObject::addChild(GameObject* child)
{
    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it != m_children.end())
        throw std::runtime_error("Cannot add same child multiple times");
    m_children.push_back(child);
}

void GameObject::removeChild(GameObject* child)
{
    auto it = std::find(m_children.begin(), m_children.end(), nullptr);
    if (it == m_children.end()) throw std::runtime_error("Cannot find child");
    m_children.erase(it);
}