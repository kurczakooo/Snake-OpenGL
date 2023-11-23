#include "Screen.h"

Screen::Screen(int width, int height, std::string title) {
    this->width = width;
    this->height = height;
    this->title = title;
}

//inicjalizuje glfw
int Screen::glfw_init() {
    if (!glfwInit()) {
        std::cerr << "Error initializing glfw" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

//tworzy okno
int Screen::window_init() {            
    this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Error with creating the Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSwapInterval(1);

    glfwSetWindowSizeLimits(this->window, this->width, this->height, this->width, this->height);
    //ustawia ze kazdy kontent bedzie sie wyswietlac w tutaj stworzonym oknie przechowywanym w klasie screen
    glfwMakeContextCurrent(window);
}

//inicjalizuje glad
int Screen::glad_init() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Error initializing glad" << std::endl;
        glfwTerminate();
        return -1;
    }
}