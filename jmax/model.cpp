#include <iostream>
#include "model.hpp"
#include "engine.hpp"

namespace jmax
{
	model::model()
		: _mesh(), _material(), _renderMap(),
		position(), rotation(), scale{1, 1, 1}
	{
	}


	model::~model()
	{
	}

	void	model::render()
	{
		const double color[3][3] =
		{
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f }
		};
		
		glPushMatrix();
		setModelview();
		glBegin(GL_TRIANGLES);
		std::list<materialAssoc>::const_iterator materialIdx = _renderMap.begin();
		idx3d k = 0;
		for (std::list<mesh>::const_iterator i = _mesh.begin(); i != _mesh.end();)
		{
			if (materialIdx != _renderMap.end())
			{
				if (k == (*materialIdx).startIndex)
				{
					(*materialIdx).material->setup();
					materialIdx++;
				}
			}

			//glBegin(GL_LINE_STRIP);
			for (unsigned char j = 0; j < 3 && i != _mesh.end(); j++)
			{
				//glColor3dv(color[j]);
				glVertex3dv(&i->vertex.x);
				glNormal3dv(&i->normal.x);
				glTexCoord2dv(&i->texture.x);
				i++;
			}
			//glEnd();
			k++;
		}
		glEnd();
		glPopMatrix();
	}

	void	model::setModelview()
	{
		glTranslated(position.x, position.y, position.z);
		glScaled(scale.x, scale.y, scale.z);
		glRotated(rotation.x, 0.0, 0.0, 1.0);
		glRotated(rotation.y, 0.0, 1.0, 0.0);
		glRotated(rotation.z, 1.0, 0.0, 0.0);
	}
}