#ifndef MATERIAL_H_
# define MATERIAL_H_

namespace jmax
{
	class material
	{
	public:
		material();
		virtual ~material();

	public:
		typedef union	u_color
		{
			unsigned int	integer;
			unsigned char	tab[4];
		}				color;

		typedef struct
		{
			idx3d		start;
			idx3d		count;
		}				meshAssoc;

		std::list<meshAssoc>	assoc;

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

#endif /* !MATERIAL_H_ */
