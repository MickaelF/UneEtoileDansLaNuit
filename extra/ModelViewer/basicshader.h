#pragma once
#include <UneEtoile/imgui/iimguiuserinterface.h>

#include <glm/vec4.hpp>

class BasicShader;
class AbstractShader;

class BasicShaderWidget : public IImGuiUserInterface
{
public:
    BasicShaderWidget(BasicShader* ptr);
    virtual ~BasicShaderWidget();

    void render() override;

private:
    BasicShader* m_shader;
};

class BasicShader
{
public:
    BasicShader();
    virtual ~BasicShader();
    void activate();

protected:
    void updateUniforms() const;

private:
    glm::vec4 m_color {};
    int m_colorId {-1};

    AbstractShader* m_shader {nullptr};
    friend class BasicShaderWidget;
    BasicShaderWidget m_widget;
    bool m_imguiUpdate {false};
};
