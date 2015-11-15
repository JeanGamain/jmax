#define _USE_MATH_DEFINES
#include <cmath>
#include "math.h"

inline float dot(vec3 v, vec3 p)
{
	return (v[0] * p[0] + v[1] * p[1] + v[2] * p[2]);
}

double		veclenght(vec3 a, vec3 b)
{
	return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2) + pow(a[2] - b[2], 2));
}

double		norme(vec3 a)
{
	return (sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]));
}

void		rotate(vec3 vec, vec3 angle)
{
	vec3	radangle = { RAD(angle[0]), RAD(angle[1]), RAD(angle[2]) };
	vec3	tmpsin = { sin(radangle[0]), sin(radangle[1]), sin(radangle[2]) };
	vec3	tmpcos = { cos(radangle[0]), cos(radangle[1]), cos(radangle[2]) };
	rotate_cordinate(vec, tmpsin, tmpcos);
}

void		rotate_cordinate(vec3 var, vec3 tmpsin, vec3 tmpcos)
{
	double	save[3];

	save[0] = var[0];
	save[1] = var[1];
	save[2] = var[2];
	var[0] = (save[0] * (tmpcos[1] * tmpcos[2])
		+ save[1] * (-tmpcos[0] * tmpsin[2]
		+ tmpsin[0] * tmpsin[1] * tmpcos[2])
		+ save[2] * (tmpsin[0] * tmpsin[2]
		+ tmpcos[0] * tmpsin[1] * tmpcos[2]));
	var[1] = (save[0] * (tmpcos[1] * tmpsin[2])
		+ save[1] * (tmpcos[0] * tmpcos[2]
		+ tmpsin[0] * tmpsin[1] * tmpsin[2])
		+ save[2] * (-tmpsin[0] * tmpcos[2]
		+ tmpcos[0] * tmpsin[1] * tmpsin[2]));
	var[2] = (save[0] * (-tmpsin[1])
		+ save[1] * (tmpsin[0] * tmpcos[1])
		+ save[2] * (tmpcos[0] * tmpcos[1]));
}