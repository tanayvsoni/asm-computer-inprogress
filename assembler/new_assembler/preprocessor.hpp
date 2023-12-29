#ifndef PREPROCESSOR_HPP
#define PREPROCESOR_HPP

#include "main.hpp"

class Preprocessor {
public:
    Preprocessor() {}; 

    void processFile(const std::string& filePath, std::string& output);


private:
    
    const std::string _filename;

    std::string _extractIncludedFilePath(const std::string& line);

};

#endif