#include <stddef.h>
#include "mesh.h"

namespace jmax
{
	mesh::mesh()
		: nbPrimitive(0), primitive(NULL),
	{
	}


	mesh::~mesh()
	{
		if (primitive != NULL)
			delete primitive;
	}

	void mesh::alloc()
	{
		primitive = new mesh::vertex[nbPrimitive];
	}
}