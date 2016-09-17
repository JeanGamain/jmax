#ifndef MESH_H_
# define MESH_H_

#include "math.hpp"
#include "material.hpp"

namespace jmax
{
	class mesh
	{
	public:
		mesh();
		virtual ~mesh();

		void	alloc();
	public:
		typedef struct
		{				
			vec3	pos;
			vec3	normal;
			vec2	texture;
		}			vertex;

		idx3d		nbPrimitive; // nbPrimitive = nbVertex / 3 short" later
		vertex *	primitive;
	};
}

#endif /* !MESH_H_ */