#include <fstream>
#include <iostream>
#include <functional>
#include <map>
#include "material.h"
#include "load.h"

std::map<std::string, material> *	load::MtlFile(std::string const & path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cerr << "Unable to open mtl file \"" << path << "\"" << std::endl;
		file.close();
		return NULL;
	}
	std::string		line;
	std::string		param;
	material		nowhere;
	material		*mtl = &nowhere;
	std::string::size_type i;
	std::map<std::string, material> *result = new std::map<std::string, material>;
	const std::map<std::string, std::function<void()> > funct =
	{
		{ "newmtl", [&]() { mtl = &(result[0][param]); } },
		{ "Ka",		[&]() { mtl->ambient = getColor(param); } },
		{ "Kd",		[&]() { mtl->diffuse = getColor(param); } },
		{ "Ks",		[&]() { mtl->specular = getColor(param); } },
		{ "map_Ka", [&]() { mtl->map_Ka = load::Texture(param); } },
		{ "map_Kd", [&]() { mtl->map_Kd = load::Texture(param); } },
		{ "map_Ks",	[&]() { mtl->map_Ks = load::Texture(param); } }
	};

	while (std::getline(file, line))
	{
		line = trim(TRIM_D, line);
		i = line.find(' '); /* ! */
		line = line.substr(0, i - 1);
		param = line.substr(i);
		if (funct.find(line) != funct.end())
			funct.find(line)->second(); /* ! find() x2 -> tmp iterator*/
	}
	file.close();
	return result;
}
