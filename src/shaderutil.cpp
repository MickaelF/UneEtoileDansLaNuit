#include "shaderutil.h"

#include <glad/glad.h>

#include "log.h"
#include "plaintextfile.h"


unsigned int ShaderUtil::generateVertexShader(std::string_view name)
{
    constexpr std::string_view vertexExtension {".vert"};
    PlainTextFile reader;
    unsigned int vertexId = glCreateShader(GL_VERTEX_SHADER);
    auto source = reader.wholeFile(name + vertexExtension);
    if (!source.has_value())
    {
        lError << "Could not find vertex shader " << name;
        return -1;
    }
    glShaderSource(vertexId, 1, source.value().c_str());
    glCompileShader(vertexId);

    if (checkShaderCompilation(vertexId))
        return vertexId;
    else
        return -1;
}

unsigned int ShaderUtil::generateFragmentShader(std::string_view name)
{
    constexpr std::string_view fragExtension {".vert"};
    PlainTextFile reader;
    unsigned int fragId = glCreateShader(GL_FRAGMENT_SHADER);
    auto source = reader.wholeFile(name + fragExtension);
    if (!source.has_value())
    {
        lError << "Could not find fragment shader " << name;
        return -1;
    }
    glShaderSource(fragId, 1, source.value().c_str());
    glCompileShader(fragId);

    if (checkShaderCompilation(fragId))
        return fragId;
    else
        return -1;
    return fragId;
}

bool ShaderUtil::checkShaderCompilation(unsigned int id)
{
    int success;
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
    if (success == 0)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        lError << "Error while compiling shader : " << infoLog;
    }
    return success != 0;
}