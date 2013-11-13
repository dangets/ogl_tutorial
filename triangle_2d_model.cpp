#include <cstdio>
#include <cstdlib>

#include <string>

#include "gl_core_3_3.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GLSLProgram.hpp"
#include "GLSLShader.hpp"
#include "TriangleModel.hpp"


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

    TriangleModel m = TriangleModel::load_from_file();
    double time = glfwGetTime();

    glClearColor(0.75f, 0.75f, 0.75f, 0.0f);
    glUseProgram(prog.get_id());

    while (!glfwWindowShouldClose(window)) {
        time = glfwGetTime();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        m.render();

        // swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
