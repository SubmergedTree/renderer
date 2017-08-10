#pragma once

#include <vector>
#include<glm\glm.hpp>
#include <GL\glew.h>
#include <iostream>

namespace gE
{
	struct Model
	{
	public:
		Model(GLuint vao, int vertexNumber);
		GLuint getVao();
		int getVertexNumber();
	private:
		GLuint vao;
		int vertexNumber;
	};


	class ModelLoader
	{
	public:
		ModelLoader();
		~ModelLoader();

		Model* createModel(std::vector<glm::vec3>verticies,
			std::vector<glm::vec2> uv,
			std::vector<glm::vec3> normals,
			std::vector<GLuint> indices);

	private:

		unsigned int createVAO();
		void unbindVAO();

		void createEBO(std::vector<GLuint> indices);

		template<typename T>
		void fillDataInVAO(int attributeNumber, int coordinateSize, std::vector<T> data);


		std::vector<int> glObjectsTracker;
	};

	template<typename T>
	inline void ModelLoader::fillDataInVAO(int attributeNumber, int coordinateSize, std::vector<T> data)
	{
		GLuint vbo;
		glGenBuffers(1, &vbo);

		glObjectsTracker.push_back(vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), &data[0], GL_STATIC_DRAW);

		glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, sizeof(T), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}