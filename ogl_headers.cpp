#include <cstdlib>
#include <iostream>

#include "ogl_headers.hpp"


void ogl_simple_init() {
    GLFWwindow * window;

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(32, 32, "", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    // Load the OpenGL functions
    if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}
