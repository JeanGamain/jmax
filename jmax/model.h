#ifndef MODEL_H_
# define MODEL_H_

#include <list>
#include "material.h"
#include "mesh.h"

namespace jmax
{
	class model
	{
	public:
		model();
		virtual ~model();

	public:
		void				render();

		mesh				mesh;
		std::list<material>	material;

		double				position[3];
		double				rotation[3];
		double				scale[3];
	};
}

#endif /* !MODEL_H_ */