#include "GLSLProgram.hpp"

#include <stdexcept>


GLSLProgram::GLSLProgram() : id_(0), is_linked_(false) {
    id_ = glCreateProgram();
}

GLSLProgram::GLSLProgram(GLSLProgram&& other) : id_(other.id_) {
    other.id_ = 0;
}

GLSLProgram::~GLSLProgram() {
    // glDeleteProgram automatically detaches shader objects
    glDeleteProgram(id_);
}


void GLSLProgram::attach(const GLSLShader& s) {
    glAttachShader(id_, s.get_id());
    // GLenum result = glGetError();
}

void GLSLProgram::detach(const GLSLShader& s) {
    glDetachShader(id_, s.get_id());
    // GLenum result = glGetError();
}

void GLSLProgram::link() {
    glLinkProgram(id_);

    GLint result = GL_FALSE;
    int log_length;

    glGetProgramiv(id_, GL_LINK_STATUS, &result);
    glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &log_length);

    if (result == GL_FALSE) {
        std::string msg;
        msg.resize(log_length);
        glGetProgramInfoLog(id_, log_length, nullptr, &msg[0]);
        glDeleteShader(id_);
        throw std::runtime_error(msg);
    }

    is_linked_ = true;
}
