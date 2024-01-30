#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "utilities/shader.h"
#include <iostream>
#include "game.h"
#include "utilities/resource_manager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void processInput(GLFWwindow* window);


const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

namespace Program
{
	void PrintFloat(float value);
	void PrintString(std::string str);
}