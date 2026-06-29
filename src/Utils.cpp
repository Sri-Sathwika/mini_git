#include "Utils.h"

#include <fstream>
#include <sstream>
#include <functional>

using namespace std;

string readFile(
    const string& filename
)
{
    ifstream fin(filename);

    stringstream ss;

    ss << fin.rdbuf();

    return ss.str();
}

string hashContent(
    const string& content
)
{
    return to_string(
        hash<string>{}(content)
    );
}

string hashFile(
    const string& filename
)
{
    return hashContent(
        readFile(filename)
    );
}