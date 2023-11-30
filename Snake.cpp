/**
 * @file Snake.cpp
 * @brief Implementacja metod klasy Snake.
 */

#include "Snake.h"
#include "Directions.h"
#include "Buttons.h"
#include "Keyboard.h"

 /**
  * @brief Aktualizuje stan przycisków.
  *
  * @param buttons Tablica przycisków do zaktualizowania.
  */
void Snake::_button_array_update(struct Button* buttons) {
    for (int i = 0; i < GLFW_KEY_LAST; i++) {
        buttons[i].pressed = buttons[i].down && !buttons[i].last;
        buttons[i].last = buttons[i].down;
    }
}

/**
 * @brief Generuje losow¹ pozycjê na planszy.
 *
 * @return Losowa pozycja.
 */
GLuint Snake::random_position(void) {
    GLuint RND = static_cast<GLuint>(rand() % (MAP_WIDTH * MAP_HEIGHT));
    GLboolean free_position;
    do {
        free_position = GL_TRUE;
        for (GLuint i = 0; i < snake.counter; i++) {
            if (snake.positions[i] == RND) {
                free_position = GL_FALSE;
                RND++;
                if (RND >= (MAP_WIDTH * MAP_HEIGHT))
                    RND %= (MAP_WIDTH * MAP_HEIGHT);
            }
        }
    } while (!free_position);
    return RND;
}

/**
 * @brief Logika gry wê¿a.
 *
 * Sprawdza kolizje, aktualizuje pozycjê wê¿a, sprawdza czy zjedzono jedzenie.
 */
void Snake::snake_logic(void) {
    // if PAUSE -> do nothing
    if (snake.direction & PAUSE)
        return;

    // check wall hit
    if ((snake.positions[0] % MAP_WIDTH == 0 && snake.direction == LEFT) || (snake.positions[0] % MAP_WIDTH == MAP_WIDTH - 1 && snake.direction == RIGHT) ||
        (snake.positions[0] / MAP_WIDTH == 0 && snake.direction == UP) || (snake.positions[0] / MAP_WIDTH == MAP_HEIGHT - 1 && snake.direction == DOWN)) 
    {
        snake.counter = 1;
        snake.direction = PAUSE;
        return;
    }

    // ELSE
    GLuint _last_snake_head_position = snake.positions[0];
    GLuint _last_snake_length = snake.counter;

    // update snake_head_position
    if (snake.direction == LEFT) snake.positions[0] -= 1;
    else if (snake.direction == RIGHT) snake.positions[0] += 1;
    else if (snake.direction == UP) snake.positions[0] -= MAP_WIDTH;
    else if (snake.direction == DOWN) snake.positions[0] += MAP_HEIGHT;

    // FOOOOOD eat check
    if (snake.positions[0] == food_position)
        snake.counter += 1;

    // check if game won
    if (snake.counter >= MAP_WIDTH * MAP_HEIGHT)
        snake.counter = 1;

    // update snake_tail_positions
    if (snake.counter > 2)
        for (GLuint i = 0; i < snake.counter - 2; i++)
            snake.positions[snake.counter - 1 - i] =
            snake.positions[snake.counter - 1 - i - 1];
    if (snake.counter > 1)
        snake.positions[1] = _last_snake_head_position;

    // check for self destruction
    for (GLuint i = 0; i < snake.counter - 1; i++)
        if (snake.positions[0] == snake.positions[i + 1])
            snake.counter = 1;

    // spawn new food if it was eaten before
    if (_last_snake_length != snake.counter)
        food_position = random_position();
}

/**
 * @brief Obs³uguje funkcje klawiszy.
 *
 * @param window Okno GLFW.
 * @param shaderID Identyfikator shadera.
 * @param texture Identyfikator tekstury.
 * @param vertices Tablica wierzcho³ków.
 */
void Snake::key_functions(GLFWwindow* window, GLuint shaderID, GLuint texture, float vertices[]) {
    _button_array_update(keyboard.keys);
    GLuint _last_snake_direction = snake.direction;

    if (keyboard.keys[GLFW_KEY_ESCAPE].down)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (keyboard.keys[GLFW_KEY_SPACE].pressed)
        snake.direction = PAUSE;

    if (keyboard.keys[GLFW_KEY_LEFT].pressed)
        if ((snake.direction != LEFT) && !(snake.direction & RIGHT))
            snake.direction = LEFT;

    if (keyboard.keys[GLFW_KEY_RIGHT].pressed)
        if (!(snake.direction & LEFT) && (snake.direction != RIGHT))
            snake.direction = RIGHT;

    if (keyboard.keys[GLFW_KEY_UP].pressed)
        if ((snake.direction != UP) && !(snake.direction & DOWN))
            snake.direction = UP;

    if (keyboard.keys[GLFW_KEY_DOWN].pressed)
        if (!(snake.direction & UP) && (snake.direction != DOWN))
            snake.direction = DOWN;

    if (snake.direction != _last_snake_direction) {
        snake_logic();
        TIME_SUM = 0.0;
    }
}
