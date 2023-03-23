#pragma once
#include "../Shader/Shader.h"
#include "../Mesh/Mesh.h"
#include "../Camera/Camera.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
    Model(const char* path, const Material& material);
    ~Model();
    void Draw(const Camera& camera, const Shader& shader) const;
private:
    // model data
    std::vector<Mesh> m_meshes;
    std::string m_directory;
    const Material* m_Material;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    //std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};