#include "GLSLShader.hpp"

#include <fstream>
#include <stdexcept>


static std::string read_file_to_string(const std::string& path) {
    std::ifstream ins(path, std::ios::in | std::ios::binary);
    if (ins) {
        std::string contents;
        // resize string to size of file
        ins.seekg(0, std::ios::end);
        contents.resize(ins.tellg());
        ins.seekg(0, std::ios::beg);
        ins.read(&contents[0], contents.size());
        ins.close();

        return contents;
    }

    throw(errno);
}


class GLSLShaderImpl {
public:
    GLSLShaderImpl(const std::string& code, GLenum type) {
        id_ = glCreateShader(type);
        type_ = type;

        GLint result = GL_FALSE;
        int log_length;

        const char * code_ptr = code.c_str();

        glShaderSource(id_, 1, &code_ptr, nullptr);
        glCompileShader(id_);
        glGetShaderiv(id_, GL_COMPILE_STATUS, &result);
        glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &log_length);

        if (result == GL_FALSE) {
            std::string msg;
            msg.resize(log_length);
            glGetShaderInfoLog(id_, log_length, nullptr, &msg[0]);
            glDeleteShader(id_);
            throw std::runtime_error(msg);
        }
    }

    GLSLShaderImpl(const GLSLShaderImpl& other) = delete;
    void operator=(const GLSLShaderImpl& other) = delete;

    ~GLSLShaderImpl() {
        glDeleteShader(id_);
    }


    GLuint id_;
    GLenum type_;
};


GLSLShader GLSLShader::from_file(const std::string& path, GLenum type) {
    std::string code = read_file_to_string(path);
    return GLSLShader::from_string(code, type);
}


GLSLShader GLSLShader::from_string(const std::string& code, GLenum type) {
    return GLSLShader(code, type);
}

GLSLShader::GLSLShader(const std::string& code, GLenum type) :
    impl_(std::make_shared<GLSLShaderImpl>(code, type)) { }

GLuint GLSLShader::get_id() const { return impl_->id_; }
GLenum GLSLShader::get_type() const { return impl_->type_; }

