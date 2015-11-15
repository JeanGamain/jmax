#include <iostream>
#include <GL/glfw3.h>
#include "bind.h"

bind::bind(std::map<int, bindValue> b)
	: binding(b)
{
}

void bind::runActive()
{
	for (std::map<int, bindValue>::iterator i = binding.begin(); i != binding.end(); i++)
		if (i->second.active)
			(static_cast<bind::bindFunct>(i->second.funct))(unsigned int(glfwGetTime() * 1000000), this, &i->second);
}

void bind::addBind(int newkey)
{
	binding[newkey] = bindValue();
}