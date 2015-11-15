#include <iostream>
#include "jmax.h"
#include "handler.h"

jmax	*engine = NULL;

void jmax::render()
{
	static fps fpsCounter(100);
	static model *bra = load::Model("Z:/Save/tek3/3d/off/geometry/cone.off");
	
	fpsCounter.timeFrame();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(360 - camera.rotation[0], 1.0, 0.0, 0.0);
	glRotated(360 - camera.rotation[1], 0.0, 1.0, 0.0);
	glRotated(360 - camera.rotation[2], 0.0, 0.0, 1.0);
	glTranslated(camera.position[0], camera.position[1], camera.position[2]);
	bra->render();
	glPopAttrib();
	//jmax::drawText(2, 2, JMAX_FONT, fpsCounter.getFps());

	glfwSwapBuffers(window);
	glfwPollEvents();
	binding.runActive();
	glfwSetTime(0);
}

void jmax::mainLoop()
{
	unsigned int	edition_mode = 9;

	glfwSetTime(0);
	while (!glfwWindowShouldClose(window))
		render();
}

void jmax::drawText(int , int , void *, char *str)
{
	std::cout << "FPS: " << str << std::endl;
}

jmax::jmax(unsigned int width, unsigned int height)
	: binding(
{
	{ GLFW_KEY_W, &hKey_Z },
	{ GLFW_KEY_S, &hKey_S },
	{ GLFW_KEY_A, &hKey_Q },
	{ GLFW_KEY_D, &hKey_D },
	{ GLFW_KEY_UP, &hKey_UP },
	{ GLFW_KEY_DOWN, &hKey_DOWN },
	{ GLFW_KEY_LEFT, &hKey_LEFT },
	{ GLFW_KEY_RIGHT, &hKey_RIGHT },
	{ GLFW_KEY_0, &hKey_0 },
	{ GLFW_KEY_1, &hKey_1 },
	{ GLFW_KEY_2, &hKey_2 },
	{ GLFW_KEY_3, &hKey_3 },
	{ GLFW_KEY_4, &hKey_4 },
	{ GLFW_KEY_5, &hKey_5 }
})
{
	engine = this;
	
	if (!glfwInit())
		std::cerr << "glfwInit failed" << std::endl;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	camera = viewPort(DEFAULT_FOV, width, height, DEFAULT_FAR);
	/* Enable smooth shading */
	glShadeModel(GL_SMOOTH);

	/* Set the background black */
	glClearColor(0, 0, 0, 0);

	/* Depth buffer setup */
	glClearDepth(1000.0f);
	glEnable(GL_NORMALIZE);
	
	/* The Type Of Depth Test To Do */
	//glDepthFunc(GL_LEQUAL);

	/* Really Nice Perspective Calculations */
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	if (!(window = glfwCreateWindow(800, 800, "JMAX", NULL, NULL))) //mode
		std::cerr << "glfwInit failed" << std::endl;
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, hResize);
	//glfwSetWindowRefreshCallback(window, hRefresh);
	glfwSetKeyCallback(window, hKeyPress);

	if (glewInit() != GLEW_OK)
		std::cerr << "GLEW error" << std::endl;

	std::cout
		<< "Render: " << glGetString(GL_RENDERER) << std::endl
		<< "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	//camera = viewPort(DEFAULT_FOV, width, height, DEFAULT_FAR);

	mainLoop();
}

jmax::~jmax()
{
	glfwTerminate();
}