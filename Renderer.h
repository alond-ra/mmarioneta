#pragma once

#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include <GL/glew.h>
#include <assert.h>

#include "Vertex.h"
#include "Shader.h"
#include <string>


#define ASSERT(x)if (!(x)) __debugbreak();

//dealing with errors in OpenGL (theCherno)
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

//dealing with errors in OpenGL
bool GLLogCall(const char* function, const char* file, int line);

void GLClearError();

class Renderer{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    Renderer();
};

#endif