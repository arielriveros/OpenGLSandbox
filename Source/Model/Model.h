//#pragma once
//#include "../Shader/Shader.h"
//#include "../Mesh/Mesh.h"
//#include "../Camera/Camera.h"
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//
//class Model
//{
//public:
//    Model(const char* path);
//    ~Model();
//    void Draw(const Camera& camera, const Shader& shader) const;
//private:
//    // model data
//    std::vector<Mesh> m_Meshes;
//    std::vector<TextureInfo> m_TexturesLoaded;
//    std::string m_Directory;
//
//    void loadModel(std::string path);
//    void processNode(aiNode* node, const aiScene* scene);
//    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
//    std::vector<TextureInfo> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
//    unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
//};