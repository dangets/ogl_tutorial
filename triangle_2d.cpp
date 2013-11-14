#include <cstdio>
#include <cstdlib>

#include <string>

#include "ogl_headers.hpp"


static void error_callback(int error, const char * description) {
    fputs(description, stderr);
}

static void key_callback(GLFWwindow * window,
        int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}


int main(int argc, char *argv[]) {
    const char * window_title = "Triangle 2D";
    GLFWwindow * window;

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(error_callback);

    window = glfwCreateWindow(512, 512, window_title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // Load the OpenGL functions
    if(ogl_LoadFunctions() == ogl_LOAD_FAILED) {
        error_callback(0, "Failed call to ogl_LoadFunctions\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    GLSLShader vert = GLSLShader::from_file("shaders/identity.vert.glsl", GL_VERTEX_SHADER);
    GLSLShader frag = GLSLShader::from_file("shaders/all_red.frag.glsl", GL_FRAGMENT_SHADER);

    GLSLProgram prog;
    prog.attach(vert);
    prog.attach(frag);
    prog.link();

    // triangle vertex positions
    static const GLfloat vertex_position_data[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };

    // setup vao
    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    // generate a vbo, and upload the vertex_position_data to it
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_position_data), vertex_position_data, GL_STATIC_DRAW);

    // specify layout of the vbo data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
            0,          // attribute 0
            3,          // number of components (X, Y, Z)
            GL_FLOAT,   // type
            GL_FALSE,   // normalized?
            0,          // stride
            (void *)0   // array buffer offset
    );
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glClearColor(0.75f, 0.75f, 0.75f, 0.0f);
    glUseProgram(prog.get_id());

    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the triangle (3 vertices)
        glBindVertexArray(vertex_array_id);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vertex_array_id);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
