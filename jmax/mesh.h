#ifndef MESH_H_
# define MESH_H_

#include "math.h"

class mesh
{
public:
	mesh();
	virtual ~mesh();

public:
	idx3d	nbVertex; // short" later
	vec3	*vertex;
	idx3d	nbNormal;
	vec3	*normal;
	idx3d	nbTextureCord;
	vec2	*textureCord;
	idx3d	nbPrimitive;
	idx3d	*primitive;
};

#endif /* !MESH_H_ */