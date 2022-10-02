#pragma once

#include <GL\glew.h>

class Mesh
{
public:
	Mesh() = default;
	~Mesh();

	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh() const;
	void ClearMesh();


private:
	GLuint m_VAOID{}, m_VBOID{}, m_IBOID{};
	GLsizei m_indexCount;
};

