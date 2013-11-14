#include "Model.hpp"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "utils.hpp"


struct AttrSpec {
    GLuint attr_id;
    GLuint num_components;
    GLenum type;
    GLboolean normalized;
    GLuint stride;
    size_t offset;
};


class ModelImpl {
public:
    ModelImpl() : vertex_buffer_obj(0), index_buffer_obj(0), vertex_array_obj(0),
            num_verts(0), num_indices(0), index_type(GL_UNSIGNED_BYTE) {
        glGenBuffers(1, &vertex_buffer_obj);
        glGenBuffers(1, &index_buffer_obj);
        glGenVertexArrays(1, &vertex_array_obj);
    }

    ~ModelImpl() {
        glDeleteBuffers(1, &vertex_buffer_obj);
        glDeleteBuffers(1, &index_buffer_obj);
        glDeleteBuffers(1, &vertex_array_obj);
    }

    void render() {
        glBindVertexArray(vertex_array_obj);
        glDrawArrays(GL_TRIANGLES, 0, num_verts);
        glBindVertexArray(0);
    }

    void upload_data(GLuint num_verts, const std::vector<AttrSpec>& attr_specs,
            const size_t data_size, const void *data) {
        glBindVertexArray(vertex_array_obj);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
        glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);

        for (const auto& attr : attr_specs) {
            glEnableVertexAttribArray(attr.attr_id);
            glVertexAttribPointer(attr.attr_id, attr.num_components, attr.type,
                    attr.normalized, attr.stride, (void *)attr.offset);
        }

        this->num_verts = num_verts;

        glBindVertexArray(0);
    }

private:
    GLuint vertex_buffer_obj;
    GLuint index_buffer_obj;
    GLuint vertex_array_obj;

    GLuint num_verts;
    GLuint num_indices;
    GLenum index_type;
};



static void get_noncomment_line(std::istream& is, std::string& str) {
    str = "";
    while (getline(is, str)) {
        size_t i = str.find_first_not_of(" \t\r");
        if (i == std::string::npos || str[i] == '#') {
            continue;
        }
        break;
    }
}

AttrSpec parse_attr_spec_line(std::string& line) {
    std::istringstream ss(line);
    std::string field;

    AttrSpec attr;

    // 0, 3, GL_FLOAT, false, 0, 0

    getline(ss, field, ',');
    attr.attr_id = std::stoul(field);

    getline(ss, field, ',');
    attr.num_components = std::stoul(field);

    getline(ss, field, ',');
    strip(field);
    if (field == "GL_FLOAT") {
        attr.type = GL_FLOAT;
    } else {
        std::string msg = "unhandled attr.type: '";
        msg += field;
        msg += "'";
        throw std::runtime_error(msg);
    }

    getline(ss, field, ',');
    strip(field);
    std::transform(field.begin(), field.end(), field.begin(), ::tolower);
    if (field == "false") {
        attr.normalized = GL_FALSE;
    } else if (field == "true") {
        attr.normalized = GL_TRUE;
    } else {
        throw std::runtime_error("attr.normalized parse error");
    }

    getline(ss, field, ',');
    attr.stride = std::stoul(field);

    getline(ss, field, ',');
    attr.offset = std::stoul(field);

    return attr;
}


size_t attr_type_size(GLenum type) {
    switch (type) {
        case GL_FLOAT:
            return 4;
        default:
            throw std::runtime_error("unhandled GLenum type");
    }
}

void read_ascii_data(std::istream& ins, const int num_verts,
        const std::vector<AttrSpec>& attr_specs, char *data) {
    size_t offset = 0;

    for (int v=0; v<num_verts; v++) {
        for (const auto& attr : attr_specs) {
            size_t attr_size = attr_type_size(attr.type);
            for (unsigned int c=0; c<attr.num_components; c++) {
                float val;
                ins >> val;
                data[offset] = val;
                offset += attr_size;
            }
        }
    }
}



Model Model::load_from_file(const char * filename) {
    std::ifstream ins(filename);

    GLuint num_verts = 0;
    GLuint num_attributes = 0;
    std::vector<AttrSpec> attr_specs;

    std::string line;
    get_noncomment_line(ins, line);
    num_verts = std::stoul(line);

    get_noncomment_line(ins, line);
    num_attributes = std::stoul(line);

    for (unsigned int i=0; i<num_attributes; ++i) {
        get_noncomment_line(ins, line);
        attr_specs.push_back(parse_attr_spec_line(line));
    }

    size_t data_size = 0;
    for (const auto& attr : attr_specs) {
        data_size += attr.num_components * attr_type_size(attr.type);
    }
    data_size *= num_verts;

    std::cout << "data_size: " << data_size << std::endl;

    std::vector<char> data;
    data.reserve(data_size);
    read_ascii_data(ins, num_verts, attr_specs, &data[0]);

    auto impl = std::make_shared<ModelImpl>();
    impl->upload_data(num_verts, attr_specs, data_size, &data[0]);

    return Model(impl);
}


Model::Model(std::shared_ptr<ModelImpl> impl) : impl_(impl) { }

void Model::render() {
    impl_->render();
}

