#version 330 core

out vec4 fragment_color;

uniform vec3 COLOR;
uniform sampler2D SNAKE_HEAD;
uniform int IS_HEAD;

in vec2 texCoord;

void main()
{
    if(IS_HEAD == 0)
        fragment_color = texture(SNAKE_HEAD, texCoord);
    else
        fragment_color = vec4(COLOR, 1.0);
}