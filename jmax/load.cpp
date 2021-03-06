#include <SOIL.h>
#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <GL/glew.h>
#include <sys/types.h>
#include <dirent.h>
#include <algorithm>
#include "load.hpp"
#include "material.hpp"

namespace jmax
{
  
  std::string		load::findCorectFileName(std::string const & path) {
    DIR *		dir;
    struct dirent *	fileName;
    std::string		dirPath;
    std::string		originalFileName;
    std::string		testFileName;
    
    const size_t last_slash_idx = path.find_last_of("/\\");
    if (std::string::npos != last_slash_idx) {
      dirPath = path.substr(0, last_slash_idx);
      originalFileName = path.substr(last_slash_idx + 1);
    } else {
      dirPath = ".";
      originalFileName = path;
    }
    transform(originalFileName.begin(), originalFileName.end(), originalFileName.begin(), ::tolower);
    dir = opendir(dirPath.c_str());
    while ((fileName = readdir(dir)))
      {
	if (fileName->d_type != DT_REG)
	  continue;
	testFileName = fileName->d_name;
	transform(testFileName.begin(), testFileName.end(), testFileName.begin(), ::tolower);
	if (testFileName == originalFileName)
	  return dirPath + '/' + fileName->d_name;
      }
    return path;
  }

  unsigned int	load::Texture(std::string const & path)
  {
    std::cout << "texture:" << path.c_str() << std::endl;
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
    const std::map<std::string, model * (*)(std::string const & path, std::string const & filename)> loader =
      {
	{ "obj", jmax::load::ObjFile },
	{ "off", jmax::load::OffFile }
      };
    if (loader.find(ext) != loader.end())
      {
	size_t	i = path.find_last_of('/');
	model *result;
	
	if (i == std::string::npos ||
	    (result = loader.find(ext)->second(path.substr(0, i + 1), path.substr(i + 1))) == NULL) {
	  
	  i++;
	  return NULL;
	}
	std::cout
	  << "Primitive: " << result->_mesh.size() / 3 << std::endl
	  << "Materials: " << result->_material.size() << std::endl
	  << "Rendering operation: " << result->_renderMap.size() << std::endl;
	  /*
	  << "Size: " <<
	  (sizeof(jmax::mesh)
	   + result->_mesh.size() * sizeof(jmax::model::mesh))
	  + result->_material.size() * 
	  / 1000 << "Ko" << std::endl;*/
	return result;
      }
    else
      std::cerr << "Unsupported model file \"" << path << "\"" << std::endl;
    return NULL;
  }
  
  std::string			 load::trim(char* charset, std::string str)
  {
    int i;
    
    i = 0;
    while (str[i] != '\0' && strchr(charset, str[i]) != NULL)
      i++;
    str = str.substr(i);
    i = str.length();
    while (strchr(charset, str[i]) != NULL)
      i--;
    i++;
    return const_cast<char *>(str.substr(0, i).c_str());
  }
  
  material::color		load::getColor(std::string line)
  {
    material::color		res;
    std::string::size_type	sz;
    double			tmp;
    unsigned char		i;
    
    res.integer = 0;
    i = 0;
    while (i < 3)
      {
	tmp = std::stod(line, &sz);
	line = line.substr(sz);
	res.tab[i] = (tmp < 0) ? 0 : ((tmp > 1) ? 1 : static_cast<unsigned char>(255 * tmp));
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
