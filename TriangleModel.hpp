#ifndef TRIANGLEMODEL_HPP
#define TRIANGLEMODEL_HPP


#include "gl_core_3_3.h"
#include <GLFW/glfw3.h>


class TriangleModel
{
public:
    //static TriangleModel load_from_file(const char *fname) {
    static TriangleModel load_from_file();
    ~TriangleModel();

    void load();

    void render();


private:
    TriangleModel();

    GLuint vertex_buffer_obj;
    GLuint index_buffer_obj;
    GLuint vertex_array_obj;

    GLuint num_verts;
    GLuint num_indices;
    GLuint index_type;          // the size of the index data (one of GL_UNSIGNED_{BYTE,SHORT,INT})
};


#endif /* end of include guard: TRIANGLEMODEL_HPP */
