#pragma once
#include <string_view>

class ShaderUtil
{
public:
    static unsigned int generateVertexShader(std::string_view name);
    static unsigned int generateFragmentShader(std::string_view name);

private:
    static bool checkShaderCompilation(unsigned int id);
};