#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

 unsigned int CompileShader(unsigned int type, const std::string& source);

 int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);


