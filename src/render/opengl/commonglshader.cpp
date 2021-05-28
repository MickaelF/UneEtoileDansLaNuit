#include <UneEtoile/render/opengl/commonglshader.h>
#include <UneEtoile/render/renderermacros.h>
#include <pttk/log.h>

#if defined(OPENGL_FOUND) || defined(OPENGLES2_FOUND)
    #include <glad/glad.h>

    #include <glm/gtc/type_ptr.hpp>
    #include <stdexcept>

CommonGLShader::CommonGLShader(const char *name, std::string_view vertex,
                               std::string_view fragment)
    : AbstractShader(name)
{
    auto vertexId = generateVertexShader(vertex);
    if (!vertexId.has_value())
        throw std::runtime_error(
            "Could not compile vertex shader for basicshader");
    auto fragId = generateFragmentShader(fragment);
    if (!fragId.has_value())
        throw std::runtime_error(
            "Could not compile fragment shader for basicshader");

    auto program = generateProgram(*vertexId, *fragId);
    glDeleteShader(*vertexId);
    glDeleteShader(*fragId);
    if (!program.has_value())
        throw std::runtime_error(
            "Could not create the program for shader basicshader");
    m_id = *program;
    m_modelMatrixUniformId = retrieveUniformId("modelMatrix");
    m_viewMatrixUniformId = retrieveUniformId("viewMatrix");
    m_projectionMatrixUniformId = retrieveUniformId("projectionMatrix");
}

CommonGLShader::~CommonGLShader()
{
    if (m_id != -1) glDeleteProgram(m_id);
}

int CommonGLShader::id() const
{
    return m_id;
}

void CommonGLShader::activate() const
{
    glUseProgram(m_id);
    updateUniforms();
}

bool CommonGLShader::generateShader(std::string shader, unsigned int id)
{
    const char *shaderSrc {shader.c_str()};
    glShaderSource(id, 1, &shaderSrc, nullptr);
    glCompileShader(id);

    return checkShaderCompilation(id);
}

std::optional<unsigned int> CommonGLShader::generateProgram(
    unsigned int vertexId, unsigned int fragmentId)
{
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexId);
    glAttachShader(shaderProgram, fragmentId);
    glLinkProgram(shaderProgram);
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        lError << "Error while creating program : " << infoLog;
        return std::nullopt;
    }
    return shaderProgram;
}

std::optional<unsigned int> CommonGLShader::generateVertexShader(
    std::string_view vertex)
{
    unsigned int vertexId = glCreateShader(GL_VERTEX_SHADER);
    if (generateShader(std::string(vertex), vertexId))
        return vertexId;
    else
        return std::nullopt;
}

std::optional<unsigned int> CommonGLShader::generateFragmentShader(
    std::string_view frag)
{
    unsigned int fragId = glCreateShader(GL_FRAGMENT_SHADER);
    if (generateShader(std::string(frag), fragId))
        return fragId;
    else
        return std::nullopt;
}

bool CommonGLShader::checkShaderCompilation(unsigned int id)
{
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == 0)
    {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        lError << "Error while compiling shader : " << infoLog;
    }
    return success != 0;
}

int CommonGLShader::retrieveUniformId(std::string_view name) const
{
    return glGetUniformLocation(m_id, name.data());
}

void CommonGLShader::updateUniform1f(int id, float val)
{
    glUseProgram(m_id);
    glUniform1f(id, val);
    glUseProgram(0);
}

void CommonGLShader::updateUniform2f(int id, const glm::vec2 &val)
{
    glUniform2f(id, val.x, val.y);
}

void CommonGLShader::updateUniform3f(int id, const glm::vec3 &val)
{
    glUniform3f(id, val.x, val.y, val.z);
}

void CommonGLShader::updateUniform4f(int id, const glm::vec4 &val)
{
    glUniform4f(id, val.x, val.y, val.z, val.w);
}

void CommonGLShader::updateUniformMat4f(int id, const glm::mat4 &val)
{
    glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(val));
}

#else
CommonGLShader::CommonGLShader(const char *name) : AbstractShader(name)
{
    lFatal << "OpenGL renderer is not included on this platform and cannot be "
              "used!";
}
CommonGLShader::~CommonGLShader() {}
int CommonGLShader::id() const
{
    return 0;
}
void CommonGLShader::activate() const {}

void updateUniform1f(int id, float val) {}
void updateUniform2f(int id, const glm::vec2 &val) {}
void updateUniform3f(int id, const glm::vec3 &val) {}
void updateUniform4f(int id, const glm::vec4 &val) {}
void updateUniformMat4f(int id, const glm::mat4 &val) {}

#endif