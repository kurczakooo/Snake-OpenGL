#pragma once
#include "Screen.h"
#include "Buttons.h"

class Mouse : public Screen
{
public:
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

extern Mouse mouse;