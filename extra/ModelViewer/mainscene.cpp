#include "mainscene.h"

#include <UneEtoile/window/mainwindow.h>
MainScene::MainScene(MainWindow* window) : IScene(window) {}

void MainScene::preRun() {}

IScene* MainScene::run()
{
    while (m_window->running())
    {
        m_window->inputHandling();
        m_window->render();
    }
    return nullptr;
}

void MainScene::postRun() {}
