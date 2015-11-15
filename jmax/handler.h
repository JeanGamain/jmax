#ifndef HANDLER_H_
# define HANDLER_H_

#include "bind.h"

void hKey_Z(unsigned int tick, bind *binding, bind::bindValue *my);
void hKey_S(unsigned int tick, bind *binding, bind::bindValue *my);
void hKey_D(unsigned int tick, bind *binding, bind::bindValue *my);
void hKey_Q(unsigned int tick, bind *binding, bind::bindValue *my);
void hKey_UP(unsigned int tick, bind *binding, bind::bindValue *my);
void hKey_DOWN(unsigned int tick, bind *binding, bind::bindValue *my);
void hKey_LEFT(unsigned int tick, bind *binding, bind::bindValue *my);
void hKey_RIGHT(unsigned int tick, bind *binding, bind::bindValue *my);
void hKey_0(unsigned int tick, bind *binding, bind::bindValue *my);
void hKey_1(unsigned int tick, bind *binding, bind::bindValue *my);
void hKey_2(unsigned int tick, bind *binding, bind::bindValue *my);
void hKey_3(unsigned int tick, bind *binding, bind::bindValue *my);
void hKey_4(unsigned int tick, bind *binding, bind::bindValue *my);
void hKey_5(unsigned int tick, bind *binding, bind::bindValue *my);

#include <GL/glfw3.h>
void hKeyPress(GLFWwindow *window, int key, int scancode, int action, int mods);
void hResize(GLFWwindow *window, int w, int h);
void hRefresh(GLFWwindow *window);

#endif /* HANDLER_H_ */