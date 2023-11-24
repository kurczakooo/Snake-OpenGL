#include "Keyboard.h"


void Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    if (key < 0)
        return;

    switch (action)
    {
    case GLFW_PRESS:
        keyboard.keys[key].down = GL_TRUE;
        break;
    case GLFW_RELEASE:
        keyboard.keys[key].down = GL_FALSE;
        break;
    default:
        break;
    }

}