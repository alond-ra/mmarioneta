#include "Renderer.h"
#include <iostream>


//dealing with errors in OpenGL
bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << ") " << function << " " << file << " " << line << std::endl;
        return false;
    }
    return true;
}

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}


Renderer::Renderer() {
    Clear();
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //background color (blue)
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const{
    //printf("?\n");
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    // glClear(GL_DEPTH_BUFFER_BIT)
    GLCall(glClear(GL_DEPTH_BUFFER_BIT));
}