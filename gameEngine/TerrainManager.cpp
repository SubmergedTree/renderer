#include "TerrainManager.h"


namespace gE
{
	TerrainKey::TerrainKey()
	{}
	TerrainKey::TerrainKey(int x, int z) : x(x), z(z)
	{}

	bool TerrainKey::operator<(const TerrainKey & terrainKey) const
	{
		return (x < terrainKey.x || (x == terrainKey.x && z< terrainKey.z));
	}

	bool TerrainKey::operator==(const TerrainKey & terrainKey) const
	{
		return ( x == terrainKey.x) && (z == terrainKey.z);
	}



	TerrainManager::TerrainManager(TerrainRenderer* renderer) : terrainRenderer(renderer), isOverTile(false)
	{
		directions[0] = TerrainKey(1,0);
		directions[1] = TerrainKey(1, 1);
		directions[2] = TerrainKey(0, 1);
		directions[3] = TerrainKey(-1, 1);
		directions[4] = TerrainKey(-1, 0);
		directions[5] = TerrainKey(-1, -1);
		directions[6] = TerrainKey(0, -1);
		directions[7] = TerrainKey(1, -1);
	}


	TerrainManager::~TerrainManager()
	{
		delete terrainRenderer;
		terrainRenderer = nullptr;
	}

	void TerrainManager::add(TerrainMesh * terrainMesh)
	{
		TerrainKey tK(0,0);
		tK.x = terrainMesh->getXposition() / terrainSize;
		tK.z = terrainMesh->getZposition() / terrainSize;
		int isInMap = terrains.count(tK);
		if (isInMap > 0)
		{
			std::cout << "double" << std::endl;
			//warning
			return;
		}
		std::pair<TerrainKey, TerrainMesh*> appendix(tK, terrainMesh);
		terrains.insert(appendix);
	}

	void TerrainManager::deleteTerrain()
	{
		for (auto& it : terrains)
		{
			delete it.second;
			it.second = nullptr;
		}

		terrains.clear();
	}


	void TerrainManager::process(glm::mat4 viewMatrix)
	{
		isOverTile = false;
		for (auto const& it : terrains)
		{
			if ((cameraPos.x < it.first.x * 80 + terrainSize) && (it.first.x * 80 < cameraPos.x) &&
				(cameraPos.z < it.first.z * 80 + terrainSize) && (it.first.z * 80 < cameraPos.z))
			{
				isOverTile = true;
				currentTile = it.first;
				terrainRenderer->render(*it.second, viewMatrix);

				for (int i = 0; i < (int)directions.size(); i++)
				{
					auto jt = terrains.find(TerrainKey(currentTile.x + directions[i].x, currentTile.z + directions[i].z));
					if (jt != terrains.end())
					{
						terrainRenderer->render(*jt->second, viewMatrix);
					}
				}
			}
		}
	}

	void TerrainManager::setCameraPos(glm::vec3 & camPos)
	{
		this->cameraPos = camPos;
	}

	float TerrainManager::getHeightOfTerrain(float x, float z)
	{
		if (isOverTile)
		{
			auto it = terrains.find(currentTile);
			if (it == terrains.end())
			{
				return 0.0f;
			}

			return it->second->getHeightOfTerrain(x,z);

		}
		return 0.0f;
	}

}