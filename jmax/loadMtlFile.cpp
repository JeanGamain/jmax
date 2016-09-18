#include <fstream>
#include <iostream>
#include <functional>
#include <map>
#include "material.hpp"
#include "load.hpp"

namespace jmax
{
  std::map<std::string, material> *	jmax::load::MtlFile(std::string const & path, std::string const & filename)
  {
    std::ifstream file(path + filename);
    if (!file.is_open())
      {
	std::cerr << "Unable to open mtl file \"" << path << filename << "\"" << std::endl;
	file.close();
	return NULL;
      }
    std::string		line;
    std::string		argv;
    material		nowhere;
    material		*mtl = &nowhere;
    std::string::size_type spaceIndex;
    std::map<std::string, material> *result = new std::map<std::string, material>;
    std::map<std::string, std::function<void()>>::const_iterator i;
    const std::map<std::string, std::function<void ()>> funct =
      {
	{ "newmtl", [&]() { mtl = &(result[0][argv]); } },
	{ "Ka",	    [&]() { mtl->ambient = getColor(argv); } },
	{ "Kd",	    [&]() { mtl->diffuse = getColor(argv); } },
	{ "Ks",	    [&]() { mtl->specular = getColor(argv); } },
	//	{ "map_Ka", [&]() { mtl->map_Ka = load::Texture(findCorectFileName(path + argv)); } },
	{ "map_Kd", [&]() { mtl->map_Kd = load::Texture(findCorectFileName(path + argv)); } },
	//{ "map_Ks", [&]() { mtl->map_Ks = load::Texture(findCorectFileName(path + argv)); } }
      };
    
    while (std::getline(file, line))
      {
	line = trim(TRIM_D, line);
	if ((spaceIndex = line.find(' ')) == std::string::npos)
	  continue;
	argv = line.substr(spaceIndex + 1);
	line = line.substr(0, spaceIndex);
	if ((i = funct.find(line)) != funct.end())
	  i->second();
      }
    file.close();
    return result;
  }
}
