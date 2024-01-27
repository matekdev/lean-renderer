#include "game_object.hpp"

#include "log.hpp"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <numeric>

GameObject::GameObject(const std::string &filePath)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        LOG(ERROR) << "ERROR::ASSIMP:: " << import.GetErrorString();
        return;
    }

    Name = filePath.substr(filePath.find_last_of("/\\") + 1) + std::to_string(_id++);
    _directory = filePath.substr(0, filePath.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
    CalculateStats();
}

int GameObject::GetVertexCount()
{
    return _vertexCount;
}

int GameObject::GetTriangleCount()
{
    return _triangleCount;
}

glm::mat4 GameObject::GetTransform()
{
    glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));
    return glm::translate(glm::mat4(1.0f), Position) * rotation * glm::scale(glm::mat4(1.0f), Scale);
}

void GameObject::Render(Shader &shader)
{
    glUseProgram(shader.GetId());
    shader.SetBool(_texturesLoaded.size() > 0, "HasTexture");
    shader.SetVec3(Color, "Color");
    shader.SetMat4(GetTransform(), "Model");

    for (auto &mesh : _meshes)
    {
        mesh.SetRenderingMode(RenderingMode);
        mesh.Render(shader);
    }
}

void GameObject::ProcessNode(aiNode *node, const aiScene *scene)
{
    for (int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(ProcessMesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh GameObject::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
        {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures);
}

std::vector<Texture> GameObject::LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for (int i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString str;
        material->GetTexture(type, i, &str);
        bool skipLoading = false;
        for (unsigned int j = 0; j < _texturesLoaded.size(); j++)
        {
            if (std::strcmp(_texturesLoaded[j].Path.data(), str.C_Str()) == 0)
            {
                textures.push_back(_texturesLoaded[j]);
                skipLoading = true;
                break;
            }
        }

        if (!skipLoading)
        {
            Texture texture;
            texture.Id = TextureFromFile(str.C_Str(), _directory);
            texture.Type = typeName;
            texture.Path = str.C_Str();
            textures.push_back(texture);
            _texturesLoaded.push_back(texture);
        }
    }

    return textures;
}

void GameObject::CalculateStats()
{
    _vertexCount = std::accumulate(
        _meshes.begin(), _meshes.end(), 0,
        [](int accumulator, Mesh &mesh)
        {
            return accumulator + mesh.VertexCount;
        });

    _triangleCount = std::accumulate(
                         _meshes.begin(), _meshes.end(), 0,
                         [](int accumulator, Mesh &mesh)
                         {
                             return accumulator + mesh.IndexCount;
                         }) /
                     3;
}
