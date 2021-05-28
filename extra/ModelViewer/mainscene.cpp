#include "mainscene.h"

#include <UneEtoile/window/mainwindow.h>
MainScene::MainScene(MainWindow* window) : IScene(window)
{
    m_triangle.setParent(&m_root);
}

void MainScene::preRun() {}

IScene* MainScene::run()
{
    while (m_window->running())
    {
        m_shader.activate();
        m_window->inputHandling();
        m_window->render(this);
    }
    return nullptr;
}

void MainScene::postRun() {}
