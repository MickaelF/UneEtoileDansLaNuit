#pragma once
#include <glm/mat4x4.hpp>

class AbstractShader;
class Camera;

class AbstractShaderHandler
{
public:
    explicit AbstractShaderHandler(AbstractShader* shader);
    virtual ~AbstractShaderHandler();

    void activate();
    void setCamera(Camera* camera);
    void updateModelMatrix(const glm::mat4& mat);

    virtual void imguiRender() = 0;

protected:
    virtual void updateUniforms();
    AbstractShader* m_shader {nullptr};

private:
    Camera* m_usedCamera {nullptr};
};