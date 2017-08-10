#include "ModelLoader.h"

namespace gE
{

	ModelLoader::ModelLoader()
	{
	}


	ModelLoader::~ModelLoader()
	{
	}


	Model* ModelLoader::createModel(std::vector<glm::vec3> verticies, std::vector<glm::vec2> uv, std::vector<glm::vec3> normals, std::vector<GLuint> indices)
	{
		unsigned int  VAO, EBO;
		glGenVertexArrays(1, &VAO);

		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);


		fillDataInVAO<glm::vec3>(0, 3, verticies);
		fillDataInVAO<glm::vec2>(1, 2, uv);
		fillDataInVAO<glm::vec3>(2,3,normals);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);


		return new Model(VAO, indices.size());

	}

	unsigned int ModelLoader::createVAO()
	{
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glObjectsTracker.push_back(vao);
		return vao;
	}

	void ModelLoader::unbindVAO()
	{
		glBindVertexArray(0);
	}

	void ModelLoader::createEBO(std::vector<GLuint> indices)
	{
		GLuint ebo;
		glGenBuffers(1,&ebo);
		glObjectsTracker.push_back(ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() * sizeof(GLuint),&indices[0],GL_STATIC_DRAW);

	}



	Model::Model(GLuint vao, int vertexNumber) : vao(vao), vertexNumber(vertexNumber)
	{
	}

	GLuint Model::getVao()
	{
		return vao;
	}

	int Model::getVertexNumber()
	{
		return vertexNumber;
	}

}