#include <fstream>
#include <iostream>
#include <functional>
#include "load.hpp"

namespace jmax
{
	model *			jmax::load::OffFile(std::string const & path, std::string const & filename)
	{
		std::ifstream file(path + filename);
		if (!file.is_open())
		{
			std::cerr << "Unable to open file \"" << path << "\"" << std::endl;
			file.close();
			return NULL;
		}
		std::string	line;
		if (!std::getline(file, line) || trim(TRIM_D, line).c_str() != "OFF" || !std::getline(file, line))
		{
			std::cerr << "Invalid .off file header \"" << path << "\"" << std::endl;
			file.close();
			return NULL;
		}
//		std::string::size_type sz;
		model *		result = new model;
	/*	mesh		*mesh = &result->mesh;

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

		mesh->alloc();
		unsigned int i[4] = { 0, 0, 0, 0 };
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
					idx3d	bra[3];
					nblistui(line, bra, 3);
					mesh->primitive[i[2] * 3].vertex = bra[0];
					mesh->primitive[i[2] * 3 + 1].vertex = bra[0];
					i[2]++;
				}
			}
			i[0]++;
		}
		if (i[1] != mesh->nbVertex || i[2] != mesh->nbPrimitive)
			std::cerr << "Warning .off file corrupted \"" << path << "\"" << std::endl;*/
		file.close();
		return result;
	}
}
