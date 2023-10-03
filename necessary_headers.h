#pragma once

#ifndef NECESSARY_HEADERS_H
#define NECESSARY_HEADERS_H


#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Model.h"
#include "Sphere.h"
#include "Camera.h"

#include "Renderer.h"
#include "Vertex.h"
#include "Shader.h"

#include "Interface.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include<stb/stb_image.h>


#endif