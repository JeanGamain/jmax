#include <iostream>
#include <map>
#include <utility>
#include "engine.hpp"
#include "handler.hpp"

jmax::engine * myRender = NULL;

namespace jmax
{

  void engine::render()
  {
    //static model *bra = load::Model("Z:/Save/tek3/3d/ak47/ak47.obj");
    //static model *bra = load::Model("Z:/Save/tek3/3d/lego/LEGO_Man.obj");

    //static model *bra = load::Model("/media/jean/1ECC85FCCC85CF09/epitech/gamain_j/3d/lego/lego.obj");
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    view.setModelview();
    if (modelFile != NULL)
      modelFile->render();
    glPopAttrib();

    glfwSwapBuffers(window);
    glfwPollEvents();
    binding->runActive();
    glfwSetTime(0);
  }
  
  void engine::mainLoop()
  {
    //		unsigned int	edition_mode = 9;
    
    glfwSetTime(0);
    while (!glfwWindowShouldClose(window))
      render();
  }
  
  engine::engine(unsigned int width, unsigned int height, char * modelPath)
    : modelFile(NULL)
  {
    std::map<int, jmax::bind::bindValue> b;
    b.insert(std::pair<int, jmax::bind::bindValue>(GLFW_KEY_W, jmax::bind::bindValue((void*)&hKey_Z)));
    b.insert(std::pair<int, jmax::bind::bindValue>(GLFW_KEY_S, jmax::bind::bindValue((void*)&hKey_S)));
    b.insert(std::pair<int, jmax::bind::bindValue>(GLFW_KEY_A, jmax::bind::bindValue((void*)&hKey_Q)));
    b.insert(std::pair<int, jmax::bind::bindValue>(GLFW_KEY_D, jmax::bind::bindValue((void*)&hKey_D)));
    b.insert(std::pair<int, jmax::bind::bindValue>(GLFW_KEY_UP, jmax::bind::bindValue((void*)&hKey_UP)));
    b.insert(std::pair<int, jmax::bind::bindValue>(GLFW_KEY_DOWN, jmax::bind::bindValue((void*)&hKey_DOWN)));
    b.insert(std::pair<int, jmax::bind::bindValue>(GLFW_KEY_LEFT, jmax::bind::bindValue((void*)&hKey_LEFT)));
    b.insert(std::pair<int, jmax::bind::bindValue>(GLFW_KEY_RIGHT, jmax::bind::bindValue((void*)&hKey_RIGHT)));
    b.insert(std::pair<int, jmax::bind::bindValue>(GLFW_KEY_0, jmax::bind::bindValue((void*)&hKey_0)));
    b.insert(std::pair<int, jmax::bind::bindValue>(GLFW_KEY_1, jmax::bind::bindValue((void*)&hKey_1)));
    b.insert(std::pair<int, jmax::bind::bindValue>(GLFW_KEY_2, jmax::bind::bindValue((void*)&hKey_2)));
    b.insert(std::pair<int, jmax::bind::bindValue>(GLFW_KEY_3, jmax::bind::bindValue((void*)&hKey_3)));
    b.insert(std::pair<int, jmax::bind::bindValue>(GLFW_KEY_4, jmax::bind::bindValue((void*)&hKey_4)));
    b.insert(std::pair<int, jmax::bind::bindValue>(GLFW_KEY_5, jmax::bind::bindValue((void*)&hKey_5)));
    binding = new jmax::bind(b);

    myRender = this;
    
    if (!glfwInit())
      std::cerr << "glfwInit failed" << std::endl;
    
    if (!(window = glfwCreateWindow(800, 800, "JMAX", NULL, NULL))) //mode
	    std::cerr << "glfwInit failed" << std::endl;
    glfwMakeContextCurrent(window);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_BUFFER_BIT);
    
    glShadeModel(GL_SMOOTH);
    
    glClearColor(0, 0, 0, 0);
    
    glEnable(GL_NORMALIZE);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_TEXTURE_2D);
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glfwSetWindowSizeCallback(window, hResize);
    //glfwSetWindowRefreshCallback(window, hRefresh);
    glfwSetKeyCallback(window, hKeyPress);
	  
    std::cout
      << "Render: " << glGetString(GL_RENDERER) << std::endl
      << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    glClearDepth(DEFAULT_FAR);
    view = camera(DEFAULT_FOV, width, height, DEFAULT_FAR);
    view.setProjection();
    modelFile = jmax::load::Model(modelPath);
    mainLoop();
  }
  
  engine::~engine()
  {
    glfwTerminate();
  }
}
