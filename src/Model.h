#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Mesh.h"
#include "Texture.h"
class Model
{

public:
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec3 binormal;
		glm::vec3 tangent;
		glm::vec2 uv;
	};
	Model() = delete;
	Model(const char* i_meshFile, const char* i_textureFile);
	~Model();

	void Render();
	/*Vertex* vertices;
	GLuint* indices;*/
	Mesh* m_mesh;
	Texture* m_texture;
	int numVertex;
	int numIndex;
};