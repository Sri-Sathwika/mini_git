#include "Repository.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include<string>
#include "StagingArea.h"
#include "Commit.h"
#include "Utils.h"

namespace fs = std::filesystem;

void Repository::init()
{
    if(fs::exists(".mygit"))
    {
        std::cout << "Repository already exists\n";
        return;
    }

    fs::create_directory(".mygit");
    fs::create_directory(".mygit/objects");
    fs::create_directory(".mygit/commits");
    fs::create_directory(".mygit/staging");
    fs::create_directory(".mygit/branches");

    std::ofstream head(".mygit/HEAD");
    std::ofstream(".mygit/branches/main") << -1;

    head << -1;

    head.close();

    std::cout
        << "Initialized empty repository\n";
}

void Repository::add(
    const std::string& filename
)
{
    if(!fs::exists(".mygit"))
    {
        std::cout
            << "Not a repository\n";

        return;
    }

    StagingArea stage;

    stage.addFile(filename);
}

void Repository::commit(
    const std::string& message
)
{
    int id = Commit::getNextCommitId();

    std::string commitPath =
        ".mygit/commits/" +
        std::to_string(id);

    fs::create_directory(commitPath);

    std::ofstream meta(
        commitPath +
        "/metadata.txt"
    );

    meta << "id=" << id << "\n";
    meta << "message=" << message << "\n";
    meta << "parent="
         << Commit::getHead()
         << "\n\n";

    std::ifstream index(
        ".mygit/staging/index.txt"
    );

    std::string file, hash;

    while(index >> file >> hash)
    {
        meta
            << file
            << "="
            << hash
            << "\n";
    }

    meta.close();

    Commit::updateHead(id);

    fs::remove_all(".mygit/staging");
    fs::create_directory(".mygit/staging");

    std::cout
        << "Committed as "
        << id
        << "\n";
}

void Repository::log()
{
    int current =
        Commit::getHead();

    while(current != -1)
    {
        std::string metadata =
            ".mygit/commits/"
            + std::to_string(current)
            + "/metadata.txt";

        std::ifstream fin(metadata);

        std::string line;
        std::string message;
        int parent = -1;

        while(std::getline(fin, line))
        {
            if(line.rfind("message=",0)==0)
            {
                message =
                    line.substr(8);
            }

            if(line.rfind("parent=",0)==0)
            {
                parent =
                    std::stoi(
                        line.substr(7)
                    );
            }
        }

        std::cout
            << "Commit "
            << current
            << "\n";

        std::cout
            << "Message: "
            << message
            << "\n\n";

        current = parent;
    }
}
void Repository::checkout(int id)
{
    std::string metadata =
        ".mygit/commits/"
        + std::to_string(id)
        + "/metadata.txt";

    if(!fs::exists(metadata))
    {
        std::cout
            << "Commit not found\n";
        return;
    }

    std::ifstream fin(metadata);

    std::string line;

    while(std::getline(fin,line))
    {
        auto pos =
            line.find('=');

        if(pos==std::string::npos)
            continue;

        std::string key =
            line.substr(0,pos);

        std::string value =
            line.substr(pos+1);

        if(key=="id" ||
           key=="message" ||
           key=="parent")
        {
            continue;
        }

        fs::copy_file(
            ".mygit/objects/" + value,
            key,
            fs::copy_options::
                overwrite_existing
        );
    }

    Commit::updateHead(id);

    std::cout
        << "Checked out commit "
        << id
        << "\n";
}

void Repository::status()
{
    int head =
        Commit::getHead();

    if(head==-1)
    {
        std::cout
            << "No commits\n";
        return;
    }

    std::string metadata =
        ".mygit/commits/"
        + std::to_string(head)
        + "/metadata.txt";

    std::ifstream fin(metadata);

    std::string line;

    bool clean=true;

    while(std::getline(fin,line))
    {
        auto pos =
            line.find('=');

        if(pos==std::string::npos)
            continue;

        std::string file =
            line.substr(0,pos);

        std::string hash =
            line.substr(pos+1);

        if(file=="id" ||
           file=="message" ||
           file=="parent")
        {
            continue;
        }

        if(!fs::exists(file))
        {
            std::cout
                << "Deleted: "
                << file
                << "\n";

            clean=false;
            continue;
        }

        std::string current =
            hashFile(file);

        if(current!=hash)
        {
            std::cout
                << "Modified: "
                << file
                << "\n";

            clean=false;
        }
    }

    if(clean)
    {
        std::cout
            << "Working tree clean\n";
    }
}

void Repository::diff(
    const std::string& filename
)
{
    int head = Commit::getHead();

    if(head==-1)
    {
        std::cout
            << "No commits\n";
        return;
    }

    std::ifstream meta(
        ".mygit/commits/"
        + std::to_string(head)
        + "/metadata.txt"
    );

    std::string line;
    std::string targetHash;

    while(std::getline(meta,line))
    {
        auto pos = line.find('=');

        if(pos==std::string::npos)
            continue;

        std::string file =
            line.substr(0,pos);

        if(file==filename)
        {
            targetHash =
                line.substr(pos+1);
            break;
        }
    }

    if(targetHash.empty())
    {
        std::cout
            << "File not tracked\n";
        return;
    }

    std::ifstream committed(
        ".mygit/objects/"
        + targetHash
    );

    std::ifstream current(
        filename
    );

    std::string oldLine;
    std::string newLine;

    std::cout
        << "--- committed\n"
        << "+++ current\n\n";

    while(true)
    {
        bool a =
            (bool)std::getline(
                committed,
                oldLine
            );

        bool b =
            (bool)std::getline(
                current,
                newLine
            );

        if(!a && !b)
            break;

        if(oldLine!=newLine)
        {
            if(a)
                std::cout
                    << "- "
                    << oldLine
                    << "\n";

            if(b)
                std::cout
                    << "+ "
                    << newLine
                    << "\n";
        }
    }
}

void Repository::branch(
    const std::string& name
)
{
    std::ofstream out(
        ".mygit/branches/"
        + name
    );

    out
        << Commit::getHead();

    std::cout
        << "Created branch "
        << name
        << "\n";
}

void Repository::listBranches()
{
    for(auto& f :
        fs::directory_iterator(
            ".mygit/branches"
        ))
    {
        std::cout
            << f.path().filename()
                   .string()
            << "\n";
    }
}

void Repository::checkoutBranch(
    const std::string& name
)
{
    std::ifstream in(
        ".mygit/branches/"
        + name
    );

    if(!in)
    {
        std::cout
            << "Branch not found\n";
        return;
    }

    int commit;

    in >> commit;

    checkout(commit);

    std::cout
        << "Switched to "
        << name
        << "\n";
}