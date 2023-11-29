/**
 * @file Screen.cpp
 * @brief Implementacja metod klasy Screen.
 */

#include "Screen.h"

 /**
  * @brief Konstruktor klasy Screen.
  *
  * Inicjalizuje obiekt klasy Screen ustawiaj�c jego szeroko��, wysoko�� i tytu�.
  *
  * @param width Szeroko�� okna.
  * @param height Wysoko�� okna.
  * @param title Tytu� okna.
  */
Screen::Screen(int width, int height, std::string title) {
    this->width = width;
    this->height = height;
    this->title = title;
}

/**
 * @brief Inicjalizacja GLFW.
 *
 * Inicjalizuje bibliotek� GLFW. Ustawia odpowiednie atrybuty kontekstu OpenGL.
 *
 * @return Kod b��du, -1 w przypadku niepowodzenia.
 */
int Screen::glfw_init() {
    if (!glfwInit()) {
        std::cerr << "B��d podczas inicjalizacji GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ... brak zwracanej warto�ci
}

/**
 * @brief Inicjalizacja okna GLFW.
 *
 * Tworzy okno GLFW o zdefiniowanej szeroko�ci, wysoko�ci i tytule.
 *
 * @return Kod b��du, -1 w przypadku niepowodzenia.
 */
int Screen::window_init() {
    this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "B��d podczas tworzenia okna" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSwapInterval(1);

    glfwSetWindowSizeLimits(this->window, this->width, this->height, this->width, this->height);
    glfwMakeContextCurrent(window);

    // ... brak zwracanej warto�ci
}

/**
 * @brief Inicjalizacja biblioteki glad.
 *
 * Inicjalizuje bibliotek� glad, kt�ra obs�uguje za�adowanie wska�nik�w funkcji OpenGL.
 *
 * @return Kod b��du, -1 w przypadku niepowodzenia.
 */
int Screen::glad_init() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "B��d podczas inicjalizacji glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    // ... brak zwracanej warto�ci
}
