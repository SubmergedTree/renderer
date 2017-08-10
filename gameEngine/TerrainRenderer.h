#pragma once

#include "TerrainShader.h"
#include "TerrainMeshGenerator.h"

namespace gE
{

	class TerrainRenderer
	{
	public:
		TerrainRenderer(TerrainShader * simpleShader, GLfloat fov, GLfloat screenWidth, GLfloat screenHeight);
		~TerrainRenderer();

		void render(TerrainMesh& tMG, glm::mat4& viewMatrix);

	private:

		void loadShaderUniforms(glm::mat4& viewMatrix, GLfloat xpos, GLfloat zpos);

		TerrainShader* terrainShader;
		GLfloat screenWidth, screenHeight;
		GLfloat fov;

	};

}