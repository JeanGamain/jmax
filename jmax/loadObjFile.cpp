#include <fstream>
#include <iostream>
#include "load.h"

namespace jmax
{
	model *		jmax::load::ObjFile(std::string const & path)
	{
		typedef std::map<std::string, std::pair<void(*)(), void(*)()>> optionKeys;

		std::ifstream file(path);
		if (!file.is_open())
		{
			std::cerr << "Unable to open file \"" << path << "\"" << std::endl;
			file.close();
			return NULL;
		}

		std::string		line;
		model *			model = new jmax::model;
		unsigned int	counter[6] = { 0 };

		const optionKeys handler =
		{
			{ "v", { // vertex
				[&model]()
				{ model->mesh.nbVertex++; },
				[&line, &model, &counter]()
				{
					nblistd(line, reinterpret_cast<double *>(model->mesh.vertex[counter[0]++]), 3);
					/*
					p = 0;
					while (p < 3)
					{
						if (obj->bound.box[p * 2])
						{
							obj->bound.box[p * 2] = 0;
							obj->bound.origin[p * 2] = vtx[p];
							obj->bound.origin[p * 2 + 1] = vtx[p];
						}
						else if (vtx[p] < obj->bound.origin[p * 2])
							obj->bound.origin[p * 2] = vtx[p];
						else if (vtx[p] > obj->bound.origin[p * 2 + 1])
							obj->bound.origin[p * 2 + 1] = vtx[p];
						p++;
					}*/
					counter[0]++;

				}
			} },
			{ "vt", { // texture
				[&model]()
				{ model->mesh.nbTextureCord++; },
				[&line, &model, &counter]()
				{
					nblistd(line, model->mesh.textureCord[counter[1]++], 2);
				}
			} },
			{ "vn", { // normal
				[&model]()
				{ model->mesh.nbNormal++; },
				[&line, &model, &counter]()
				{
					nblistd(line, model->mesh.textureCord[counter[2]++], 3);
				}
			} },
			{ "f", { // primitive
				[&line, &model]()
				{
					if (strwordcount(line.c_str()) == 3)
						model->mesh.nbPrimitive++;
				},
				[&line, &model, &counter]()
				{
					if (strwordcount(line.c_str()) != 3)
						return;
					unsigned char nbpoly = strwordcount(line.c_str());
					unsigned int p = 0;
					char *tmp = const_cast<char*>(line.c_str());
					while (*tmp != '\0' && p < nbpoly)
					{
						model->mesh.primitive[counter[6] + p].vertex =
							(unsigned int)strtod(tmp, &tmp);
						if (*tmp == '/')
						{
							model->mesh.primitive[counter[6] + p].textureCord =
								(unsigned int)strtod(1 + tmp, &tmp);
							if (*tmp == '/')
								model->mesh.primitive[counter[6] + p].normal =
								(unsigned int)strtod(1 + tmp, &tmp);
						}
						p++;
					}
					counter[6] += nbpoly; // !
					counter[3]++; // !
				}
			} },
			{ "usemtl", {
				NULL,
				[&line, &model, &counter]()
				{
					if (p == obj->nbMaterial)
						
					else
						obj->RenderIndex[counter[4]].material = &obj->Material[p];
					counter[4]++;
				}
			} },
			{ "mtllib", {
				NULL,
				[&line, &model, &counter, &path]()
				{
					size_t	i;
					if ((i = path.find_last_of('/')) != std::string::npos)
						line = path.substr(0, i) + "/" + line;
					model->material.push_back(MtlFile(line));
				}
			} }
		};

		while (std::getline(file, line))
		{
			line = trim(TRIM_D, line);
			optionKeys::const_iterator i;
			size_t e;
			if ((e = line.find_first_of(' ')) != std::string::npos &&
				(i = handler.find(line.substr(0, e))) != handler.end())
			{
				line = trim(TRIM_D, line.substr(e));
				(*i).second.first();
			}
		}
		file.clear();
		file.seekg(0, std::ios::beg);
		model->mesh.alloc();
		while (std::getline(file, line))
		{
			line = trim(TRIM_D, line);
			optionKeys::const_iterator i;
			size_t e;
			if ((e = line.find_first_of(' ')) != std::string::npos &&
				(i = handler.find(line.substr(0, e))) != handler.end())
			{
				line = trim(TRIM_D, line.substr(e));
				(*i).second.second();
			}
		}
		return model;
	}
}