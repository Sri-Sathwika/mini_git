#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string readFile(
    const std::string& filename
);

std::string hashContent(
    const std::string& content
);

std::string hashFile(
    const std::string& filename
);

#endif