MiniGit — A Git-like Version Control System in C++

A lightweight, educational version control system built from scratch in C++ that mimics core Git functionality including staging, committing, branching, and file tracking using content-addressable storage.

🚀 Features
📦 Content-addressable object storage
Files stored using hash-based identifiers
🧾 Staging area
Tracks files before commit using an index system
📌 Commit system
Stores snapshots with metadata (id, message, parent)
🕰️ Commit history (log)
Traverse commit chain like a linked list
🔄 Checkout
Restore project state from any commit
📊 Status tracking
Detects modified and deleted files
🔍 Diff tool
Compares working directory with committed version
🌿 Branching system
Create and switch branches using pointers to commits
🏗️ Architecture Overview
Working Directory
      ↓
   Staging Area (index.txt)
      ↓
   Commit Object
      ↓
 Metadata + File Hashes
      ↓
 Content Addressable Storage (.mygit/objects)
      ↓
 Commit Graph (.mygit/commits)
      ↓
 Branch Pointers (.mygit/branches)
⚙️ How it works
Each file is hashed and stored in .mygit/objects/
Staging area maintains a file → hash mapping
Commit stores snapshot metadata and file hashes
HEAD tracks the current commit
Branches are simple pointers to commits
🧪 Supported Commands
mygit init
mygit add <file>
mygit commit "<message>"
mygit log
mygit checkout <commit_id>
mygit status
mygit diff <file>
mygit branch
mygit branch <name>
mygit switch <name>
🛠️ Tech Stack
C++
STL (filesystem, fstream, unordered_map)
SHA-like hashing (custom implementation)
File system manipulation
📂 Project Structure
mini_git/
│
├── src/
│   ├── main.cpp
│   ├── Repository.cpp
│   ├── StagingArea.cpp
│   ├── Commit.cpp
│   ├── Utils.cpp
│
├── .mygit/
│   ├── objects/
│   ├── commits/
│   ├── staging/
│   ├── branches/
│   └── HEAD
💡 Key Learnings
File system programming in C++
Persistent storage design
Hash-based indexing
Version control system internals
State restoration algorithms
Branching as pointer manipulation
🧠 Inspiration

Built to understand how Git works internally by implementing a simplified version from scratch.

📌 Future Improvements
3-way merge system
Conflict resolution
Rebase support
Compression for objects
Distributed syncing (remote repo)