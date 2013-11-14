#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>

#include "ogl_headers.hpp"


class ModelImpl;


class Model {
public:
    void render();

    static Model load_from_file(const char * filename);

private:
    Model(std::shared_ptr<ModelImpl> impl);

    std::shared_ptr<ModelImpl> impl_;
};



#endif /* end of include guard: MODEL_HPP */
