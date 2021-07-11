#pragma once

#include <UneEtoile/scene/iscene.h>
#include <UneEtoile/scene/camera.h>

#include "basicshader.h"
#include "triangle.h"

class MainScene : public IScene
{
public:
    MainScene(MainWindow* window);
    void preRun() override;
    IScene* run() override;
    void postRun() override;

private:
    BasicShader m_shader;
    Triangle m_triangle;
    Camera m_camera;
};