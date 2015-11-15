#include <stddef.h>
#include "mesh.h"

mesh::mesh()
	: nbVertex(0), vertex(NULL), nbTextureCord(0), textureCord(NULL),
	  nbNormal(0), normal(NULL), nbPrimitive(0), primitive(NULL)
{
}


mesh::~mesh()
{
}
