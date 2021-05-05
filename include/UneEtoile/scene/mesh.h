#pragma once

#include <UneEtoile/scene/gameobject.h>

class Texture;
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
                  std::vector<Texture*> textures);
    Mesh(const Mesh& other);
    Mesh(Mesh&& other);
    Mesh& operator=(const Mesh& other);
    Mesh& operator=(Mesh& other);
    bool isMesh() override { return true; }

    const std::vector<Vertex>& vertices() const { return m_vertices; }
    const std::vector<unsigned int>& indices() const { return m_indices; }
    const std::vector<Texture*>& textures() const { return m_textures; }

private:
    void clear();
    void setup();

    IRenderIDCard* m_idCard {nullptr};

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Texture*> m_textures;
};