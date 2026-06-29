 """# MiniGit — A Git-like Version Control System in C++

A lightweight, educational version control system built from scratch in C++ that mimics core Git functionality, including staging, committing, branching, and file tracking using content-addressable storage.

---

## 🚀 Features

* **📦 Content-Addressable Object Storage**
    * Files are uniquely identified and stored using hash-based identifiers derived from their content.
* **🧾 Staging Area**
    * Tracks modified, new, or deleted files before a commit is created, using an internal index system.
* **📌 Commit System**
    * Stores permanent snapshots of the project state along with crucial metadata (Commit ID, message, timestamp, and parent pointer).
* **🕰️ Commit History (Log)**
    * Traverses the commit chain sequentially like a linked list to display the history of the repository.
* **🔄 Checkout**
    * Restores the entire project working directory to the exact state of any historic commit ID.
* **📊 Status Tracking**
    * Compares the working directory against the staging index and HEAD to detect modified, untracked, and deleted files.
* **🔍 Diff Tool**
    * Line-by-line comparison between the current version in the working directory and the last committed version.
* **🌿 Branching System**
    * Supports lightweight branch creation and context switching using independent pointers to specific commits.

---

## 🏗️ Architecture Overview

The system pipeline structures data flow sequentially from modification to persistent object storage:
