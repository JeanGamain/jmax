#include <iostream>
#include <GLFW/glfw3.h>
#include "bind.hpp"

jmax::bind::bind(std::map<int, bindValue> b)
	: binding(b)
{
}

void jmax::bind::runActive()
{
	for (std::map<int, bindValue>::iterator i = binding.begin(); i != binding.end(); i++)
		if (i->second.active)
		  (reinterpret_cast<bind::bindFunct>(i->second.funct))((unsigned int)(glfwGetTime() * 1000000), this, &i->second);
}

void jmax::bind::addBind(int newkey)
{
	binding[newkey] = bindValue();
}
