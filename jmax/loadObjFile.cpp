#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include "load.hpp"

namespace jmax
{
	model *		jmax::load::ObjFile(std::string const & path, std::string const & filename)
	{
		std::ifstream file(path + filename);
		if (!file.is_open())
		{
			std::cerr << "Unable to open file \"" << path << filename << "\"" << std::endl;
			file.close();
			return NULL;
		}

		std::string		line;
		model *			newModel = new model;
		std::vector<vec3>	vertex;
		std::vector<vec3>	normal;
		std::vector<vec2>	textureCord;

		optionKeys handler =
		{
			{ "v", // vertex
			[](std::string line, std::vector<vec3> & vertex, std::vector<vec2> &, std::vector<vec3> &, model *, std::string const &)
			{
				vec3 tmp;
				nblistd(line, reinterpret_cast<double *>(&tmp), 3);
				vertex.push_back(tmp);
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
			}
			},
			{ "vt", // texture
			[](std::string line, std::vector<vec3> &, std::vector<vec2> & textureCord, std::vector<vec3> &, model *, std::string const &)
			{
				vec2 tmp;
				nblistd(line, reinterpret_cast<double *>(&tmp), 2);
				textureCord.push_back(tmp);
			}
			},
			{ "vn", // normal
			[](std::string line, std::vector<vec3> &, std::vector<vec2> &, std::vector<vec3> &normal, model *, std::string const &)
			{
				vec3 tmp;
				nblistd(line, reinterpret_cast<double *>(&tmp), 3);
				normal.push_back(tmp);
			}
			},
			{ "f", // primitive
			[](std::string line, std::vector<vec3> & vertex, std::vector<vec2> &textureCord, std::vector<vec3> &normal, model * newModel, std::string const &)
			{
				if (strwordcount(line.c_str()) < 3)
					return;
				std::vector<model::mesh> primitive;
				model::mesh		newMesh;
				unsigned char	nbpoly = strwordcount(line.c_str());
				char *			tmp = const_cast<char*>(line.c_str());
				unsigned int	vtn[3];

				for (unsigned int p = 0; *tmp != '\0' && p < nbpoly; p++)
				{
				  tmp = const_cast<char*>(trim(TRIM_D, tmp).c_str());
					vtn[0] = static_cast<unsigned int>(strtod(tmp, &tmp));
					if (vtn[0] > 0 && --vtn[0] < vertex.size())
						memcpy(&newMesh.vertex, &vertex[vtn[0]], sizeof(vec3));
					if (*tmp++ == '/')
					{
						vtn[1] = static_cast<unsigned int>(strtod(tmp, &tmp));
						if (vtn[1] > 0 && --vtn[1] < vertex.size())
							memcpy(&newMesh.texture, &textureCord[vtn[1]], sizeof(vec2));
						if (*tmp++ == '/')
						{
							vtn[2] = static_cast<unsigned int>(strtod(tmp, &tmp));
							if (vtn[2] > 0 && --vtn[2] < vertex.size())
								memcpy(&newMesh.normal, &normal[vtn[2]], sizeof(vec3));
						}
					}
					primitive.push_back(newMesh);
				}
				if (primitive.size() == 3)
					newModel->_mesh.insert(newModel->_mesh.end(), primitive.begin(), primitive.end());
				else
				{
					std::vector<model::mesh>::const_iterator end = primitive.end() - 2;
					std::vector<model::mesh>::const_iterator lastVertex = primitive.end() - 1;
					for (std::vector<model::mesh>::const_iterator i = primitive.begin(); i != end;)
					{
						newModel->_mesh.push_back(*i);
						newModel->_mesh.push_back(*(++i));
						newModel->_mesh.push_back(*lastVertex);
					}
				}
			}
			},
			{ "usemtl",
			[](std::string line, std::vector<vec3> &, std::vector<vec2> &, std::vector<vec3> &, model * newModel, std::string const &)
			{
				std::map<std::string, material>::iterator i = newModel->_material.find(line);
				if (i == newModel->_material.end())
				{
					std::cerr << "Missing material " << line << std::endl;
					return;
				}
				newModel->_renderMap.push_back(model::materialAssoc{ newModel->_mesh.size(), &(i->second) });
			}
			},
			{ "mtllib",
			[](std::string line, std::vector<vec3> &, std::vector<vec2> &, std::vector<vec3> &, model * newModel, std::string const & path)
			{
			  const std::string filename = line;
				std::map<std::string, material> *newMaterial = MtlFile(path, filename);
				newModel->_material.insert(newMaterial->begin(), newMaterial->end());
				delete newMaterial;
			}
			}
		};
		/*
		while (std::getline(file, line))
		{
			line = trim(TRIM_D, line);
			optionKeys::const_iterator j;
			size_t e;
			if ((e = line.find_first_of(' ')) != std::string::npos &&
				(j = handler.find(line.substr(0, e))) != handler.end())
				counter[std::distance(handler.begin(), j)]++;
		}

		file.clear();
		file.seekg(0, std::ios::beg);
		*/

		while (std::getline(file, line))
		{
		  line = trim(TRIM_D, line);
		  optionKeys::const_iterator i;
		  size_t e;
		  if ((e = line.find_first_of(' ')) != std::string::npos &&
		      (i = handler.find(line.substr(0, e))) != handler.end())
		    {
		      line = trim(TRIM_D, line.substr(e));
		      i->second(line, vertex, textureCord, normal, newModel, path);
		    }
		}
		return newModel;
	}
}
