#include <stddef.h>
#include "mesh.h"

namespace jmax
{
	mesh::mesh()
		: nbVertex(0), vertex(NULL), nbTextureCord(0), textureCord(NULL),
		nbNormal(0), normal(NULL), nbPrimitive(0), primitive(NULL)
	{
	}


	mesh::~mesh()
	{
		if (vertex != NULL)
			delete vertex;
		if (textureCord != NULL)
			delete textureCord;
		if (normal != NULL)
			delete normal;
		if (primitive != NULL)
			delete primitive;
	}

	void mesh::alloc()
	{
		vertex = new vec3[nbVertex];
		textureCord = new vec2[nbTextureCord];
		normal = new vec3[nbNormal];
		primitive = new vtxInfo[nbPrimitive * 3]; /* ! 3 TRIANGLE ONLY! */
	}
}