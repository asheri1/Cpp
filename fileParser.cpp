#include "FileParser.h"
#include <fstream>

FileParser::FileParser(const std::string& file_path) {
    parseFile(file_path);
}

void FileParser::parseFile(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file) {
        throw std::runtime_error("Failed to open the input file.");
    }
}