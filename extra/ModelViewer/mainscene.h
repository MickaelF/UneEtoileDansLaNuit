#pragma once

#include <UneEtoile/scene/iscene.h>

#include "basicshader.h"

class MainScene : public IScene
{
public:
    MainScene(MainWindow* window);
    void preRun() override;
    IScene* run() override;
    void postRun() override;

private:
    BasicShader m_shader;
};