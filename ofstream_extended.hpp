#pragma once

#include <string>
#include <fstream>

class ofstream_extended : public std::ofstream {
    public:
        ofstream_extended(std::string file_name);
        std::string file_name;
};