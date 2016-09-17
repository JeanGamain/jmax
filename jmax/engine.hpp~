#ifndef ENGINE_HPP_
# define ENGINE_HPP_

# include "bind.hpp"

# include <GL/glew.h>
# include <GLFW/glfw3.h>

# include "load.hpp"
# include "material.hpp"
# include "model.hpp"
# include "camera.hpp"


# define	DEFAULT_FAR 300
# define	DEFAULT_FOV 90.0
# define	JMAX_FONT NULL

namespace jmax
{
	class engine
	{
	public:
		engine(unsigned int width, unsigned int height);
		virtual ~engine();

		void		render();
		void		mainLoop();

		// Static
		static void	drawText(int x, int y, void *font, char *str);

	public:
		camera			view;
		GLFWwindow *		window;
		jmax::bind *		binding;
	};
}

#endif /* !JMAX_HPP_ */
