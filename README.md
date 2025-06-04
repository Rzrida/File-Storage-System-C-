# File-Storage-System-Cpp-


#  File Storage System - Virtual Hard Disk Simulation

A C++ based simulation of a file storage system using a 10MB Virtual Hard Disk (VHD). This educational project replicates the core functionalities of modern file systems—like file creation, deletion, modification, defragmentation, and metadata management—through custom data structures.

![image](https://github.com/user-attachments/assets/b9b5fd8f-2e27-410f-8dc5-87c816933128)


##  Introduction

This project implements a simplified **Virtual Hard Disk (VHD)** that functions like a physical storage system. It includes hierarchical directory management, file metadata handling, and memory block management—all simulated within a single 10MB file named `File_System`.



##  Project Objectives

* Build a virtual file storage environment for educational purposes.
* Support file operations: create, view, modify, delete, copy (to/from Windows).
* Manage memory using address tracking and block allocation.
* Implement defragmentation to handle fragmented memory.
* Optimize operations using appropriate data structures.



## System Architecture

The 10MB `File_System` file is divided into:

| Section                   | Size | Description                                              |
| ------------------------- | ---- | -------------------------------------------------------- |
| Metadata (File Directory) | 1MB  | Stores filenames and their starting addresses.           |
| Address Min-Heap          | 1MB  | Maintains free block addresses for efficient allocation. |
| File Content Area         | 8MB  | Stores actual file data using 1024-byte blocks.          |



##  Key Features

* Initialize file system from scratch or load from file.
* Create and add files into the virtual disk.
* Delete files and reclaim memory.
* Modify existing files.
* Copy files between virtual disk and Windows.
* View file contents.
* Defragment memory blocks for optimized storage.



##  Technologies Used

* **Language:** C++
* **Standard Libraries:** STL (Vectors, Maps, Priority Queues, etc.)
* **Binary File Handling:** `fstream` for I/O



## Data Structures

| Component          | Data Structure                       | Purpose                                     |
| ------------------ | ------------------------------------ | ------------------------------------------- |
| File Directory     | `vector<FileName>` + `unordered_map` | Efficient lookup & indexed storage          |
| Free Block Manager | `priority_queue<FileAddress>`        | Min-heap for smallest available address     |
| File Content       | `linked list of ContentArea`         | Non-contiguous block linkage                |
| File Manager       | Hybrid of vector + map               | Combines indexing and direct file retrieval |


 **Available operations:**

   * Add a new file
   * Delete existing files
   * Modify file content
   * View file
   * Copy file to/from Windows
   * Defragment storage

> Note: The system auto-loads from `File_System` if it already exists, otherwise it initializes a new file.

<img width="848" alt="Screenshot 2025-06-04 at 11 25 11 PM" src="https://github.com/user-attachments/assets/ca9679ff-179c-4c54-8b36-4a6f6dd63aea" />


## Challenges & Solutions

###  Challenge: Efficient File Lookup

**Solution:** Used `unordered_map` for O(1) access based on filenames.

###  Challenge: Fragmentation Management

**Solution:** Used `priority_queue` to manage and reuse free addresses optimally.

###  Challenge: Handling Non-Contiguous File Storage

**Solution:** Implemented a `linked list` for each file's block addresses.



##  Future Work

* Add multi-user support with authentication.
* Implement directory trees (nested folders).
* Build a GUI for better user interaction.
* Integrate background defragmentation.
* Improve error handling and validation.


##  External Tools Used

* Google & YouTube (for debugging & learning)
* AI tools (for assistance in design & documentation)



##  Conclusion

This project demonstrates the power of combining data structure principles with file handling techniques to simulate a real-world problem. It offers a hands-on, low-level understanding of how file systems work under the hood, with a focus on performance, modularity, and extensibility.


