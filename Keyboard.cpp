/**
 * @file Keyboard.cpp
 * @brief Implementacja metod klasy Keyboard.
 */

#include "Keyboard.h"

 /**
  * @brief Funkcja zwrotna obs�uguj�ca wej�cie z klawiatury.
  *
  * Ta funkcja jest wywo�ywana, gdy klawisz klawiatury jest wci�ni�ty lub zwolniony.
  * Aktualizuje stan okre�lonego klawisza w klasie Keyboard.
  *
  * @param window Okno GLFW, kt�re otrzyma�o zdarzenie.
  * @param key Klawisz klawiatury, kt�ry zosta� wci�ni�ty lub zwolniony.
  * @param scancode Systemowy kod klawisza.
  * @param action Akcja, kt�ra zosta�a wykonana (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT).
  * @param mods Bitowa reprezentacja naci�ni�tych klawiszy modyfikuj�cych.
  */
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
