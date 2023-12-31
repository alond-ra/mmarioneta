#pragma once

#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderProgramSource{
    std::string VertexSource;
    std::string FragmentSource;
}; 


class Shader{
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        std::unordered_map<std::string, int> m_UniformLocationCache;

    public:
        Shader(const std::string& filepath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        // Set uniforms
        void SetUniform1i(const std::string& name, int value);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform4f(const std::string& name, glm::vec4& vector);
        void SetUniformMat4f(const std::string& name, glm::mat4& transform);
        void SetUniform3f(const std::string& name, glm::vec3& vector);

        int GetUniformLocation(const std::string& name);
        ShaderProgramSource ParseShader(const std::string& filepath);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

};

#endif