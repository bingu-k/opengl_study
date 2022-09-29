#ifndef MODEL_HPP
#define MODEL_HPP

#include "header.hpp"
#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Shader;

unsigned int	TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
private:
	std::vector<Mesh>	meshes;
	std::string			directory;

	std::vector<Texture>	textures_loaded;

	void	loadModel(std::string path);
	void	processNode(aiNode* node, const aiScene* scene);
	Mesh	processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture>	loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
public:

	Model(std::string path);
	void	Draw(Shader& shader);
	~Model();
};

Model::Model(std::string path)
{ loadModel(path); };

void	Model::Draw(Shader& shader)
{
	for (unsigned int idx = 0; idx < meshes.size(); ++idx)
		meshes[idx].Draw(shader);
};

Model::~Model()
{ };

void	Model::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
};

void	Model::processNode(aiNode* node, const aiScene* scene)
{
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for(unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene);
};

Mesh	Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex>		vertices;
	std::vector<GLuint>		indices;
	std::vector<Texture>	textures;

	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
		glm::vec3	pos, nor;
		glm::vec2	tex(0.0f, 0.0f);
		pos.x = mesh->mVertices[i].x;
		pos.y = mesh->mVertices[i].y;
		pos.z = mesh->mVertices[i].z;

		nor.x = mesh->mNormals[i].x;
		nor.y = mesh->mNormals[i].y;
		nor.z = mesh->mNormals[i].z;
        
		if (mesh->mTextureCoords[0])
		{
			tex.x = mesh->mTextureCoords[0][i].x;
			tex.x = mesh->mTextureCoords[0][i].y;
		}
		
        Vertex	vertex{pos, nor, tex};
		vertices.push_back(vertex);
    }
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; ++j)
			indices.push_back(mesh->mFaces[i].mIndices[j]);
	}
	if(mesh->mMaterialIndex >= 0)
    {
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, 
											aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material, 
											aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
	return (Mesh(vertices, indices, textures));
};

std::vector<Texture>	Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture>	textures;

    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; 
                break;
            }
        }
        if(!skip)
        {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
		}
    }
    return textures;
};

#endif