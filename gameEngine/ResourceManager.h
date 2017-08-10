#pragma once

#include <string>
#include <map>



class ResourceManager
{
public:
	void loadStringPairFile(std::string fileName);

	int getIntFromStringPairFile(std::string fileName, std::string key);
	float getFloatFromStringPairFile(std::string fileName, std::string key);
	std::string getStringFromStringPairFile(std::string fileName, std::string key);


private:

	std::map<std::string, std::map<std::string, std::string>*> stringPairFiles;
};

