#pragma once
#include "Screen.h"


#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800

#define MAP_WIDTH 8
#define MAP_HEIGHT 8

#define SPEED 4 // Snake speed


class Snake
{
public:
    GLuint counter;
    GLuint positions[MAP_WIDTH * MAP_HEIGHT];
    GLuint direction;
    GLuint food_position;

    GLuint random_position(void);
    void snake_logic(void);
    void key_functions(GLFWwindow* window, GLuint shaderID, GLuint texture, float vertices[]);
    void _button_array_update(struct Button* buttons);
};

extern Snake snake;
extern GLdouble TIME_NOW, TIME_LAST, TIME_DELTA, TIME_SUM;