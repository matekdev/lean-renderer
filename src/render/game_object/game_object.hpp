#pragma once

#include "mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class GameObject
{
public:
    enum Type
    {
        Model,
        Light
    };

    std::string Name;
    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f); // pitch, yaw, roll?
    glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);

    // material
    glm::vec3 Ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 Diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 Specular = glm::vec3(0.5f, 0.5f, 0.5f);
    float Shininess = 32.0f;

    int RenderingMode = 0;

    GameObject(const std::string &filePath, const Type &type = Type::Model);

    Type GetType();
    int GetVertexCount();
    int GetTriangleCount();
    glm::mat4 GetTransform();
    void Render(Shader &shader);
    void RenderOutline(Shader &shader);

private:
    inline static int _id;
    Type _type;
    std::vector<Mesh> _meshes;
    std::vector<Texture> _texturesLoaded;
    std::string _directory;

    int _vertexCount;
    int _triangleCount;

    void ProcessNode(aiNode *node, const aiScene *scene);
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName);
    void CalculateStats();
};