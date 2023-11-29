/**
 * @file Keyboard.cpp
 * @brief Implementacja metod klasy Keyboard.
 */

#include "Keyboard.h"

 /**
  * @brief Funkcja zwrotna obs³uguj¹ca wejœcie z klawiatury.
  *
  * Ta funkcja jest wywo³ywana, gdy klawisz klawiatury jest wciœniêty lub zwolniony.
  * Aktualizuje stan okreœlonego klawisza w klasie Keyboard.
  *
  * @param window Okno GLFW, które otrzyma³o zdarzenie.
  * @param key Klawisz klawiatury, który zosta³ wciœniêty lub zwolniony.
  * @param scancode Systemowy kod klawisza.
  * @param action Akcja, która zosta³a wykonana (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT).
  * @param mods Bitowa reprezentacja naciœniêtych klawiszy modyfikuj¹cych.
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
