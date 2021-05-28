#include "triangle.h"

Triangle::Triangle() : Mesh()
{
    m_vertices.push_back(Vertex {{0.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {}});
    m_vertices.push_back(Vertex {{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {}});
    m_vertices.push_back(Vertex {{-1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {}});
    m_indices = {0, 1, 2};
    setup();
}

Triangle::~Triangle() {}