#ifndef MODEL_HPP
#define MODEL_HPP

#include "gl_core_3_3.h"
#include <GLFW/glfw3.h>


class Model
{
public:
    //static Model load_from_file(const char *fname) {
    static Model load_from_file();
    ~Model();

    void load();

    void render();


private:
    Model();

    GLuint vertex_buffer_obj;
    GLuint index_buffer_obj;
    GLuint vertex_array_obj;

    GLuint num_verts;
    GLuint num_indices;
    GLuint index_type;          // the size of the index data (one of GL_UNSIGNED_{BYTE,SHORT,INT})
};


#endif /* end of include guard: MODEL_HPP */
