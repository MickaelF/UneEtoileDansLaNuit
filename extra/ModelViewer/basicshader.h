#pragma once
#include <UneEtoile/imgui/iimguiuserinterface.h>
#include <UneEtoile/render/opengl/openglshader.h>

#include <glm/vec4.hpp>

class BasicShader;

class BasicShaderWidget : public IImGuiUserInterface
{
public:
    BasicShaderWidget(BasicShader* ptr);
    virtual ~BasicShaderWidget();

    void render() override;

private:
    BasicShader* m_shader;
};

class BasicShader : public OpenGlShader
{
public:
    BasicShader();
    virtual ~BasicShader();

private:
    glm::vec4 m_color {};
    friend class BasicShaderWidget;
    BasicShaderWidget m_widget;
};
