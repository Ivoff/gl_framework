#include <application/application.hpp>
#include <shader/shader.hpp>

int i = 1;

void Application::setup() {
    GLuint vertex_shader   = Shader::create("shaders/vertex.vert", GL_VERTEX_SHADER);
    GLuint fragment_shader = Shader::create("shaders/fragment.frag", GL_FRAGMENT_SHADER);     
    m_data.current_program = new Program({vertex_shader, fragment_shader});    
    glCreateVertexArrays(1, &m_data.current_vao);
    glBindVertexArray(m_data.current_vao);
}

void Application::render() {    
    GLfloat color[] = {0.1f, 0.2f, 0.3f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, color);    
    m_data.current_program->use();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Application::update(float delta_time) {

}

void Application::process_input() {

}

void Application::destroy() {
    m_data.destroy();
}

