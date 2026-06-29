#ifndef COMMIT_H
#define COMMIT_H

#include <string>

class Commit
{
public:

    static int getNextCommitId();

    static int getHead();

    static void updateHead(int id);
};

#endif