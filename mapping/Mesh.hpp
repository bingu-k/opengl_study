#ifndef MESH_HPP
#define MESH_HPP

#include "header.hpp"
#include "Shader.hpp"

class Mesh
{
private:
	GLuint	VBO, EBO;

	void	setupMesh(void);
public:
	GLuint					VAO;
	std::vector<Vertex>		vertices;
	std::vector<GLuint>		indices;
	std::vector<Texture>	textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void	Draw(Shader& shader);

	~Mesh();
};

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
};

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
};

void	Mesh::setupMesh(void)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coord));
	
	glBindVertexArray(0);
};

void	Mesh::Draw(Shader &shader)
{
	unsigned int	diffuseNum = 0, specularNum = 0, normalNum = 0, heightNum = 0;
	for (unsigned int idx = 0; idx < textures.size(); ++idx)
	{
		glActiveTexture(GL_TEXTURE0 + idx);
		std::string	name = "";
		if (textures[idx].type == "diffuse")
			name = "material.texture_" + textures[idx].type + std::to_string(++diffuseNum);
		else if (textures[idx].type == "specular")
			name = "material.texture_" + textures[idx].type + std::to_string(++specularNum);
		else if (textures[idx].type == "normal")
			name = "material.texture_" + textures[idx].type + std::to_string(++normalNum);
		else if (textures[idx].type == "height")
			name = "material.texture_" + textures[idx].type + std::to_string(++heightNum);
		shader.setFloat(name.c_str(), idx);

		glBindTexture(GL_TEXTURE_2D, textures[idx].id);
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

#endif