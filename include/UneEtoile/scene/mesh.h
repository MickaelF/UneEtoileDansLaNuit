#pragma once

#include <UneEtoile/render/abstractshader.h>
#include <UneEtoile/scene/abstractshaderhandler.h>
#include <UneEtoile/scene/gameobject.h>

#include <vector>

class AbstractTexture;
class IRenderIDCard;

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoords;
};

class Mesh : public GameObject
{
public:
    explicit Mesh() = default;
    virtual ~Mesh();
    explicit Mesh(std::vector<Vertex> vertices,
                  std::vector<unsigned int> indices,
                  std::vector<AbstractTexture*> textures);
    Mesh(const Mesh& other);
    Mesh(Mesh&& other);
    Mesh& operator=(const Mesh& other);
    Mesh& operator=(Mesh& other);

    IRenderIDCard* renderCard() const override { return m_idCard; }

    const std::vector<Vertex>& vertices() const { return m_vertices; }
    const std::vector<unsigned int>& indices() const { return m_indices; }
    const std::vector<AbstractTexture*>& textures() const { return m_textures; }

    void setIsStatic(bool state);
    bool isStatic() const { return m_isStatic; }

    void addShader(AbstractShaderHandler* shader);
    const std::vector<AbstractShaderHandler*>& shaders() const
    {
        return m_shaderHandlers;
    }

protected:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<AbstractTexture*> m_textures;
    void setup();

private:
    void clear();

    IRenderIDCard* m_idCard {nullptr};
    std::vector<AbstractShaderHandler*> m_shaderHandlers;
    bool m_isStatic {true};
};