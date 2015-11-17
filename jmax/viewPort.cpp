#define _USE_MATH_DEFINES
#include <cmath>
#include "jmax.h"
#include "viewPort.h"

namespace jmax
{
	viewPort::viewPort(float v, unsigned int x, unsigned int y, float f)
		:width(width), height(height),
		ratio(static_cast<float>(x) / static_cast<float>(y)), fov(v)
	{
		rotation[0] = 0;
		rotation[1] = 0;
		rotation[2] = 0;
		position[0] = 0;
		position[1] = 0;
		position[2] = 0;
		frustum[3] = static_cast<float>(tan(fov / 360 * M_PI));
		frustum[2] = -frustum[3];
		frustum[1] = frustum[3] * ratio;
		frustum[0] = -frustum[1];
		frustum[4] = 0;
		frustum[5] = f;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(frustum[0], frustum[1],
			frustum[2], frustum[3],
			frustum[4], frustum[5]);
	}

	viewPort::~viewPort()
	{
	}
}
