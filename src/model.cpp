#include "model.h"

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>

#include <pttk/log.h>
#include "mesh.h"
#include "texturefactory.h"

Model::Model(const std::filesystem::path &path)
{
    Assimp::Importer import;
    const aiScene *scene =
        import.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        lError << "Error while loading an asset using assimp.\n" << import.GetErrorString();
        return;
    }
    m_directory = path.parent_path();

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.emplace_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++) processNode(node->mChildren[i], scene);
}

Mesh &&Model::processMesh(aiMesh *mesh, const aiScene *scene) const
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture *> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.position =
            glm::vec3 {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
        vertex.normal = glm::vec3 {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
        if (mesh->mTextureCoords[0])
        {
            vertex.texcoords =
                glm::vec2 {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
        }
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        auto &face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture *> diffuseMaps =
            loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        std::vector<Texture *> specularMaps =
            loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    return std::move(Mesh(std::move(vertices), std::move(indices), std::move(textures)));
}

std::vector<Texture *> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                                   const std::string &typeName) const
{
    std::vector<Texture *> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        auto texPath = m_directory / str.C_Str();
        textures.push_back(TextureFactory::instance().generateTexture(texPath));
    }
    return textures;
}