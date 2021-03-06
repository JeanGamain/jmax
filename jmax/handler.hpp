#ifndef HANDLER_HPP_
# define HANDLER_HPP_

#include "bind.hpp"

void hKey_Z(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my);
void hKey_S(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my);
void hKey_D(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my);
void hKey_Q(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my);
void hKey_UP(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my);
void hKey_DOWN(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my);
void hKey_LEFT(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my);
void hKey_RIGHT(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my);
void hKey_0(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my);
void hKey_1(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my);
void hKey_2(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my);
void hKey_3(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my);
void hKey_4(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my);
void hKey_5(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my);

#include <GLFW/glfw3.h>
void hKeyPress(GLFWwindow *window, int key, int scancode, int action, int mods);
void hResize(GLFWwindow *window, int w, int h);
void hRefresh(GLFWwindow *window);

#endif /* HANDLER_HPP_ */
