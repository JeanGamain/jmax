#include <fstream>
#include <iostream>
#include <functional>
#include "load.h"

model *			load::OffFile(std::string const & path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cerr << "Unable to open file \"" << path << "\"" << std::endl;
		file.close();
		return NULL;
	}
	std::string	line;
	if (!std::getline(file, line) || trim(TRIM_D, line) != "OFF" || !std::getline(file, line))
	{
		std::cerr << "Invalid .off file header \"" << path << "\"" << std::endl;
		file.close();
		return NULL;
	}	
	std::string::size_type sz;
	model *		result = new model;
	mesh		*mesh = &result->mesh;

	line = trim(TRIM_D, line);
	mesh->nbVertex = std::stoi(line, &sz);
	line = line.substr(sz);
	mesh->nbPrimitive = std::stoi(line, NULL);
	std::string	param;
	if (mesh->nbVertex < 0 || mesh->nbPrimitive < 0)
	{
		std::cerr << "Invalid .off file \"" << path << "\"" << std::endl;
		file.close();
		return NULL;
	}
	
	mesh->vertex = new vec3[mesh->nbVertex];
	mesh->primitive = new idx3d[mesh->nbPrimitive * 3]; /* ! 3 TRIANGLE ONLY! */
	unsigned int i[4] = {0, 0, 0, 0};
	while (std::getline(file, line))
	{
		line = trim(TRIM_D, line);
		if (line.empty())
			continue;
		if (i[0] < mesh->nbVertex)
		{
			nblistd(line, mesh->vertex[i[1]], 3);
			i[1]++;
		}
		else
		{
			i[3] = std::stoi(line, &sz);
			line = line.substr(sz);
			if (i[3] == 3)
			{
				nblistui(line, &mesh->primitive[i[2] * 3], 3); /* ! 3 TRIANGLE ONLY! */
				i[2]++;
			}
		}
		i[0]++;
	}
	if (i[1] != mesh->nbVertex || i[2] != mesh->nbPrimitive)
		std::cerr << "Warning .off file corrupted \"" << path << "\"" << std::endl;
	file.close();
	std::cout
		<< "Vertex: " << mesh->nbVertex << std::endl
		<< "Normal: " << mesh->nbNormal << std::endl
		<< "TextureCord: " << mesh->nbTextureCord << std::endl
		<< "Primitive: " << mesh->nbPrimitive << std::endl
		<< "Size: " <<
			(sizeof(mesh) +
			mesh->nbVertex * sizeof(vec3) +
			mesh->nbNormal * sizeof(vec3) +
			mesh->nbTextureCord * sizeof(vec2) +
			mesh->nbPrimitive * sizeof(idx3d)) / 1000
		<< "Ko" << std::endl;

	return result;
}
