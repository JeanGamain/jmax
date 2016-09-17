#ifndef MATERIAL_HPP_
# define MATERIAL_HPP_

#include <list>

namespace jmax
{
	class material
	{
	public:
		material();
		virtual ~material();

		void	setup() const;

	public:
		typedef union	u_color
		{
			unsigned int	integer;
			unsigned char	tab[4];
		}				color;

		unsigned char	transparency;
		unsigned char	reflexion;
		unsigned int	map_Ka;
		unsigned int	map_Kd;
		unsigned int	map_Ks;
		unsigned int	map_bump;
		color	ambient;
		color	diffuse;
		color	specular;

	};
}

#endif /* !MATERIAL_HPP_ */
