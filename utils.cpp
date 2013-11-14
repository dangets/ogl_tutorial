#include "utils.hpp"

#include <fstream>
#include <boost/algorithm/string.hpp>

using std::string;

string lstrip(string& str) {
    boost::algorithm::trim_left(str);
    return str;
}

string lstrip_copy(const string& str) {
    return boost::algorithm::trim_left_copy(str);
}

std::string rstrip(std::string& str) {
    boost::algorithm::trim_right(str);
    return str;
}

std::string rstrip_copy(const std::string& str) {
    return boost::algorithm::trim_right_copy(str);
}

string strip(string& str) {
    boost::algorithm::trim(str);
    return str;
}

string strip_copy(const string& str) {
    return boost::algorithm::trim_copy(str);
}


string read_file_to_string(const string& path) {
    std::ifstream ins(path, std::ios::in | std::ios::binary);
    if (ins) {
        string contents;
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

