#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string_view>

class AbstractShader
{
public:
    AbstractShader(const char *name);
    virtual ~AbstractShader();

    const char *name;
    virtual int id() const = 0;

    virtual void activate() const = 0;
    static AbstractShader *getShader(std::string_view name);

    virtual int retrieveUniformId(std::string_view name) const = 0;

    virtual void updateUniform1f(int id, float val) = 0;
    virtual void updateUniform2f(int id, const glm::vec2 &val) = 0;
    virtual void updateUniform3f(int id, const glm::vec3 &val) = 0;
    virtual void updateUniform4f(int id, const glm::vec4 &val) = 0;
    virtual void updateUniformMat4f(int id, const glm::mat4 &val) = 0;

    static AbstractShader* currentShader;
};