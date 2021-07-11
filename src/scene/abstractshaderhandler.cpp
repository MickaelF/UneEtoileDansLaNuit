#include <UneEtoile/render/abstractshader.h>
#include <UneEtoile/scene/abstractshaderhandler.h>
#include <UneEtoile/scene/camera.h>

AbstractShaderHandler::AbstractShaderHandler(AbstractShader* shader)
    : m_shader(shader)
{
}

AbstractShaderHandler::~AbstractShaderHandler()
{
    delete m_shader;
}

void AbstractShaderHandler::setCamera(Camera* camera)
{
    if (m_usedCamera != camera) m_usedCamera = camera;
}

void AbstractShaderHandler::updateModelMatrix(const glm::mat4& mat)
{
    static int modelMatrixId = m_shader->retrieveUniformId("modelMatrix");
    m_shader->updateUniformMat4f(modelMatrixId, mat);
}

void AbstractShaderHandler::updateUniforms()
{
    static int viewMatrixId = m_shader->retrieveUniformId("viewMatrix");
    static int projectionMatrixId =
        m_shader->retrieveUniformId("projectionMatrix");
    if (m_usedCamera->hasViewChanged())
    {
        m_shader->updateUniformMat4f(viewMatrixId, m_usedCamera->viewMatrix());
        m_usedCamera->setHasViewChangedFalse();
    }
    if (m_usedCamera->hasProjectionChanged())
    {
        m_shader->updateUniformMat4f(projectionMatrixId,
                                     m_usedCamera->projectionMatrix());
        m_usedCamera->setHasProjectionChangedFalse();
    }
}

void AbstractShaderHandler::activate()
{
    m_shader->activate();
    AbstractShader::currentShader = m_shader;
    updateUniforms();
}