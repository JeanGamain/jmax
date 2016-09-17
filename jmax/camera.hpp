#ifndef camera_HPP_
# define camera_HPP_

#include "math.hpp"

namespace jmax
{
	class camera
	{
	public:
		camera(){};
		camera(float fov, unsigned int width, unsigned int height, float far);
		virtual  ~camera();

	public:
		unsigned int	width;
		unsigned int	height;
		float			ratio;
		float			fov;
		vec3			rotation;
		vec3			tmpsin;
		vec3			tmpcos;
		vec3			normal;
		vec3			position;
		float			frustum[6];

		void			resize(unsigned int x, unsigned int y);
		void			setProjection();
		void			setModelview();
		float			getNear();
		float			getFar();
	};
}

#endif /* !camera_HPP_ */