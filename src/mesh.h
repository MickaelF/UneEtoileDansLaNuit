#pragma once

#include "gameobject.h"

class Texture;

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
    explicit Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
                  std::vector<Texture*> textures);
    Mesh(const Mesh& other);
    Mesh(Mesh&& other);
    Mesh& operator=(const Mesh& other);
    Mesh& operator=(Mesh& other);

private:
    void clear();
    void setup();
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Texture*> m_textures;
};