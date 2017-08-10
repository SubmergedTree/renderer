#pragma once

#include <glm\glm.hpp>


#include "ModelLoader.h"
#include "TextureBase.h"

#include <string>

namespace gE
{

	class TerrainMesh
	{
		friend class TerrainRenderer;

	public:
		TerrainMesh(int gridX, int gridZ, std::string heightmap);
		~TerrainMesh();

		void setSpecularR(TextureBase& specularR);
		void setSpecularG(TextureBase& specularG);
		void setSpecularB(TextureBase& specularB);

		void setDiffuseR(TextureBase& diffuseR);
		void setDiffuseG(TextureBase& diffuseG);
		void setDiffuseB(TextureBase& diffuseB);

		void setSpecularBackground(TextureBase& specBack);
		void setDiffuseBackground(TextureBase& difBack);

		void setBlendMap(TextureBase& blendMap);

		int getXposition();
		int getZposition();

		float getHeightOfTerrain(float x, float z);

	private:

		void generateTerrain();

		float getHeightfromHeightmap(int x, int z);
		void loadHeightmap(std::string heightmap);
		unsigned int heightmapWidth, heightmapHeight;

		const int SIZE;
		static const int VERTEX_COUNT = 256;

		float heights[VERTEX_COUNT][VERTEX_COUNT];

		std::vector<unsigned char> finalImage;

		std::vector<float> red, green, blue;

		glm::vec3 calculateNormal(int x, int z);

		Model* model;

		int xPosition;
		int zPosition;

		TextureBase specularR;
		TextureBase diffuseR;

		TextureBase specularG;
		TextureBase diffuseG;

		TextureBase specularB;
		TextureBase diffuseB;

		TextureBase specularBackground;
		TextureBase diffuseBackground;

		TextureBase blendMap;
	};

}