#include "ofstream_extended.hpp"

#ifdef _TESTING
std::unordered_set<ofstream_extended*> ofstream_extended::instances;
ofstream_extended::ofstream_extended(std::string file_name) : std::ofstream(file_name), file_name{file_name} {
    instances.insert(this);
}
#else
ofstream_extended::ofstream_extended(std::string file_name) : std::ofstream(file_name), file_name{file_name} {}
#endif
#ifdef _TESTING
#include <iostream>
ofstream_extended::~ofstream_extended() {
    instances.erase(this);
}
#endif