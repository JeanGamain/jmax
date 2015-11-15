#ifndef LOAD_H_
# define LOAD_H_

# define TRIM_D " \a\b\t\v\f\r"

# include <string>
# include <map>
# include "mesh.h"
# include "model.h"
# include "material.h"

namespace load
{
	unsigned int	Texture(std::string const & path);
	model *			Model(std::string const & path);

	model *			ObjFile(std::string const & path);
	model *			OffFile(std::string const & path);

	std::map<std::string, material> *	MtlFile(std::string const & path);

	std::string		trim(char *charset, std::string str);
	material::color	getColor(std::string line);
	void			nblistui(std::string str, unsigned int *nblist, unsigned int maxlen);
	void			nblistd(std::string str, double *nblist, unsigned int maxlen);
	unsigned int	strwordcount(char *str);
};

#endif /* !LOAD_H_ */
