#include <UneEtoile/render/opengl/openglshader.h>
#include <glad/glad.h>
#include <pttk/file/plaintextfile.h>
#include <pttk/log.h>

#include <stdexcept>

OpenGlShader::OpenGlShader(const char* name) : AbstractShader(name)
{
    auto vertexId = generateVertexShader();
    if (!vertexId.has_value())
        throw std::runtime_error(
            "Could not compile vertex shader for basicshader");
    auto fragId = generateFragmentShader();
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
}

OpenGlShader::~OpenGlShader()
{
    if (m_id != -1) glDeleteProgram(m_id);
}

int OpenGlShader::id() const
{
    return m_id;
}

void OpenGlShader::activate() const
{
    glUseProgram(m_id);
}

bool OpenGlShader::generateShader(const std::string& name, unsigned int id)
{
    constexpr const char* path {"/shaders/glsl/"};
    PlainTextFile reader;
    auto source = reader.wholeFile(std::filesystem::current_path().string() +
                                   path + name);
    if (!source.has_value())
    {
        lError << "Could not find shader file " << name;
        return false;
    }
    auto cText = source->c_str();
    glShaderSource(id, 1, &cText, nullptr);
    glCompileShader(id);

    return checkShaderCompilation(id);
}

std::optional<unsigned int> OpenGlShader::generateProgram(
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

std::optional<unsigned int> OpenGlShader::generateVertexShader()
{
    constexpr std::string_view vertexExtension {".vert"};
    unsigned int vertexId = glCreateShader(GL_VERTEX_SHADER);
    if (generateShader(std::string(name) + std::string(vertexExtension),
                       vertexId))
        return vertexId;
    else
        return std::nullopt;
}

std::optional<unsigned int> OpenGlShader::generateFragmentShader()
{
    constexpr std::string_view fragExtension {".frag"};
    unsigned int fragId = glCreateShader(GL_FRAGMENT_SHADER);
    if (generateShader(std::string(name) + std::string(fragExtension), fragId))
        return fragId;
    else
        return std::nullopt;
}

bool OpenGlShader::checkShaderCompilation(unsigned int id)
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
