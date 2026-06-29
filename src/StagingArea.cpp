#include "Utils.h"
#include "StagingArea.h"
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
bool StagingArea::addFile(
    const std::string& filename
)
{

    if(!fs::exists(filename))
    {
        std::cout
            << "File not found\n";
        return false;
    }

    std::string hash =
        hashFile(filename);

    fs::copy_file(
        filename,
        ".mygit/objects/" + hash,
        fs::copy_options::overwrite_existing
    );

    std::ofstream index(
        ".mygit/staging/index.txt",
        std::ios::app
    );

    index
        << filename
        << " "
        << hash
        << "\n";

    index.close();

    std::cout
        << "Added "
        << filename
        << "\n";

    return true;
}