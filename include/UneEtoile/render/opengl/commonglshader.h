#pragma once
#include <UneEtoile/render/renderermacros.h>
#if defined(OPENGL_FOUND) || defined(OPENGLES2_FOUND)
    #include <UneEtoile/render/abstractshader.h>

    #include <optional>
    #include <string_view>

class CommonGLShader : public AbstractShader
{
public:
    CommonGLShader(const char *name, std::string_view vertex,
                   std::string_view fragment);
    virtual ~CommonGLShader();

    int id() const override;
    void activate() const override;
    int retrieveUniformId(std::string_view name) const override;
    void updateUniform1f(int id, float val) override;
    void updateUniform2f(int id, const glm::vec2 &val) override;
    void updateUniform3f(int id, const glm::vec3 &val) override;
    void updateUniform4f(int id, const glm::vec4 &val) override;
    void updateUniformMat4f(int id, const glm::mat4 &val) override;

protected:
    std::optional<unsigned int> generateVertexShader(std::string_view vertex);
    std::optional<unsigned int> generateFragmentShader(std::string_view frag);
    std::optional<unsigned int> generateProgram(unsigned int vertexId,
                                                unsigned int fragmentId);
    virtual void updateUniforms() const {}

private:
    bool generateShader(std::string shader, unsigned int id);
    bool checkShaderCompilation(unsigned int id);
    unsigned int m_id {0};

    int m_modelMatrixUniformId {0};
    int m_viewMatrixUniformId {0};
    int m_projectionMatrixUniformId {0};
};
#endif