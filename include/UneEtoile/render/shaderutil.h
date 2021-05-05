#pragma once
#include <string_view>
#include <optional>

class ShaderUtil
{
public:
    static std::optional<unsigned int> generateVertexShader(std::string_view name);
    static std::optional<unsigned int> generateFragmentShader(std::string_view name);
    static std::optional<unsigned int> generateProgram(unsigned int vertexId, unsigned int fragmentId);
    static void deleteShader(int id);

private:
    static bool generateShader(const std::string& name, unsigned id);
    static bool checkShaderCompilation(unsigned int id);
};