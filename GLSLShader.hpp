#ifndef GLSLSHADER_HPP
#define GLSLSHADER_HPP

#include <string>

#include "gl_core_3_3.h"


class GLSLShader {
public:
    static GLSLShader from_file(const std::string& path, GLenum type);
    static GLSLShader from_string(const std::string& code, GLenum type);

    GLSLShader(const GLSLShader& other) = delete;
    GLSLShader(GLSLShader&& other);

    ~GLSLShader();

    GLuint get_id() const { return id_; }
    GLenum get_type() const { return type_; }

private:
    GLSLShader(const std::string& code, GLenum type);

    GLuint id_;
    GLenum type_;
};


#endif /* end of include guard: GLSLSHADER_HPP */
