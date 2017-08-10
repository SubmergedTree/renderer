#include "Error.h"

#include <fstream>

namespace gE
{

	class FileRAII
	{
	public:
		FileRAII()
		{
			errorFile.open("errorReport.txt");
		}

		~FileRAII()
		{
			errorFile.close();
		}

		void writeTo(std::string msg)
		{
			errorFile << msg << "\n \n";
		}

	private:
		std::ofstream errorFile;
	};

	void warning(std::string warningMsg)
	{
		FileRAII write;
		std::string msg = "warning: ";
		msg += warningMsg;
		write.writeTo(msg);
	}

	void error(std::string error)
	{
		FileRAII write;
		std::string msg = "error: ";
		msg += error;
		write.writeTo(msg);

		exit(EXIT_FAILURE);
	}
}