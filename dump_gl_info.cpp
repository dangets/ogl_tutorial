#include <cstdio>
#include <cstdlib>

#include "gl_core_3_3.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>



void dump_gl_info(bool dump_extensions) {
    const GLubyte * renderer = glGetString(GL_RENDERER);
    const GLubyte * vendor = glGetString(GL_VENDOR);
    const GLubyte * version = glGetString(GL_VERSION);
    const GLubyte * glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
	
	printf("-------------------------------------------------------------\n");
    printf("GL Vendor    : %s\n", vendor);
    printf("GL Renderer  : %s\n", renderer);
    printf("GL Version   : %s\n", version);
    printf("GL Version   : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glsl_version);
    printf("-------------------------------------------------------------\n");

    if (dump_extensions) {
        GLint nExtensions;
        glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
        for (int i = 0; i < nExtensions; i++) {
            printf("%s\n", glGetStringi(GL_EXTENSIONS, i));
        }
    }
}


int main(int argc, char *argv[]) {
    const char * window_title = "Junk";
    GLFWwindow * window;

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(32, 32, window_title, NULL, NULL);
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

    dump_gl_info(false);

    glfwTerminate();

    return 0;
}
