#include <UneEtoile/scene/mesh.h>

#include <UneEtoile/render/abstractrenderer.h>
#include <UneEtoile/render/irenderidcard.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
           std::vector<Texture*> textures)
    : m_vertices(std::move(vertices)),
      m_indices(std::move(indices)),
      m_textures(std::move(textures))
{
    vertices.clear();
    indices.clear();
    textures.clear();
    setup();
}

Mesh::Mesh(const Mesh& other)
    : m_vertices(other.m_vertices),
      m_indices(other.m_indices),
      m_textures(other.m_textures)
{
    setup();
}

Mesh::Mesh(Mesh&& other)
    : m_vertices(std::move(other.m_vertices)),
      m_indices(std::move(other.m_indices)),
      m_textures(std::move(other.m_textures))
{
    other.clear();
    setup();
}

Mesh::~Mesh()
{
    if (m_idCard)
    {
        m_idCard->clear();
        delete m_idCard;
    }
}

Mesh& Mesh::operator=(const Mesh& other)
{
    m_vertices = other.m_vertices;
    m_indices = other.m_indices;
    m_textures = other.m_textures;
    setup();
    return *this;
}

Mesh& Mesh::operator=(Mesh& other)
{
    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);
    m_textures = std::move(other.m_textures);
    setup();
    other.clear();
    return *this;
}

void Mesh::setup()
{
    m_idCard = AbstractRenderer::instance()->load(*this);
}

void Mesh::clear()
{
    m_idCard->clear();
    delete m_idCard;
    m_idCard = nullptr;
}