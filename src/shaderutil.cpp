#include "shaderutil.h"

#include <glad/glad.h>

#include <pttk/log.h>
#include <pttk/file/plaintextfile.h>

bool ShaderUtil::generateShader(const std::string& name, unsigned int id)
{
    PlainTextFile reader;
    auto source = reader.wholeFile(name);
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

std::optional<unsigned int> ShaderUtil::generateProgram(unsigned int vertexId, unsigned int fragmentId)
{
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexId);
    glAttachShader(shaderProgram, fragmentId);
    glLinkProgram(shaderProgram);
    int success; 
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        lError << "Error while creating program : " << infoLog;
        return std::nullopt;
    }
    return shaderProgram;
}

std::optional<unsigned int> ShaderUtil::generateVertexShader(std::string_view name)
{
    constexpr std::string_view vertexExtension {".vert"};
    unsigned int vertexId = glCreateShader(GL_VERTEX_SHADER);
    if (generateShader(std::string(name) + std::string(vertexExtension), vertexId))
        return vertexId;
    else
        return std::nullopt;
}

std::optional<unsigned int> ShaderUtil::generateFragmentShader(std::string_view name)
{
    constexpr std::string_view fragExtension {".vert"};
    unsigned int fragId = glCreateShader(GL_FRAGMENT_SHADER); 
    if (generateShader(std::string(name) + std::string(fragExtension), fragId))
        return fragId;
    else
        return std::nullopt;
}

bool ShaderUtil::checkShaderCompilation(unsigned int id)
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

void ShaderUtil::deleteShader(int id)
{
    glDeleteShader(id);
}