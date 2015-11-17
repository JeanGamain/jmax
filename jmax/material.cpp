#include "material.h"

namespace jmax
{
	material::material()
		: transparency(0), reflexion(0),
		map_Ka(0), map_Kd(0), map_Ks(0), map_bump(0)
	{
		ambient.integer = 255;
		diffuse.integer = 255;
		specular.integer = 255;

	}


	material::~material()
	{
	}
}
