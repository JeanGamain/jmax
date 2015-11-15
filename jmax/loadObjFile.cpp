#include <fstream>
#include <iostream>
#include "load.h"

model *		load::ObjFile(std::string const & path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cerr << "Unable to open file \"" << path << "\"" << std::endl;
		file.close();
		return NULL;
	}
	return NULL;
	
}