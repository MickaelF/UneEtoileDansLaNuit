#pragma once
#include <UneEtoile/render/abstractshader.h>

#include <optional>
#include <string_view>

class OpenGlShader : public AbstractShader
{
public:
    OpenGlShader(const char* name);
    virtual ~OpenGlShader();

    int id() const override;
    void activate() const override;

protected:
    std::optional<unsigned int> generateVertexShader();
    std::optional<unsigned int> generateFragmentShader();
    std::optional<unsigned int> generateProgram(unsigned int vertexId,
                                                unsigned int fragmentId);

private:
    bool generateShader(const std::string& name, unsigned id);
    bool checkShaderCompilation(unsigned int id);
    int m_id {-1};
};
