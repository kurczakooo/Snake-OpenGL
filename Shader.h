#pragma once
#include "Screen.h"

std::string get_file_contents(const char* filename);


class Shader
{
public:

	GLuint ID;
	const GLchar* vertex_code;
	const GLchar* fragment_code;

	Shader() {};
	Shader(const char* vertexFile, const char* fragmentFile);

	void generate_map(const char* uniform_id, int map_width, int map_height);
	void generate_snake_head(const char* uniform_id, GLuint texture);
	void generate_snake_body(const char* condition_uniform_id, const char* uniform_id);
	void generate_food(const char* condition_uniform_id, const char* uniform_id);

};