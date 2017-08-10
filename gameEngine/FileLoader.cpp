#include "FileLoader.h"

#include <fstream>
#include <sstream>
#include "Error.h"

namespace gE
{
	std::map<std::string, std::string>* loadStringPairFile(std::string path)
	{
		std::map<std::string, std::string> *  returnValue = new std::map<std::string, std::string>;

		std::string line;
		std::string key, value;
		std::ifstream fileToRead(path);

		if (fileToRead.is_open())
		{

			std::istringstream iss(line);
			while (std::getline(fileToRead, line))
			{
				bool firstValue = true;
				std::string buffer;
				std::stringstream ss(line);

				while (ss >> buffer)
				{
					if (firstValue)
					{
						key = buffer;
						firstValue = false;
					}
					else
					{
						value = buffer;
					}
				}
				returnValue->insert(std::pair<std::string, std::string>(key, value));
			}

			fileToRead.close();
		}
		else
		{
			error("unable to open file");
		}
		return returnValue;
	}

	std::string  loadFromFile(std::string path)
	{
		std::string result;

		std::ifstream fileToRead(path);

		if (fileToRead.is_open())
		{
			std::stringstream ss;
			ss << fileToRead.rdbuf();
			fileToRead.close();
			result = ss.str();
		}
		else
		{
			error("unable to open file");
		}
		return result;
	}

}

