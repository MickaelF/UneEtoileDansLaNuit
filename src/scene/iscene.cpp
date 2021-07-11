#include <UneEtoile/scene/iscene.h>

IScene::IScene(MainWindow* window) : m_window(window), m_widget(*this)
{
    m_root.setName("Root");
}
