#include "ResourceManager.h"

#include "FileLoader.h"
#include "util.h"
#include "Error.h"

void ResourceManager::loadStringPairFile(std::string fileName)
{
	std::pair<std::string, std::map<std::string, std::string>*> pair;
	pair.first = fileName;
	pair.second = gE::loadStringPairFile(fileName);

	stringPairFiles.insert(pair);
}

int ResourceManager::getIntFromStringPairFile(std::string fileName, std::string key)
{
	auto iterator = stringPairFiles.find(fileName);

	if (iterator == stringPairFiles.end())
	{
		gE::warning("can't find stringPair");
		throw 111;
	}

	std::string result = iterator->second->find(key)->second;
	if (gE::isNumber(result))
	{
		return std::stoi(result);
	}
	gE::warning("is not of type");

	return -1;
}

float ResourceManager::getFloatFromStringPairFile(std::string fileName, std::string key)
{
	auto iterator = stringPairFiles.find(fileName);

	if (iterator == stringPairFiles.end())
	{
		gE::warning("can't find stringPair");

		throw 111;
	}

	std::string result = iterator->second->find(key)->second;


	if (gE::isNumber(result))
	{
		return std::stof(result);
	}
	gE::warning("is not of type");
	return -1;
}

#include<iostream>
std::string ResourceManager::getStringFromStringPairFile(std::string fileName, std::string key)
{
	auto iterator = stringPairFiles.find(fileName);

	if (iterator == stringPairFiles.end())
	{
		gE::warning("can't find pair");

		throw 111;
	}
	else
	{
		auto iteratorInner = iterator->second->find(key);

		if (iteratorInner == iterator->second->end())
		{
			gE::warning("can't find pair");

			throw 111;
		}
		else
		{
			return  iterator->second->find(key)->second;
		}
	}
}