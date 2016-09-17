#define _USE_MATH_DEFINES
#include "math.hpp"
#include "engine.hpp"
#include "camera.hpp"

namespace jmax
{
	camera::camera(float v, unsigned int x, unsigned int y, float f)
		: width(x), height(y), ratio(static_cast<float>(x) / static_cast<float>(y)),
		fov(v), rotation(),
		tmpsin{ sin(rotation.x), sin(rotation.y), sin(rotation.z) },
		tmpcos{ cos(rotation.x), cos(rotation.y), cos(rotation.z) },
		normal(), position()
	{
		frustum[4] = 0.1f;
		frustum[5] = f;
		frustum[3] = tanf(fov / 360.0f * static_cast<float>(M_PI)) * frustum[4];
		frustum[2] = -frustum[3];
		frustum[1] = frustum[3] * ratio;
		frustum[0] = -frustum[1];
	}

	camera::~camera()
	{
	}

	void			camera::resize(unsigned int x, unsigned int y)
	{
		width = x;
		height = y;
		ratio = static_cast<float>(x) / static_cast<float>(y);
		frustum[1] = frustum[3] * ratio;
		setProjection();
	}

	void			camera::setProjection()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(frustum[0], frustum[1],
				  frustum[2], frustum[3],
				  frustum[4], frustum[5]);

	}

	void			camera::setModelview()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotated(360 - rotation.x, 1.0, 0.0, 0.0);
		glRotated(360 - rotation.y, 0.0, 1.0, 0.0);
		glRotated(360 - rotation.z, 0.0, 0.0, 1.0);
		glTranslated(position.x, position.y, position.z);
	}

	float			camera::getNear()
	{
		return frustum[5];
	}

	float			camera::getFar()
	{
		return frustum[5];
	}
}
