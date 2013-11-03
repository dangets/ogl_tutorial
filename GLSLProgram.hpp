#ifndef GLSLPROGRAM_HPP
#define GLSLPROGRAM_HPP

#include "gl_core_3_3.h"

#include "GLSLShader.hpp"

class GLSLProgram
{
public:
    GLSLProgram();
    GLSLProgram(const GLSLProgram& other) = delete;
    GLSLProgram(GLSLProgram&& other);
    ~GLSLProgram();

    void attach(const GLSLShader& s);
    void detach(const GLSLShader& s);

    void link();

    // get_uniform_location

    GLuint get_id() const { return id_; }

private:
    GLuint id_;
    bool is_linked_;
};

#endif /* end of include guard: GLSLPROGRAM_HPP */
