#pragma once

#include <map>
#include <string>

namespace gE
{

	extern std::map<std::string, std::string>* loadStringPairFile(std::string path);
	extern std::string loadFromFile(std::string path);
}