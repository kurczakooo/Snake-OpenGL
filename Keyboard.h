#pragma once
#include "Screen.h"
#include "Buttons.h"

class Keyboard 
{
public:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	struct Button keys[GLFW_KEY_LAST];

};


 extern Keyboard keyboard;