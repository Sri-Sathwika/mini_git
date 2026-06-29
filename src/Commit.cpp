#include "Commit.h"

#include <fstream>

int Commit::getHead()
{
    std::ifstream fin(".mygit/HEAD");

    int x;

    fin >> x;

    return x;
}

void Commit::updateHead(int id)
{
    std::ofstream fout(".mygit/HEAD");

    fout << id;
}

int Commit::getNextCommitId()
{
    return getHead() + 1;
}