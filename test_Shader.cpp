#include <cstdlib>
#include <cstdio>
#include <utility>

#include "ogl_headers.hpp"


int main(int argc, char *argv[])
{
    const char * window_title = "Triangle 2D";
    GLFWwindow * window;

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(512, 512, window_title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    // Load the OpenGL functions
	if(ogl_LoadFunctions() == ogl_LOAD_FAILED) {
        fprintf(stderr, "Failed call to ogl_LoadFunctions\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

    GLSLShader vert = GLSLShader::from_file("shaders/identity.vert.glsl", GL_VERTEX_SHADER);
    GLSLShader frag = GLSLShader::from_file("shaders/all_red.frag.glsl", GL_FRAGMENT_SHADER);

    GLSLProgram prog;
    prog.attach(vert);
    prog.attach(frag);
    prog.link();

    return 0;
}
