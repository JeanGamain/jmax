#ifndef MESH_H_
# define MESH_H_

#include "math.h"

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
			idx3d	vertex;
			idx3d	normal;
			idx3d	textureCord;
		}			vtxInfo;

		idx3d	nbVertex; // short" later
		vec3	*vertex;
		idx3d	nbNormal;
		vec3	*normal;
		idx3d	nbTextureCord;
		vec2	*textureCord;
		idx3d	nbPrimitive;
		vtxInfo	*primitive;
	};
}

#endif /* !MESH_H_ */