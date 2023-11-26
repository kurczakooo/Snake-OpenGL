#include "Shader.h"

std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw std::runtime_error("Error loading file content");
}


Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	vertex_code = vertexCode.c_str();
	fragment_code = fragmentCode.c_str();

	GLuint fShader, vShader;

	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vertex_code, NULL);
	glCompileShader(vShader);

	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fragment_code, NULL);
	glCompileShader(fShader);

	ID = glCreateProgram();
	glAttachShader(ID, vShader);
	glAttachShader(ID, fShader);
	glLinkProgram(ID);


	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

void Shader::generate_map(const char* uniform_id, int map_width, int map_height) {

	glUniform2f(glGetUniformLocation(ID, uniform_id), (GLfloat)map_width, (GLfloat)map_height);
}

void Shader::generate_snake_head(const char* uniform_id, GLuint texture) {

	glUniform1i(glGetUniformLocation(ID, uniform_id), 0);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Shader::generate_snake_body(const char* condition_uniform_id, const char* uniform_id) {

	glUniform1i(glGetUniformLocation(ID, condition_uniform_id), 1);
	glUniform3f(glGetUniformLocation(ID, uniform_id), 0.3529, 0.2118, 0.1176);
}

void Shader::generate_food(const char* condition_uniform_id, const char* uniform_id) {

	glUniform1i(glGetUniformLocation(ID, condition_uniform_id), 1);
	glUniform3f(glGetUniformLocation(ID, uniform_id), 1.0, 0.0, 0.0);
}