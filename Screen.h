#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include<fstream>
#include<sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Screen
{
public: 
	GLFWwindow* window;
	int width;
	int height;
	std::string title;
	  //jak widzisz klasa przechowuje okno i metody tworzace je, inicjalizujace glfw i glad
public:
	  Screen(int width, int height, std::string title);
	  int glfw_init();
	  int window_init();
	  int glad_init();
};