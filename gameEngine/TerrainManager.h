#pragma once

#include "TerrainMeshGenerator.h"
#include "TerrainRenderer.h"
#include <map>
#include <glm\glm.hpp>
#include <array>

namespace gE
{

	struct TerrainKey
	{
		TerrainKey();
		TerrainKey(int x, int z);

		int x;
		int z;

		bool operator<(const TerrainKey& terrainKey) const;
		bool operator==(const TerrainKey& terrainKey) const;
	};

	class TerrainManager
	{
	public:
		TerrainManager(TerrainRenderer* renderer);
		~TerrainManager();

		void add(TerrainMesh* terrainMesh);

		void deleteTerrain();

		void process(glm::mat4 viewMatrix);

		void setCameraPos(glm::vec3& cameraPos);

		float getHeightOfTerrain(float x,float z);

	private:
		std::map<TerrainKey, TerrainMesh*> terrains;
		glm::vec3 cameraPos;
		TerrainKey currentTile;
		const int terrainSize = 80;
		TerrainRenderer* terrainRenderer;
		std::array<TerrainKey,8> directions;

		bool isOverTile;

	};
}