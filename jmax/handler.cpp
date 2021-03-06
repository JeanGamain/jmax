#include <iostream>
#include "bind.hpp"
#include "math.hpp"
#include "engine.hpp"

extern jmax::engine	*myRender;

void hKeyPress(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	std::map<int, jmax::bind::bindValue>::iterator val = myRender->binding->binding.find(key);

	if (val != myRender->binding->binding.end())
	{
		if (val->second.value == GLFW_RELEASE && action == GLFW_PRESS)
			val->second.status = !val->second.status;
		val->second.value = action;
		(reinterpret_cast<jmax::bind::bindFunct>(val->second.funct))((unsigned int)(glfwGetTime() * 1000000), myRender->binding, &val->second);
	}
}

void hResize(GLFWwindow *window, int w, int h)
{
	if (h == 0)
		h = 1;
	glfwGetFramebufferSize(window, &w, &h);
	myRender->view.resize(w, h);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void hRefresh(GLFWwindow *window)
{
	myRender->render();
}

void hKey_Z(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my)
{
	if (my->value == GLFW_RELEASE)
		my->active = 0;
	else if ((*binding)[GLFW_KEY_S].value == GLFW_RELEASE)
	{
		my->active = 1;
		vec3 bra = { 0.0, 0.0, 0.0000003 * tick };
		bra.rotateByCache(myRender->view.tmpsin, myRender->view.tmpcos);

		myRender->view.position[0] += bra.x;
		myRender->view.position[1] += bra.y;
		myRender->view.position[2] += bra.z;
	}
}

void hKey_S(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my)
{
	if (my->value == GLFW_RELEASE)
		my->active = 0;
	else if ((*binding)[GLFW_KEY_Z].value == GLFW_RELEASE)
	{
		my->active = 1;
		vec3 bra = { 0.0, 0.0, -0.0000003 * tick };
		bra.rotateByCache(myRender->view.tmpsin, myRender->view.tmpcos);
		myRender->view.position[0] += bra.x;
		myRender->view.position[1] += bra.y;
		myRender->view.position[2] += bra.z;
	}
}

void hKey_D(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my)
{
	if (my->value == GLFW_RELEASE)
		my->active = 0;
	else if ((*binding)[GLFW_KEY_Q].value == GLFW_RELEASE)
	{
		my->active = 1;
		vec3 bra = { -0.0000003 * tick, 0.0, 0.0 };
		bra.rotateByCache(myRender->view.tmpsin, myRender->view.tmpcos);
		myRender->view.position[0] += bra.x;
		myRender->view.position[1] += bra.y;
		myRender->view.position[2] += bra.z;
	}
}

void hKey_Q(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my)
{
	if (my->value == GLFW_RELEASE)
		my->active = 0;
	else if ((*binding)[GLFW_KEY_S].value == GLFW_RELEASE)
	{
		my->active = 1;
		vec3 bra = { 0.0000003 * tick, 0.0, 0.0 };
		bra.rotateByCache(myRender->view.tmpsin, myRender->view.tmpcos);
		myRender->view.position[0] += bra.x;
		myRender->view.position[1] += bra.y;
		myRender->view.position[2] += bra.z;
	}
}

void hKey_UP(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my)
{
	if (my->value == GLFW_RELEASE)
		my->active = 0;
	else if ((*binding)[GLFW_KEY_DOWN].value == GLFW_RELEASE)
	{
		my->active = 1;
		myRender->view.rotation.x = CIRCULAR_ADD(myRender->view.rotation.x, 360.0, 2);
		myRender->view.tmpcos.x = cos(RAD(myRender->view.rotation.x));
		myRender->view.tmpsin.x = sin(RAD(myRender->view.rotation.x));
	}
}

void hKey_DOWN(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my)
{
	if (my->value == GLFW_RELEASE)
		my->active = 0;
	else if ((*binding)[GLFW_KEY_UP].value == GLFW_RELEASE)
	{
		my->active = 1;
		myRender->view.rotation.x = CIRCULAR_SUB(myRender->view.rotation.x, 360.0, 2);
		myRender->view.tmpcos.x = cos(RAD(myRender->view.rotation.x));
		myRender->view.tmpsin.x = sin(RAD(myRender->view.rotation.x));
	}
}

void hKey_LEFT(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my)
{
	if (my->value == GLFW_RELEASE)
		my->active = 0;
	else if ((*binding)[GLFW_KEY_RIGHT].value == GLFW_RELEASE)
	{
		my->active = 1;
		myRender->view.rotation.y = CIRCULAR_ADD(myRender->view.rotation.y, 360.0, 2);
		myRender->view.tmpcos.y = cos(RAD(myRender->view.rotation.y));
		myRender->view.tmpsin.y = sin(RAD(myRender->view.rotation.y));
	}
}

void hKey_RIGHT(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my)
{
	if (my->value == GLFW_RELEASE)
		my->active = 0;
	else if ((*binding)[GLFW_KEY_LEFT].value == GLFW_RELEASE)
	{
		my->active = 1;
		myRender->view.rotation.y = CIRCULAR_SUB(myRender->view.rotation.y, 360.0, 2);
		myRender->view.tmpcos.y = cos(RAD(myRender->view.rotation.y));
		myRender->view.tmpsin.y = sin(RAD(myRender->view.rotation.y));
	}
}

void hKey_0(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my)
{
	if (my->value == GLFW_RELEASE)
		my->active = 0;
	else
	{
		my->active = 1;

	}
}

void hKey_1(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my)
{

}

void hKey_2(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my)
{

}

void hKey_3(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my)
{

}

void hKey_4(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my)
{

}

void hKey_5(unsigned int tick, jmax::bind *binding, jmax::bind::bindValue *my)
{

}

/*
//select = bra;

if (binding[].value) // ratio++
m_step += 0.1;

// 3d Editition
if (keybind[2][9] || keybind[2][11]) // select next object
{
select = select->next;
if (select == NULL)
select = map;
}
if (keybind[2][10]) // next edition mode
edition_mode = (edition_mode + 1) % 10;
if (keybind[1][12] != keybind[1][13]) // + or -
{
if (edition_mode < 3)
select->object->position[edition_mode] += (keybind[1][12]) ? 0.1 : -0.1;
else if (edition_mode < 6)
select->object->rotation[edition_mode - 3] =
CIRCULAR(select->object->rotation[edition_mode - 3], 360.0
, r_step, keybind[1][12]);
else if (edition_mode < 9)
select->object->scale[edition_mode - 6] += (keybind[1][12]) ? -0.1 : 0.1;
else if (edition_mode == 9)
{
select->object->scale[0] += (keybind[1][12]) ? -0.1 : 0.1;
select->object->scale[1] += (keybind[1][12]) ? -0.1 : 0.1;
select->object->scale[2] += (keybind[1][12]) ? -0.1 : 0.1;
}
//calcBoundingBox(select->object);
}

// Cam rotation
if ((keybind[1][4] != keybind[1][5]) ||
(keybind[1][6] != keybind[1][7]))
{
if (keybind[1][4] || keybind[1][5])
rotate[1] = CIRCULAR(rotate[1], 360.0, r_step, keybind[1][5]);
else
rotate[0] = CIRCULAR(rotate[0], 360.0, r_step, keybind[1][7]);
tmpcos[0] = cos(M_PI * rotate[0] / 180);
tmpcos[1] = cos(M_PI * rotate[1] / 180);
tmpcos[2] = cos(M_PI * rotate[2] / 180);
tmpsin[0] = sin(M_PI * rotate[0] / 180);
tmpsin[1] = sin(M_PI * rotate[1] / 180);
tmpsin[2] = sin(M_PI * rotate[2] / 180);
}

// Cam translation
if ((binding[GLFW_KEY_Z].value != binding[GLFW_KEY_S].value) ||
(binding[GLFW_KEY_Q].value != binding[GLFW_KEY_D].value))
{
float move[3];
move[0] = 0;
move[1] = 0;
move[2] = 0;
if (binding[GLFW_KEY_Z].value)
move[0] = m_step;
else if (binding[GLFW_KEY_S].value)
move[0] = -m_step;
if (binding[GLFW_KEY_Q].value)
move[2] = m_step;
else if (binding[GLFW_KEY_D].value)
move[2] = -m_step;
rotate_cordinate(move, tmpsin, tmpcos);
pos[0] += move[0];
pos[1] += move[1];
pos[2] += move[2];
}*/
