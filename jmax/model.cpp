#include <iostream>
#include "model.h"
#include "jmax.h"

namespace jmax
{
	model::model()
		: mesh(), material()
	{
		rotation[0] = 0;
		rotation[1] = 0;
		rotation[2] = 0;
		position[0] = 0;
		position[1] = 0;
		position[2] = 0;
		scale[0] = 1;
		scale[1] = 1;
		scale[2] = 1;
	}


	model::~model()
	{
	}

	void	model::render()
	{/*

		glPushMatrix();
		glTranslated(position[0], position[1], position[2]);
		glScaled(scale[0], scale[1], scale[2]);
		glRotated(rotation[2], 0.0, 0.0, 1.0);
		glRotated(rotation[1], 0.0, 1.0, 0.0);
		glRotated(rotation[0], 1.0, 0.0, 0.0);*/
		glBegin(GL_TRIANGLES);
		unsigned int i = 0;
		while (i < (mesh.nbPrimitive * 3))
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3d(mesh.vertex[mesh.primitive[i]][0], mesh.vertex[mesh.primitive[i]][1], mesh.vertex[mesh.primitive[i]][2]);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3d(mesh.vertex[mesh.primitive[i + 1]][0], mesh.vertex[mesh.primitive[i + 1]][1], mesh.vertex[mesh.primitive[i + 1]][2]);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3d(mesh.vertex[mesh.primitive[i + 2]][0], mesh.vertex[mesh.primitive[i + 2]][1], mesh.vertex[mesh.primitive[i + 2]][2]);
			i += 3;
		}
		glEnd();
		//glPopMatrix();
	}
}