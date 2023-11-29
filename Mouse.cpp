/**
 * @file Mouse.cpp
 * @brief Implementacja metod klasy Mouse.
 */

#include "Mouse.h"
#include "Keyboard.h"

 /**
  * @brief Funkcja zwrotna obs�uguj�ca przycisk myszy.
  *
  * Ta funkcja jest wywo�ywana, gdy przycisk myszy jest wci�ni�ty lub zwolniony.
  * Aktualizuje stan odpowiadaj�cego klawisza na klawiaturze w klasie Keyboard.
  *
  * @param window Okno GLFW, kt�re otrzyma�o zdarzenie.
  * @param button Przycisk myszy, kt�ry zosta� wci�ni�ty lub zwolniony.
  * @param action Akcja, kt�ra zosta�a wykonana (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT).
  * @param mods Bitowa reprezentacja naci�ni�tych klawiszy modyfikuj�cych.
  */
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
