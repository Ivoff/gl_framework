#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <env.hpp>

struct Shader{

    static GLuint create(std::string file_path, GLint shader_type){
        GLuint s_id{};

        file_path = PROJECT_ROOT + file_path;  
        FILE* file = fopen(file_path.c_str(), "rb");        
        if (!file) {            
            std::cerr << "Error trying to open: " << file_path.c_str() << std::endl;
            exit(EXIT_FAILURE);
        }

        long int file_size{};
        fseek(file, 0, SEEK_END);
        file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *file_content = new char[file_size + 1];
        fread(file_content, sizeof(char), file_size, file);
        file_content[file_size] = '\0';        

        s_id = glCreateShader(shader_type);        
        glShaderSource(s_id, 1, &file_content, NULL);
        glCompileShader(s_id);

        int compile_ok{};
        char log[4096]{};
        glGetShaderiv(s_id, GL_COMPILE_STATUS, &compile_ok);
        if(!compile_ok){
            glGetShaderInfoLog(s_id, 512, NULL, log);
            std::cerr << "Error Shader [" << s_id << "]: " << log << std::endl;
            delete[] file_content;
            exit(EXIT_FAILURE);
        }

        delete[] file_content;                
        return s_id;
    }
};

class Program
{
private:

public:
    GLuint               m_id;
    std::vector<GLuint> m_shaders;

    Program(std::vector<GLuint> shaders) :
        m_shaders{shaders}
    {
        m_id = glCreateProgram();
        for(auto some_shader : m_shaders)
            glAttachShader(m_id, some_shader);
        
        glLinkProgram(m_id);

        for(auto some_shader : m_shaders)
            glDeleteShader(some_shader);

        int link_ok{};
        char log[4096]{};
        glGetProgramiv(m_id, GL_LINK_STATUS, &link_ok);
        if (!link_ok) {
            glGetProgramInfoLog(m_id, 4096, NULL, log);
            std::cerr << "Error Program [" << m_id << "]:\n" << log << std::endl;
            exit(EXIT_FAILURE);
        }        
    }

    void destroy() {
        glDeleteProgram(m_id);
    }

    void use() {
        glUseProgram(m_id);
    }
};

#endif;