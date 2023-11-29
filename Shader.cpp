/**
 * @file Shader.cpp
 * @brief Implementacja metod klasy Shader.
 */

#include "Shader.h"


 /**
  * @brief Funkcja pomocnicza do odczytu zawarto�ci pliku.
  *
  * Odczytuje zawarto�� pliku o podanej nazwie i zwraca jako std::string.
  *
  * @param filename Nazwa pliku do odczytu.
  * @return Zawarto�� pliku jako std::string.
  * @throws std::runtime_error Je�li wyst�pi� b��d podczas odczytu pliku.
  */	
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

/**
 * @brief Konstruktor klasy Shader.
 *
 * Tworzy obiekt Shader, wczytuje i kompiluje kody �r�d�owe shader�w.
 *
 * @param vertexFile �cie�ka do pliku z kodem �r�d�owym shadera wierzcho�k�w.
 * @param fragmentFile �cie�ka do pliku z kodem �r�d�owym shadera fragment�w.
 */
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

/**
 * @brief Generuje map� o okre�lonych wymiarach i przekazuje je do shadera.
 *
 * @param uniform_id Identyfikator zmiennej jednorodnej w shaderze.
 * @param map_width Szeroko�� mapy.
 * @param map_height Wysoko�� mapy.
 */
void Shader::generate_map(const char* uniform_id, int map_width, int map_height) {

	glUniform2f(glGetUniformLocation(ID, uniform_id), (GLfloat)map_width, (GLfloat)map_height);
}



/**
 * @brief Generuje g�ow� w�a na podstawie jego kierunku.
 *
 * @param uniform_id Identyfikator zmiennej jednorodnej w shaderze.
 * @param texture Identyfikator tekstury.
 * @param snake Obiekt klasy Snake reprezentuj�cy w�a.
 */
void Shader::generate_snake_head(const char* uniform_id, GLuint texture, Snake snake) {

	switch (snake.direction) {
	case UP:
		glUniform1i(glGetUniformLocation(ID, uniform_id), 0);
		glBindTexture(GL_TEXTURE_2D, texture);
		break;
	case DOWN:
		glUniform1i(glGetUniformLocation(ID, uniform_id), 2);
		glBindTexture(GL_TEXTURE_2D, texture);
		break;
	case LEFT:
		glUniform1i(glGetUniformLocation(ID, uniform_id), 3);
		glBindTexture(GL_TEXTURE_2D, texture);
		break;
	case RIGHT:
		glUniform1i(glGetUniformLocation(ID, uniform_id), 4);
		glBindTexture(GL_TEXTURE_2D, texture);
		break;
	default:
		glUniform1i(glGetUniformLocation(ID, uniform_id), 0);
		glBindTexture(GL_TEXTURE_2D, texture);
		break;
	}
}


/**
 * @brief Generuje cia�o w�a w shaderze.
 *
 * @param condition_uniform_id Identyfikator zmiennej jednorodnej warunkowej w shaderze.
 * @param uniform_id Identyfikator zmiennej jednorodnej w shaderze.
 */
void Shader::generate_snake_body(const char* condition_uniform_id, const char* uniform_id) {

	glUniform1i(glGetUniformLocation(ID, condition_uniform_id), 1);
	glUniform3f(glGetUniformLocation(ID, uniform_id), 0.3529, 0.2118, 0.1176);
}


/**
 * @brief Generuje jedzenie na mapie w shaderze.
 *
 * @param condition_uniform_id Identyfikator zmiennej jednorodnej warunkowej w shaderze.
 * @param uniform_id Identyfikator zmiennej jednorodnej w shaderze.
 */
void Shader::generate_food(const char* condition_uniform_id, const char* uniform_id) {

	glUniform1i(glGetUniformLocation(ID, condition_uniform_id), 1);
	glUniform3f(glGetUniformLocation(ID, uniform_id), 1.0, 0.0, 0.0);
}