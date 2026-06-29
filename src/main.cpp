#include "Repository.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: mygit <command>\n";
        return 0;
    }

    Repository repo;

    string command = argv[1];

    if (command == "init")
    {
        repo.init();
    }
    else if (command == "add")
    {
        if (argc < 3)
        {
            cout
                << "Specify a file\n";
        }
        else
        {
            repo.add(argv[2]);
        }
    }
    else if (command == "commit")
    {
        if (argc < 3)
        {
            cout
                << "Commit message missing\n";
        }
        else
        {
            repo.commit(
                argv[2]);
        }
    }
    else if (command == "log")
    {
        repo.log();
    }
    else if (command == "checkout")
    {
        if (argc < 3)
        {
            std::cout
                << "Provide commit id\n";
        }
        else
        {
            repo.checkout(
                std::stoi(argv[2]));
        }
    }
    else if (command == "status")
    {
        repo.status();
    }
    else if (command == "diff")
    {
        repo.diff(argv[2]);
    }
    else if (command == "branch")
    {
        if (argc == 2)
            repo.listBranches();
        else
            repo.branch(argv[2]);
    }
    else if (command == "switch")
    {
        repo.checkoutBranch(
            argv[2]);
    }
    else
    {
        cout << "Unknown command\n";
    }

    return 0;
}