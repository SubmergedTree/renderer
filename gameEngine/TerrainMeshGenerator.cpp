#include "TerrainMeshGenerator.h"

#include <iostream>
#include <vector>
#include <cmath>
#include "Math.h"

#include "LodePNG.h"

namespace gE
{

	TerrainMesh::TerrainMesh(int gridX, int gridZ, std::string heightmap) 
		:specularR(NULL), specularG(NULL), specularB(NULL), diffuseR(NULL),
		diffuseG(NULL), diffuseB(NULL), specularBackground(NULL), diffuseBackground(NULL),
		blendMap(NULL), SIZE(80)
	{
		xPosition = gridX * SIZE;//SIZE
		zPosition = gridZ * SIZE;//SIZE instead of 800
		loadHeightmap(heightmap);
		generateTerrain();
	}


	TerrainMesh::~TerrainMesh()
	{
		delete model;
		model = nullptr;
	}

	void TerrainMesh::setSpecularR(TextureBase & specularR)
	{
		this->specularR = specularR;
	}

	void TerrainMesh::setSpecularG(TextureBase & specularG)
	{
		this->specularG = specularG;
	}

	void TerrainMesh::setSpecularB(TextureBase & specularB)
	{
		this->specularB = specularB;
	}

	void TerrainMesh::setDiffuseR(TextureBase & diffuseR)
	{
		this->diffuseR = diffuseR;
	}

	void TerrainMesh::setDiffuseG(TextureBase & diffuseG)
	{
		this->diffuseG = diffuseG;
	}

	void TerrainMesh::setDiffuseB(TextureBase & diffuseB)
	{
		this->diffuseB = diffuseB;
	}

	void TerrainMesh::setSpecularBackground(TextureBase & specBack)
	{
		this->specularBackground = specBack;
	}

	void TerrainMesh::setDiffuseBackground(TextureBase & difBack)
	{
		this->diffuseBackground = difBack;
	}

	void TerrainMesh::setBlendMap(TextureBase & blendMap)
	{
		this->blendMap = blendMap;
	}


	int TerrainMesh::getXposition()
	{
		return xPosition;
	}

	int TerrainMesh::getZposition()
	{
		return zPosition;
	}

	float TerrainMesh::getHeightOfTerrain(float x, float z)
	{
		float terrainX = x - this->xPosition;
		float terrainZ = z- this->zPosition;

		float gridSquareSize = (SIZE / ((float)VERTEX_COUNT - 1));

		int gridX = (int)floorf(terrainX / gridSquareSize);
		int gridZ = (int)floorf(terrainZ / gridSquareSize);

		if (gridX >= VERTEX_COUNT - 1 || gridZ >= VERTEX_COUNT - 1 || gridX <0 || gridZ < 0)
		{
			return 0;
		}

		float xCoord = fmod(terrainX,gridSquareSize) / gridSquareSize;
		float zCoord = fmod(terrainZ, gridSquareSize) / gridSquareSize;

		float returnValue;

		if (xCoord <= (1 - zCoord)) {
			returnValue = barycentricInterpolation(glm::vec3(0, heights[gridX][gridZ], 0), glm::vec3(1,heights[gridX + 1][gridZ], 0), glm::vec3(0,heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
		}
		else {
			returnValue = barycentricInterpolation(glm::vec3(1, heights[gridX + 1][gridZ], 0), glm::vec3(1,heights[gridX + 1][gridZ + 1], 1), glm::vec3(0,heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
		}

		return returnValue;
	}

	void TerrainMesh::generateTerrain()
	{
	//	const int VERTEX_COUNT = 256;
	//	const int SIZE = size;

	//	float heights[VERTEX_COUNT][VERTEX_COUNT];

		const int count = VERTEX_COUNT * VERTEX_COUNT;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;

		std::vector<GLuint> indices(6 * ((VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)));

		int vertexPointer = 0;

		for (int i = 0; i < VERTEX_COUNT; i++)
		{
			for(int j = 0; j < VERTEX_COUNT; j++)
			{

				glm::vec3 vertex;
				vertex.x = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;

				float height = getHeightfromHeightmap(j,i);
				heights[j][i] = height;


				vertex.y = height;
				vertex.z = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;

				vertices.push_back(vertex);

				glm::vec3 normal = calculateNormal(j,i);
				normals.push_back(normal);

				glm::vec2 uv((float)j / ((float)VERTEX_COUNT - 1), (float)i / ((float)VERTEX_COUNT - 1));
				texCoords.push_back(uv);

				vertexPointer++;

			}
		}


		int pointer = 0;

		for (int gz = 0; gz < VERTEX_COUNT - 1; gz++)
		{
			for (int gx = 0; gx < VERTEX_COUNT - 1; gx++)
			{
				int topLeft = (gz*VERTEX_COUNT) + gx;
				int topRight = topLeft + 1;
				int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
				int bottomRight = bottomLeft + 1;
				indices[pointer++] = topLeft;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = topRight;
				indices[pointer++] = topRight;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = bottomRight;
			}
		}

		ModelLoader mL;

		model = mL.createModel(vertices, texCoords,normals,indices);

	
	}

	void TerrainMesh::loadHeightmap(std::string heightmap)
	{
		std::vector<unsigned char> png;
		std::vector<unsigned char> image; //the raw pixels
		unsigned int width = 0, height = 0;

		//load and decode
		unsigned error = lodepng::load_file(png, heightmap.c_str());
		if (!error) error = lodepng::decode(image, width, height, png);

		//if there's an error, display it
		if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

		heightmapWidth = width;
		heightmapHeight = height;

		int bar = 0;
		for (int i = 0; i < (int)image.size(); i++)
		{
			if (bar == 0)
			{
				red.push_back((float)image[i]);
				bar++;
			}
			else if (bar == 1)
			{
				green.push_back((float)image[i]);
				bar++;
			}
			else if (bar == 2)
			{
				blue.push_back((float)image[i]);
				bar++;
			}
			else if (bar == 3)
			{
				bar = 0;
			}
		}

	}

	float TerrainMesh::getHeightfromHeightmap(int x, int z)
	{
		if (x < 0 || x >= (int)heightmapHeight || z < 0 || z >= (int)heightmapHeight) 
		{
			return 0;
		}

		int index = (z * heightmapWidth) + x;

		float maxHeight = 40;
		float maxPixelColor = 256 * 256 * 256;

		float height = 0.2126f * red[index] + 0.7152f * green[index] + 0.0722f * blue[index];

		const float min = 0;
		const float max = 255;

		const float newMin = 0;
		const float newMax = 10;

		float normalized = (height - min) * ((newMax - newMin) / (max - min)) + newMin;

		return normalized;
	}

	glm::vec3 TerrainMesh::calculateNormal(int x, int z)
	{
		float heightL = getHeightfromHeightmap(x - 1,z);
		float heightR = getHeightfromHeightmap(x + 1, z);
		float heightD = getHeightfromHeightmap(x, z - 1);
		float heightU = getHeightfromHeightmap(x, z + 1);

		glm::vec3 normal = glm::vec3(heightL - heightR, 2.0f, heightD - heightU);
		glm::normalize(normal);

		return normal;
	}
}