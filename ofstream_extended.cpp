#include "ofstream_extended.hpp"

ofstream_extended::ofstream_extended(std::string file_name) : std::ofstream(file_name), file_name{file_name} {}