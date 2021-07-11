#pragma once
#include <UneEtoile/scene/abstractshaderhandler.h>

#include <glm/vec4.hpp>

class BasicShader : public AbstractShaderHandler
{
public:
    BasicShader();
    virtual ~BasicShader();
    void imguiRender() override;

protected:
    void updateUniforms() override;

private:
    glm::vec4 m_color {1.0f, 1.0f, 1.0f, 1.0f};
    bool m_colorChanged {true};
};
