#include "TriangleModel.hpp"


TriangleModel TriangleModel::load_from_file() {
    TriangleModel m;
    m.load();
    return m;
}


TriangleModel::~TriangleModel() {
    //glDeleteBuffers(1, &vertex_buffer_obj);
    //glDeleteBuffers(1, &index_buffer_obj);
    //glDeleteVertexArrays(1, &vertex_array_obj);
}


void TriangleModel::load() {
    // cleanup any existing buffers (NOOP if they are 0)
    glDeleteBuffers(1, &vertex_buffer_obj);
    glDeleteBuffers(1, &index_buffer_obj);
    glDeleteVertexArrays(1, &vertex_array_obj);

    // read file
    GLfloat data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    num_verts = 3;
    size_t num_components = 3;      // position x, y, z
    GLenum attr_type = GL_FLOAT;
    GLboolean attr_normalized = GL_FALSE;
    size_t attr_stride = 0;
    size_t attr_offset = 0;

    size_t data_size = num_verts * num_components * sizeof(GLfloat);

    // setup vao
    glGenVertexArrays(1, &vertex_array_obj);
    glBindVertexArray(vertex_array_obj);

    // generate buffer objects & upload
    glGenBuffers(1, &vertex_buffer_obj);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);

    // specify layout of the vbo data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
            0,          // attribute 0
            num_components,
            attr_type,
            attr_normalized,
            attr_stride,
            (GLvoid *)attr_offset
            );


    //glGenBuffers(1, &index_buffer_obj);

    // unbind any buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void TriangleModel::render() {
    glBindVertexArray(vertex_array_obj);
    glDrawArrays(GL_TRIANGLES, 0, num_verts);
    glBindVertexArray(0);
}


TriangleModel::TriangleModel() : vertex_buffer_obj(0), index_buffer_obj(0), vertex_array_obj(0),
    num_indices(0), index_type(GL_UNSIGNED_INT) { }

