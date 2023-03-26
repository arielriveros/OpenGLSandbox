#pragma once
#include "../Shader/Shader.h"
#include "../Mesh/Mesh.h"
#include "../Camera/Camera.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ModelLoader
{
public:
    ModelLoader();
    ~ModelLoader();
    void LoadModel(std::string path, Mesh* target);
private:
    // model data
    std::vector<Texture> m_TexturesLoaded;
    std::string m_Directory;
    
    void processNode(aiNode* node, const aiScene* scene, Mesh* target);
    void processMesh(aiMesh* mesh, const aiScene* scene, Mesh* target);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const char* typeName);
};