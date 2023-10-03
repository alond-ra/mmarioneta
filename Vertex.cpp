#include "Vertex.h"
#include "Renderer.h"
#include <GL/glew.h>
#include <assert.h>
#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
    GLCall( glGenBuffers(1, &m_RendererID) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_RendererID) );
    GLCall( glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW) );
}

VertexBuffer::~VertexBuffer(){
    GLCall( glDeleteBuffers(1, &m_RendererID) );
}

void VertexBuffer::Bind() const{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_RendererID) );
}

void VertexBuffer::Unbind() const{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
}

// IndexBuffer 

IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int count):m_Count(count){
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall( glGenBuffers(1, &m_RendererID) );
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID) );
    GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW) );

}

IndexBuffer::~IndexBuffer(){
    GLCall( glDeleteBuffers(1, &m_RendererID) );
}

void IndexBuffer::Bind() const{
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID) );
}

void IndexBuffer::Unbind() const{
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
}

VertexArray::VertexArray(){
    GLCall( glGenVertexArrays(1, &m_RendererID) );
}

VertexArray::~VertexArray(){
    GLCall( glDeleteVertexArrays(1, &m_RendererID) );
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
    Bind();
    vb.Bind();
    const std::vector<VertexBufferElement> elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size() ; i++){
        const VertexBufferElement element = elements[i];

        GLCall( glEnableVertexAttribArray(i) );
        GLCall( glVertexAttribPointer(i, element.count, element.type, element.normalized,
                                      layout.GetStride(), (void*)(uintptr_t)(offset)));

        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);

    }
}

void VertexArray::Bind() const{
    GLCall( glBindVertexArray(m_RendererID) );
}

void VertexArray::Unbind() const{
    GLCall( glBindVertexArray(0) );
};