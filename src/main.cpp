#include <application/application.hpp>
#include <stdio.h>

int main() {
    Application *app = new Application(860, 640, "OpenGL", 60);
    app->setup();
    while( app->m_info.is_running ) 
    {        
        app->m_process_input();
        app->m_update();
        app->render();

        glfwSwapBuffers(app->m_window.window);
    }        

    delete app;

    return 0;
}