#include <UneEtoile/render/opengl/commonglidcard.h>
#include <UneEtoile/render/opengl/commonglmeshhandler.h>
#include <UneEtoile/render/renderermacros.h>
#include <UneEtoile/scene/mesh.h>
#if defined(OPENGL_FOUND) || defined(OPENGLES2_FOUND)
    #include "glad/glad.h"
    #include "imgui_impl_opengl3.h"
    #include "imgui_impl_sdl.h"

CommonGLMeshHandler::~CommonGLMeshHandler() {}

IRenderIDCard* CommonGLMeshHandler::load(Mesh& mesh)
{
    unsigned int vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    auto& vertices = mesh.vertices();

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 &vertices[0], GL_STATIC_DRAW);

    auto& indices = mesh.indices();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, texcoords));

    glBindVertexArray(0);
    return new CommonGLIDCard(vao, vbo, ebo, indices.size());
}

void CommonGLMeshHandler::unload(IRenderIDCard* card)
{
    CommonGLIDCard* oglCard = static_cast<CommonGLIDCard*>(card);
    glDeleteVertexArrays(1, &oglCard->vao);
    glDeleteBuffers(1, &oglCard->vbo);
    glDeleteBuffers(1, &oglCard->ebo);
}

#else
CommonGLMeshHandler::~CommonGLMeshHandler() {}
IRenderIDCard* CommonGLRenderer::load(Mesh& mesh)
{
    return nullptr;
}
void CommonGLRenderer::unload(IRenderIDCard* card) {}

#endif