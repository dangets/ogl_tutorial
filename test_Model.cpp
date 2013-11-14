#include <iostream>

#include "ogl_headers.hpp"

#include "Model.hpp"


int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "usage error" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    ogl_simple_init();

    Model m = Model::load_from_file(argv[1]);

    return 0;
}
