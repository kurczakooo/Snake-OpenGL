#include "Snake.h"
#include "Directions.h"
#include "Buttons.h"
#include "Keyboard.h"

void SnakeData::init() {
    TIME_NOW = TIME_LAST = glfwGetTime();
    TIME_DELTA = TIME_SUM = 0.0;
}

void SnakeData::set_tempo() {
    TIME_NOW = glfwGetTime();
    TIME_DELTA = TIME_NOW - TIME_LAST;
    TIME_LAST = TIME_NOW;
    TIME_SUM += TIME_DELTA;
    if (TIME_SUM >= 1.0 / SPEED)
    {
        snake.snake_logic();
        TIME_SUM = 0.0;
    }
}


void Snake::_button_array_update(struct Button* buttons)
{
    for (int i = 0; i < GLFW_KEY_LAST; i++)
    {
        buttons[i].pressed = buttons[i].down && !buttons[i].last;
        buttons[i].last = buttons[i].down;
    }
}

GLuint Snake::random_position(void)
{
    GLuint RND = (GLuint)(rand() % (MAP_WIDTH * MAP_HEIGHT));
    GLboolean free_position;
    do {
        free_position = GL_TRUE;
        for (GLuint i = 0; i < snake.counter; i++)
        {
            if (snake.positions[i] == RND)
            {
                free_position = GL_FALSE;
                RND++;
                if (RND >= (MAP_WIDTH * MAP_HEIGHT))
                    RND %= (MAP_WIDTH * MAP_HEIGHT);
            }
        }
    } while (!free_position);
    return RND;
}

void Snake::snake_logic(void)
{
    /* if PAUSE -> do nothing */
    if (snake.direction & PAUSE)
        return;

    /* check wall hit */
    if ((snake.positions[0] % MAP_WIDTH == 0 && snake.direction == LEFT) ||
        (snake.positions[0] % MAP_WIDTH == MAP_WIDTH - 1 && snake.direction == RIGHT) ||
        (snake.positions[0] / MAP_WIDTH == 0 && snake.direction == UP) ||
        (snake.positions[0] / MAP_WIDTH == MAP_HEIGHT - 1 && snake.direction == DOWN))
    {
        snake.counter = 1;
        snake.direction = PAUSE;
        return;
    }

    /* ELSE */
    GLuint _last_snake_head_position = snake.positions[0];
    GLuint _last_snake_length = snake.counter;

    /* update snake_head_position */
    if (snake.direction == LEFT) snake.positions[0] -= 1;
    else if (snake.direction == RIGHT) snake.positions[0] += 1;
    else if (snake.direction == UP) snake.positions[0] -= MAP_WIDTH;
    else if (snake.direction == DOWN) snake.positions[0] += MAP_HEIGHT;

    /* FOOOOOD eat check */
    if (snake.positions[0] == food_position)
        snake.counter += 1;

    /* check if game won */
    if (snake.counter >= MAP_WIDTH * MAP_HEIGHT)
        snake.counter = 1;

    /* update snake_tail_positions */
    if (snake.counter > 2)
        for (GLuint i = 0; i < snake.counter - 2; i++)
            snake.positions[snake.counter - 1 - i] =
            snake.positions[snake.counter - 1 - i - 1];
    if (snake.counter > 1)
        snake.positions[1] = _last_snake_head_position;

    /* check for self destruction */
    for (GLuint i = 0; i < snake.counter - 1; i++)
        if (snake.positions[0] == snake.positions[i + 1])
            snake.counter = 1;

    /* spawn new food if it was eaten before */
    if (_last_snake_length != snake.counter)
        food_position = random_position();
}

void Snake::key_functions(GLFWwindow* window)
{
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

    if (snake.direction != _last_snake_direction)
    {
        snake_logic();
        TIME_SUM = 0.0;
    }
}