#ifndef JMAX_H_
# define JMAX_H_

# include "bind.h"

# include <GL\glew.h>
# include <GL\wglew.h>
# include <GL\glfw3.h>

# include "load.h"
# include "material.h"
# include "mesh.h"
# include "model.h"
# include "viewPort.h"
# include "fps.h"


# define	DEFAULT_FAR 10000
# define	DEFAULT_FOV 90.0
# define	JMAX_FONT NULL

namespace jmax
{
	class jmax
	{
	public:
		jmax(unsigned int width, unsigned int height);
		virtual ~jmax();

		void		render();
		void		mainLoop();

		// Static
		static void	drawText(int x, int y, void *font, char *str);

	public:
		viewPort			camera;
		GLFWwindow			*window;
		jmax::bind				binding;
	};
}

#endif /* !JMAX_H_ */