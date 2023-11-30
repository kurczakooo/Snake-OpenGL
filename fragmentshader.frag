#version 330 core

out vec4 fragment_color;

uniform vec3 COLOR;
uniform sampler2D SNAKE_HEAD;
uniform sampler2D FOOD;
uniform int IS_HEAD;

in vec2 texCoord;
in vec2 foodTexCoord;

void main()
{
    if(IS_HEAD == 0)
        fragment_color = texture(SNAKE_HEAD, vec2(texCoord.x, texCoord.y));
    else if(IS_HEAD == 1)
        fragment_color = vec4(COLOR, 1.0);
    else if(IS_HEAD == 2)
        fragment_color = texture(SNAKE_HEAD, vec2(1 - texCoord.x, 1 - texCoord.y));
    else if(IS_HEAD == 3)
        fragment_color = texture(SNAKE_HEAD, vec2(1 - texCoord.y, 1 - texCoord.x));
    else if(IS_HEAD == 4)
        fragment_color = texture(SNAKE_HEAD, vec2(texCoord.y, texCoord.x));
    else if(IS_HEAD == 5)
        fragment_color = texture(FOOD, vec2(foodTexCoord.x, foodTexCoord.y));
}