#ifndef GLSLSHADER_HPP
#define GLSLSHADER_HPP

#include <memory>
#include <string>

#include "gl_core_3_3.h"


class GLSLShaderImpl;


class GLSLShader {
public:
    static GLSLShader from_file(const std::string& path, GLenum type);
    static GLSLShader from_string(const std::string& code, GLenum type);

    GLuint get_id() const;
    GLenum get_type() const;

private:
    GLSLShader(const std::string& code, GLenum type);

    std::shared_ptr<GLSLShaderImpl> impl_;
};


#endif /* end of include guard: GLSLSHADER_HPP */
