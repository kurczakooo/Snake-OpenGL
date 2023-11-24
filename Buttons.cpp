#include "Buttons.h"

void Button::_button_array_update(struct Button* buttons)
{
    for (int i = 0; i < GLFW_KEY_LAST; i++)
    {
        buttons[i].pressed = buttons[i].down && !buttons[i].last;
        buttons[i].last = buttons[i].down;
    }
}