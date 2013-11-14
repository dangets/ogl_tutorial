#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

std::string lstrip(std::string& str);
std::string lstrip_copy(const std::string& str);

std::string rstrip(std::string& str);
std::string rstrip_copy(const std::string& str);

std::string strip(std::string& str);
std::string strip_copy(const std::string& str);

std::string read_file_to_string(const std::string& path);


#endif /* end of include guard: UTILS_HPP */
