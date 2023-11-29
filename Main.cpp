#include "Screen.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Snake.h"
#include "Buttons.h"
#include "Directions.h"
#include "Texture.h"

//hierarchia klas
//komentarze
//dokumentacja

GLdouble TIME_NOW, TIME_LAST, TIME_DELTA, TIME_SUM;
Snake snake;

Keyboard keyboard;
Mouse mouse;

GLfloat vertices[] = {
  0.0, 0.0,
  0.0, 1.0,
  1.0, 1.0,
  1.0, 0.0,
};

GLuint indices[] = {
  0, 1, 2,
  2, 3, 0
};

int main(void) {

    Screen screen(WINDOW_WIDTH, WINDOW_HEIGHT, "snake");
    screen.glfw_init();
    screen.window_init();
    screen.glad_init();

    glfwSetKeyCallback(screen.window, keyboard.key_callback);
    glfwSetMouseButtonCallback(screen.window, mouse.mouse_button_callback);

    Texture texture_skubi("components/skubi.png");

    Shader shader_program("vertexshader.vert", "fragmentshader.frag");

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
    

    snake.counter = 1;
    snake.positions[0] = (GLuint)(rand() % (MAP_WIDTH * MAP_HEIGHT));
    snake.direction = PAUSE;

    snake.food_position = snake.random_position();

    TIME_NOW = TIME_LAST = glfwGetTime();
    TIME_DELTA = TIME_SUM = 0.0;

    while (!glfwWindowShouldClose(screen.window))
    {
        glClearColor(0.14, 0.16, 0.18, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        snake.key_functions(screen.window, shader_program.ID, texture_skubi.ID, vertices);

        TIME_NOW = glfwGetTime();
        TIME_DELTA = TIME_NOW - TIME_LAST;
        TIME_LAST = TIME_NOW;
        TIME_SUM += TIME_DELTA;
        if (TIME_SUM >= 1.0 / SPEED)
        {
            snake.snake_logic();
            TIME_SUM = 0.0;
        }

        glBindVertexArray(VAO);
        glUseProgram(shader_program.ID);

        shader_program.generate_map("GRID_COUNT", MAP_WIDTH, MAP_HEIGHT);

        /* snake */
        for (GLuint i = 0; i < snake.counter; i++)
        {
            glUniform1f(glGetUniformLocation(shader_program.ID, "POSITION"), snake.positions[i]);

            if (i == 0) {
                shader_program.generate_snake_head("IS_HEAD", texture_skubi.ID, snake);
            }
            else
                shader_program.generate_snake_body("IS_HEAD", "COLOR");

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        /* food */
        glUniform1f(glGetUniformLocation(shader_program.ID, "POSITION"), snake.food_position);
        shader_program.generate_food("IS_HEAD", "COLOR");
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(screen.window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
