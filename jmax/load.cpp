#include <SOIL.h>
#include <iostream>
#include <map>
#include <string>
#include <Windows.h>
#include <GL\glew.h>
#include "load.h"
#include "material.h"

namespace jmax
{

	unsigned int	load::Texture(std::string const & path)
	{
		unsigned int texture =
			SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
			SOIL_FLAG_DDS_LOAD_DIRECT | SOIL_FLAG_COMPRESS_TO_DXT);
		if (texture == 0)
			std::cerr << "Error loading texture \"" << path << "\": " << SOIL_last_result() << std::endl;
		else
		{
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
		return texture;
	}

	model *			load::Model(std::string const & path)
	{
		std::string ext = path.substr(path.find_last_of(".") + 1);
		const std::map<std::string, model * (*)(std::string const & filename)> loader =
		{
			{ "obj", jmax::load::ObjFile },
			{ "off", jmax::load::OffFile }
		};
		if (loader.find(ext) != loader.end())
		{
			model *result = loader.find(ext)->second(path);
			std::cout
				<< "Vertex: " << result->mesh.nbVertex << std::endl
				<< "Normal: " << result->mesh.nbNormal << std::endl
				<< "TextureCord: " << result->mesh.nbTextureCord << std::endl
				<< "Primitive: " << result->mesh.nbPrimitive << std::endl
				<< "Size: " <<
				(sizeof(mesh) +
				result->mesh.nbVertex * sizeof(vec3) +
				result->mesh.nbNormal * sizeof(vec3) +
				result->mesh.nbTextureCord * sizeof(vec2) +
				result->mesh.nbPrimitive * sizeof(idx3d)) / 1000
				<< "Ko" << std::endl;
			return result;
		}
		else
			std::cerr << "Unsupported model file \"" << path << "\"" << std::endl;
		return NULL;
	}

	std::string		load::trim(char* charset, std::string str)
	{
		unsigned int i;

		i = 0;
		while (str[i] != '\0' && strchr(charset, str[i]) != NULL)
			i++;
		str = str.substr(i);
		i = str.length();
		while (i > -1 && strchr(charset, str[i]) != NULL)
			i--;
		return (str.substr(0, i));
	}

	material::color		load::getColor(std::string line)
	{
		material::color		res;
		std::string::size_type sz;
		double				tmp;
		unsigned char		i;

		res.integer = 0;
		i = 0;
		while (i < 3)
		{
			tmp = std::stod(line, &sz);
			line = line.substr(sz);
			res.tab[i] = (tmp < 0) ? 0 : ((tmp > 1) ? 1 : unsigned char(255 * tmp));
			i++;
		}
		return (res);
	}

	void	load::nblistd(std::string str, double *nblist, unsigned int maxlen)
	{
		unsigned int		   nb;
		std::string::size_type sz;
		nb = 0;
		while (!str.empty() && nb != maxlen)
		{
			nblist[nb++] = std::stod(str, &sz);
			str = str.substr(sz);
		}
	}

	void	load::nblistui(std::string str, unsigned int *nblist, unsigned int maxlen)
	{
		unsigned int		   nb;
		std::string::size_type sz;
		nb = 0;
		while (!str.empty() && nb != maxlen)
		{
			nblist[nb++] = std::stoul(str, &sz);
			str = str.substr(sz);
		}

	}

	unsigned int	load::strwordcount(const char *str)
	{
		unsigned int	i;
		unsigned int	nb;

		i = 0;
		nb = 0;
		while (1)
		{
			while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t'))
				i++;
			if (str[i] == '\0')
				return (nb);
			while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
				i++;
			nb++;
		}
	}
}