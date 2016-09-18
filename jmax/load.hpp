#ifndef LOAD_HPP_
# define LOAD_HPP_

# define TRIM_D " \a\b\t\v\f\r"

# include <string>
# include <map>
# include <vector>
# include "model.hpp"
# include "material.hpp"

namespace jmax
{
  namespace load
  {
    typedef std::map<std::string, void(*)(std::string, std::vector<vec3> &, std::vector<vec2> &, std::vector<vec3> &, model *, std::string const &)> optionKeys;
    
    unsigned int	Texture(std::string const & path);
    model *			Model(std::string const & path);

    model *			ObjFile(std::string const & path, std::string const & filename);
    model *			OffFile(std::string const & path, std::string const & filename);
    
    std::map<std::string, material> *	MtlFile(std::string const & path, std::string const &);
    std::string		findCorectFileName(std::string const & path);
    std::string		trim(char *charset, std::string str);
    material::color	getColor(std::string line);
    void			nblistui(std::string str, unsigned int *nblist, unsigned int maxlen);
    void			nblistd(std::string str, double *nblist, unsigned int maxlen);
    unsigned int	strwordcount(const char *str);
  };
}

#endif /* !LOAD_HPP_ */
