#pragma once

#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLint createProgram(const char* vShader, const char* fShader);

GLint loadShader(GLenum shaderType, const char* pSource);

GLuint loadTexture(const char* path);

void checkCompileErrors(GLuint shader, std::string type);

