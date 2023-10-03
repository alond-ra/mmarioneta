#pragma once

#ifndef VERTEX_ARRAY_CLASS_H
#define VERTEX_ARRAY_CLASS_H

#include <GL/glew.h>
#include<iostream>
#include <vector>

// VertexBuffer definitions
class VertexBuffer{
private:
    unsigned int m_RendererID;

public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;
};

struct VertexBufferElement{
public: 
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type){
        switch (type){
        case GL_FLOAT: return sizeof(GLfloat);
        case GL_UNSIGNED_INT: return sizeof(GLuint);
        case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
        default: return 0;
        }
    }
};

class VertexBufferLayout{
private:
    unsigned int m_Stride;
    std::vector<VertexBufferElement> m_Elements;

    void Push(unsigned int type, unsigned int count, unsigned char normalized){
        m_Elements.push_back({ type, count, normalized });
        m_Stride += count * VertexBufferElement::GetSizeOfType(type);
    };

public:
    VertexBufferLayout() : m_Stride(0) { }

    void AddFloat(unsigned int count) { Push(GL_FLOAT, count, GL_FALSE); }
    void AddUnsignedInt(unsigned int count) { Push(GL_UNSIGNED_INT, count, GL_FALSE); }
    void AddUnsignedByte(unsigned int count) { Push(GL_UNSIGNED_BYTE, count, GL_TRUE); }

    const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
    unsigned int GetStride() const { return m_Stride; }
};

class IndexBuffer{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;

public:
    IndexBuffer(const unsigned int* indices, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    unsigned int GetCount() const { return m_Count; }

};

class VertexArray{
private:
    unsigned int m_RendererID;

public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void Unbind() const;
};


#endif