# MiniGit — A Git-like Version Control System in C++

A lightweight, educational version control system built from scratch in C++ that mimics core Git functionality including staging, committing, branching, and file tracking using content-addressable storage.

---

## 🚀 Features

### 📦 Content-addressable object storage
Files stored using hash-based identifiers

### 🧾 Staging area
Tracks files before commit using an index system

### 📌 Commit system
Stores snapshots with metadata (id, message, parent)

### 🕰️ Commit history (log)
Traverse commit chain like a linked list

### 🔄 Checkout
Restore project state from any commit

### 📊 Status tracking
Detects modified and deleted files

### 🔍 Diff tool
Compares working directory with committed version

### 🌿 Branching system
Create and switch branches using pointers to commits

---

## 🏗️ Architecture Overview
