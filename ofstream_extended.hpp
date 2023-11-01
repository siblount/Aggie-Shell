#pragma once

#include <string>
#include <fstream>
#include <unordered_set>
class ofstream_extended : public std::ofstream {
    public:
        static std::unordered_set<ofstream_extended*> instances;
        ofstream_extended(std::string file_name);
        std::string file_name;
        #ifdef _TESTING
        ~ofstream_extended();
        #endif
};