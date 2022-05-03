#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <chrono>
#include <thread>
#include <glad/glad.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <shader/shader.hpp>

struct WINDOW {
    int width;
    int height;
    GLFWwindow* window;
};

struct APP {    
    bool is_running;
    const char* title;
    int frame_target;    
    double last_frame_time;
    int min_fps_time;
};

struct APP_STATE {
    Program *current_program;
    GLuint current_vao;

    void destroy() {
        glDeleteVertexArrays(1, &current_vao);
        current_program->destroy();        
    }
};

class Application 
{
private:
    
public:    
    APP m_info;
    WINDOW m_window;
    APP_STATE m_state;

    Application(int width, int height, const char* title, int frame_target) : 
        m_info {false, title, frame_target, 0.0, NULL},
        m_window {width, height, nullptr}
    {        
        if(!glfwInit()) {
            std::cerr << "Error initializing GLFW" << std::endl;
            exit(EXIT_FAILURE);
        }        

        glfwWindowHint(GL_MAJOR_VERSION, 4);
        glfwWindowHint(GL_MINOR_VERSION, 5);

        m_window.window = glfwCreateWindow(m_window.width, m_window.height, m_info.title, NULL, NULL);        
        if (!m_window.window) {
            std::cerr << "Error during window creation" << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }        

        glfwMakeContextCurrent(m_window.window);                        

        if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
            std::cerr << "Error while loading OpenGL functions";
            glfwTerminate();
            exit(EXIT_FAILURE);
        }                

        glfwGetFramebufferSize(m_window.window, &m_window.width, &m_window.height);
        glViewport(0, 0, m_window.width, m_window.height);
        
        glfwSetFramebufferSizeCallback(m_window.window, [](GLFWwindow *window, int width, int height){
            glViewport(0, 0, width, height);
        });

        if (m_info.frame_target != 0) {
            m_info.min_fps_time = 1000.0 / m_info.frame_target;
        }

        m_info.is_running = true;        
    }

    void m_update(){
        int available_time = m_info.min_fps_time - (int)(glfwGetTime() - m_info.last_frame_time);
        // precisa ser <= aqui porque se a funcao de update for simples e nao demorar passa direto                
        if (available_time > 0 && available_time <= m_info.min_fps_time)
            std::this_thread::sleep_for(std::chrono::milliseconds(available_time));

        float current_delta = glfwGetTime() - m_info.last_frame_time;
        current_delta = (current_delta > 0.05f) ? 0.05f : current_delta;
        
        m_info.last_frame_time = glfwGetTime();

        this->update(current_delta);        
    }

    void m_process_input(){
        glfwPollEvents();

        if (glfwWindowShouldClose(m_window.window))
            m_info.is_running = false;
        else
            process_input();
    }

    ~Application() {
        destroy();
        glfwTerminate();        
    }
    virtual void setup();
    virtual void render();
    virtual void update(float delta_time);
    virtual void process_input();   
    virtual void destroy();
};

#endif