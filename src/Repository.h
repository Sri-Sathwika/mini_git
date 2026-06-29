#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <string>

class Repository
{
public:
    void init();

    void add(
        const std::string &filename);
    void commit(
        const std::string &message);
    void log();
    void checkout(int id);
    void status();
    void diff(const std::string &filename);
    void branch(
        const std::string &name);

    void listBranches();

    void checkoutBranch(
        const std::string &name);
};

#endif