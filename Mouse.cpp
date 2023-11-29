#include "Mouse.h"
#include "Keyboard.h"


void Mouse::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS)
			keyboard.keys[GLFW_KEY_RIGHT].down = GL_TRUE;
		if (action == GLFW_RELEASE)
			keyboard.keys[GLFW_KEY_RIGHT].down = GL_FALSE;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS)
			keyboard.keys[GLFW_KEY_LEFT].down = GL_TRUE;
		if (action == GLFW_RELEASE)
			keyboard.keys[GLFW_KEY_LEFT].down = GL_FALSE;
	}
	else if (button == GLFW_MOUSE_BUTTON_5) {
		if (action == GLFW_PRESS)
			keyboard.keys[GLFW_KEY_UP].down = GL_TRUE;
		if (action == GLFW_RELEASE)
			keyboard.keys[GLFW_KEY_UP].down = GL_FALSE;
	}
	else if (button == GLFW_MOUSE_BUTTON_4) {
		if (action == GLFW_PRESS)
			keyboard.keys[GLFW_KEY_DOWN].down = GL_TRUE;
		if (action == GLFW_RELEASE)
			keyboard.keys[GLFW_KEY_DOWN].down = GL_FALSE;
	}

}