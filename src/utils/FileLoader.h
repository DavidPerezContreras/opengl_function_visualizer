#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include <vector>

namespace utils {

class FileLoader {
public:
    static std::string LoadTextFile(const std::string& filepath);
    static std::vector<char> LoadBinaryFile(const std::string& filepath);
};

}

#endif 
