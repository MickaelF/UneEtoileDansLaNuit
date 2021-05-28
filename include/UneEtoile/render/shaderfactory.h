#pragma once

#include <string_view>

class AbstractShader;

class ShaderFactory
{
public:
    static AbstractShader* shader(std::string_view name);
    
private:
    static AbstractShader* glShader(std::string_view name);
    static AbstractShader* glesShader(std::string_view name);
};