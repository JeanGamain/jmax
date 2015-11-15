#ifndef MATH_H_
# define MATH_H_

# define	RAD(a) (M_PI * (a) / 180)
# define	ABS(a) ((a < 0) ? (-a) : (a))
# define	CIRCULAR(nb, max, val, mod) ((mod) ? (((max - nb) < val) ? (val - (max - nb)) : (nb + val)) : ((nb < val) ? (max - (val - nb)) : (nb - val)))

typedef double vec4[4]; /* ! glm? */
typedef double vec3[3];
typedef double vec2[2];
typedef unsigned int idx3d;

inline float dot(double v[3], double p[3]);
double		veclenght(double a[3], double b[3]);
double		norme(double a[3]);
void		rotate(vec3 vec, vec3 angle);
void		rotate_cordinate(double var[3], double tmpsin[3], double tmpcos[3]);

#endif /* MATH_H_ */