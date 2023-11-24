#include "Screen.h"
#include "Bitmap.h"

#include "Keyboard.h"
#include "Snake.h"
#include "Buttons.h"
#include "Directions.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libraries/stb_image.h"


Snake snake;
GLuint food_position;
GLdouble TIME_NOW, TIME_LAST, TIME_DELTA, TIME_SUM;

Keyboard keyboard;

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

const GLchar* vShader_Code =
"#version 330 core\n"
"layout (location = 0) in vec2 v_pos;\n"
"layout (location = 1) in vec2 v_texCoord;\n"///////////
"uniform float POSITION;\n"
"uniform vec2 GRID_COUNT;\n"
"out vec2 texCoord;\n"//////////////////////////
"void main(){\n"
"  vec2 GRID_SIZE = vec2(2 / GRID_COUNT.x, 2 / GRID_COUNT.y);\n"
"  vec2 pos_center = vec2((mod(POSITION, GRID_COUNT.x) * GRID_SIZE.x) - 1.0 + (GRID_SIZE.x / 2),\n"
"    1.0 - GRID_SIZE.y - (floor(POSITION / GRID_COUNT.x) * GRID_SIZE.y) + (GRID_SIZE.y / 2));\n"
"  gl_Position = vec4(\n"
"    pos_center.x - (GRID_SIZE.x / 2) + (v_pos.x * GRID_SIZE.x),\n"
"    pos_center.y - (GRID_SIZE.y / 2) + (v_pos.y * GRID_SIZE.y),\n"
"    0.0, 1.0);\n"
"    texCoord = vec2(v_pos.x, v_pos.y);\n"////////////////////
"}\0";

const GLchar* fShader_Code =
"#version 330 core\n"
"out vec4 fragment_color;\n"
"uniform vec3 COLOR;\n"
"uniform sampler2D SNAKE_HEAD;\n"
"uniform int IS_HEAD;\n"
"in vec2 texCoord;\n"
"void main(){\n"
"   if(IS_HEAD == 0)\n"
"       fragment_color = texture(SNAKE_HEAD, texCoord);\n"
"   else\n"
"       fragment_color = vec4(COLOR, 1.0);\n"
"}\0";



int main(void) {

    Screen screen(WINDOW_WIDTH, WINDOW_HEIGHT, "snake");


    screen.glfw_init();

    screen.window_init();

    screen.glad_init();

    glfwSetKeyCallback(screen.window, keyboard.key_callback);


    //Texture snake_head("components\skubi.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(GL_TRUE);
    unsigned char* image = stbi_load("components/skubi.png", &width, &height, &channels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);



    GLuint vShader, fShader, shader_programm;
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShader_Code, NULL);
    glCompileShader(vShader);
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShader_Code, NULL);
    glCompileShader(fShader);
    shader_programm = glCreateProgram();
    glAttachShader(shader_programm, vShader);
    glAttachShader(shader_programm, fShader);
    glLinkProgram(shader_programm);
    glDeleteShader(vShader);
    glDeleteShader(fShader);


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

    food_position = snake.random_position();

    TIME_NOW = TIME_LAST = glfwGetTime();
    TIME_DELTA = TIME_SUM = 0.0;


    while (!glfwWindowShouldClose(screen.window))
    {
        glClearColor(0.14, 0.16, 0.18, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        snake.key_functions(screen.window);

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
        glUseProgram(shader_programm);
        glUniform2f(glGetUniformLocation(shader_programm, "GRID_COUNT"), (GLfloat)MAP_WIDTH, (GLfloat)MAP_HEIGHT);

        /* snake */
        for (GLuint i = 0; i < snake.counter; i++)
        {
            glUniform1f(glGetUniformLocation(shader_programm, "POSITION"), snake.positions[i]);

            if (i == 0) {
               glUniform1i(glGetUniformLocation(shader_programm, "IS_HEAD"), 0);
               glBindTexture(GL_TEXTURE_2D, texture);
            }
            else {
                glUniform1i(glGetUniformLocation(shader_programm, "IS_HEAD"), 1);
                glUniform3f(glGetUniformLocation(shader_programm, "COLOR"), 0.3529, 0.2118, 0.1176);
            }

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        /* food */
        glUniform1f(glGetUniformLocation(shader_programm, "POSITION"), food_position);
        glUniform1i(glGetUniformLocation(shader_programm, "IS_HEAD"), 1);
        glUniform3f(glGetUniformLocation(shader_programm, "COLOR"), 1.0, 0.0, 0.0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(screen.window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
