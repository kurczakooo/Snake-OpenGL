/**
 * @file Screen.cpp
 * @brief Implementacja metod klasy Screen.
 */

#include "Screen.h"

 /**
  * @brief Konstruktor klasy Screen.
  *
  * Inicjalizuje obiekt klasy Screen ustawiaj¹c jego szerokoœæ, wysokoœæ i tytu³.
  *
  * @param width Szerokoœæ okna.
  * @param height Wysokoœæ okna.
  * @param title Tytu³ okna.
  */
Screen::Screen(int width, int height, std::string title) {
    this->width = width;
    this->height = height;
    this->title = title;
}

/**
 * @brief Inicjalizacja GLFW.
 *
 * Inicjalizuje bibliotekê GLFW. Ustawia odpowiednie atrybuty kontekstu OpenGL.
 *
 * @return Kod b³êdu, -1 w przypadku niepowodzenia.
 */
int Screen::glfw_init() {
    if (!glfwInit()) {
        std::cerr << "B³¹d podczas inicjalizacji GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ... brak zwracanej wartoœci
}

/**
 * @brief Inicjalizacja okna GLFW.
 *
 * Tworzy okno GLFW o zdefiniowanej szerokoœci, wysokoœci i tytule.
 *
 * @return Kod b³êdu, -1 w przypadku niepowodzenia.
 */
int Screen::window_init() {
    this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "B³¹d podczas tworzenia okna" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSwapInterval(1);

    glfwSetWindowSizeLimits(this->window, this->width, this->height, this->width, this->height);
    glfwMakeContextCurrent(window);

    // ... brak zwracanej wartoœci
}

/**
 * @brief Inicjalizacja biblioteki glad.
 *
 * Inicjalizuje bibliotekê glad, która obs³uguje za³adowanie wskaŸników funkcji OpenGL.
 *
 * @return Kod b³êdu, -1 w przypadku niepowodzenia.
 */
int Screen::glad_init() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "B³¹d podczas inicjalizacji glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    // ... brak zwracanej wartoœci
}
