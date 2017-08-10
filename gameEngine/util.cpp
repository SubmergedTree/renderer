#include "util.h"


namespace gE
{

	inline bool isNumber(const std::string & s)
	{
		if (s.empty() || ((!isdigit(s[0])))) return false;

		char * p;
		strtol(s.c_str(), &p, 10);

		return (*p == 0);
	}

}