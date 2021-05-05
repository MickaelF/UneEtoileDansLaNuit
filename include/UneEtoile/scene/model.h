#pragma once
#include <assimp/material.h>

#include <filesystem>

class aiNode;
class aiScene;
class aiMesh;
class Mesh;
class Texture;

class Model
{
public:
    explicit Model(const std::filesystem::path& path);

private:
    void processNode(aiNode* node, const aiScene* scene);
    Mesh&& processMesh(aiMesh* mesh, const aiScene* scene) const;

    std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
                                               const std::string& typeName) const;

    std::vector<Mesh> m_meshes;
    std::filesystem::path m_directory;
};