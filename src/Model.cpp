
#include "Model.h"
#include <fstream>
#include <iostream>
#include <sstream>
Model::Model(const char* i_meshFile, const char* i_textureFile)
{
	Vertex* vertices;
	GLuint* indices;
	std::string content;
	std::ifstream in(i_meshFile, std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		content.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&content[0], content.size());
		in.close();
	}
	std::stringstream ss(content);
	std::string strtmp;
	int nrVertices;
	int nrIndices;
	std::getline(ss, strtmp, '\n');
	int rs = sscanf_s(strtmp.c_str(), "NrVertices: %d", &nrVertices);
	numVertex = nrVertices;
	vertices = new Vertex[nrVertices];
	for (int i = 0; i < nrVertices; i++)
	{
		std::getline(ss, strtmp, '\n');
		//int temp;
		int rs = sscanf_s(strtmp.c_str(), "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
			&vertices[i].pos.x, &vertices[i].pos.y, &vertices[i].pos.z, &vertices[i].normal.x, &vertices[i].normal.y, &vertices[i].normal.z,
			&vertices[i].binormal.x, &vertices[i].binormal.y, &vertices[i].binormal.z,
			&vertices[i].tangent.x, &vertices[i].tangent.y, &vertices[i].tangent.z,
			&vertices[i].uv.x, &vertices[i].uv.y);
	}

	std::getline(ss, strtmp, '\n');
	rs = sscanf_s(strtmp.c_str(), "NrIndices: %d", &nrIndices);
	numIndex = nrIndices;
	indices = new GLuint[nrIndices];
	int numLine = nrIndices / 3;
	for (int i = 0; i < numLine; ++i)
	{
		std::getline(ss, strtmp, '\n');
		//int temp;
		int rs = sscanf_s(strtmp.c_str(), "   %*d.  %d,  %d,  %d", &indices[3 * i], &indices[3 * i + 1], &indices[3 * i + 2]);
	}

	//Initialize Mesh
	GLfloat* verticesData = new GLfloat[nrVertices * 8];
	for (int i = 0; i < nrVertices; ++i)
	{
		verticesData[i * 8] = vertices[i].pos.x;
		verticesData[i * 8 + 1] = vertices[i].pos.y;
		verticesData[i * 8 + 2] = vertices[i].pos.z;
		verticesData[i * 8 + 3] = vertices[i].uv.x;
		verticesData[i * 8 + 4] = 1.0f - vertices[i].uv.y;
		verticesData[i * 8 + 5] = vertices[i].normal.x;
		verticesData[i * 8 + 6] = vertices[i].normal.y;
		verticesData[i * 8 + 7] = vertices[i].normal.z;
	}
	m_mesh = new Mesh();
	m_mesh->CreateMesh(verticesData, indices, nrVertices * 8, nrIndices);


	//Texture
	m_texture = new Texture(i_textureFile);
	m_texture->LoadTexture();
}

void Model::Render()
{
	m_texture->UseTexture();
	m_mesh->RenderMesh();
}

Model::~Model()
{
	delete m_mesh;
	delete m_texture;
}