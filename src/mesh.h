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
    explicit Mesh(); 


private: 
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices; 
    std::vector<Texture*> m_textures;  
};