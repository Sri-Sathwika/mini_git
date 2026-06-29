# mini_git

A lightweight, educational Git-like version control system written in C++. **mygit** provides core version control workflows—initialize a repository, stage files, commit snapshots, browse history, compare changes, and manage branches—using a simple command-line interface.

## Features

| Command | Description |
|---------|-------------|
| `init` | Create a new `.mygit` repository in the current directory |
| `add <file>` | Stage a file for the next commit |
| `commit <message>` | Create a commit from staged files |
| `log` | Print commit history (newest to oldest) |
| `status` | Show modified or deleted files vs. the latest commit |
| `diff <file>` | Compare a file against its last committed version |
| `checkout <id>` | Restore tracked files from a commit by numeric ID |
| `branch [name]` | List branches, or create a new branch at the current HEAD |
| `switch <name>` | Check out the commit pointed to by a branch |

## Project Structure

```
mini_git/
├── src/
│   ├── main.cpp          # CLI entry point and command routing
│   ├── Repository.h/cpp  # Core repository operations
│   ├── StagingArea.h/cpp # Staging index and object storage
│   ├── Commit.h/cpp      # HEAD pointer and commit ID management
│   └── Utils.h/cpp       # File I/O and content hashing
└── .gitignore
```

### Internal layout (`.mygit/`)

After `init`, the tool creates a hidden `.mygit` directory:

```
.mygit/
├── HEAD              # Current commit ID (-1 before the first commit)
├── objects/          # Content-addressed file blobs (hash → file content)
├── commits/          # One folder per commit with metadata.txt
├── staging/          # Staging index (index.txt)
└── branches/         # Branch pointers (e.g. main)
```

Each commit stores metadata in `commits/<id>/metadata.txt`:

```
id=<commit_id>
message=<commit_message>
parent=<parent_commit_id>

<file_path>=<content_hash>
...
```

## How It Works

1. **Staging** — `add` reads a file, computes a hash of its contents, copies the blob into `.mygit/objects/`, and appends an entry to the staging index.
2. **Committing** — `commit` assigns the next sequential ID, writes metadata (message, parent, staged files), updates `HEAD`, and clears the staging area.
3. **Checkout** — Restores tracked files from a commit’s stored object hashes back into the working directory and moves `HEAD` to that commit.
4. **Status & diff** — Compare working-tree files against the latest commit using the same hash function.

Content hashing uses C++’s `std::hash` on file contents (not SHA-1); this keeps the implementation simple for learning purposes.

## Requirements

- A C++17-capable compiler (`g++`, `clang++`, or MSVC with `/std:c++17`)
- C++17 `<filesystem>` support (link with `-lstdc++fs` on some older GCC versions)

## Build

From the project root:

```bash
g++ -std=c++17 -o mygit src/main.cpp src/Repository.cpp src/StagingArea.cpp src/Commit.cpp src/Utils.cpp
```

On Linux with GCC versions before 9, you may need:

```bash
g++ -std=c++17 -o mygit src/*.cpp -lstdc++fs
```

On Windows with MinGW or MSVC, adjust the compiler command as needed. The executable name used in examples below is `mygit`.

## Usage

```bash
# Initialize a repository
./mygit init

# Stage and commit
./mygit add notes.txt
./mygit commit "Initial commit"

# View history and status
./mygit log
./mygit status

# Compare changes
./mygit diff notes.txt

# Branches
./mygit branch feature
./mygit switch feature
./mygit branch

# Restore a previous commit
./mygit checkout 0
```

## Example Session

```bash
$ ./mygit init
Initialized empty repository

$ echo "hello" > hello.txt
$ ./mygit add hello.txt
Added hello.txt

$ ./mygit commit "Add hello.txt"
Committed as 0

$ echo "world" >> hello.txt
$ ./mygit status
Modified: hello.txt

$ ./mygit diff hello.txt
--- committed
+++ current

- hello
+ hello
+ world
```

## Limitations

This is a **learning project**, not a production VCS. Notable limitations:

- No remote repositories, merges, or rebases
- Sequential numeric commit IDs instead of cryptographic hashes
- Branch switching does not update branch pointers on new commits
- `diff` requires a filename argument (no repo-wide diff)
- Staging index is cleared after each commit; unstaged changes are not tracked between commits

## License

No license file is included. Add one if you plan to distribute or open-source this project.
