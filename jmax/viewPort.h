#ifndef VIEWPORT_H_
# define VIEWPORT_H_

class viewPort
{
public:
	viewPort(){};
	viewPort(float fov, unsigned int width, unsigned int height, float far);
	virtual  ~viewPort();

public:
	unsigned int	width;
	unsigned int	height;
	float			ratio;
	float			fov;
	float			frustum[6];
	double			rotation[3];
	double			position[3];
};

#endif /* !VIEWPORT_H_ */