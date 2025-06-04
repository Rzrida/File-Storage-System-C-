#pragma once
#include <iostream> 
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include <cstring>
#include <list>
#include <iomanip>
#include <set> 
#include <unordered_map>
#include "helper_Function.h"

using namespace std;

// ------------------------- FILE SYSTEM MANAGER -------------------------
class FileSystemManager {

private:
    string fileName;
    priority_queue<FileAddress, vector<FileAddress>, greater<FileAddress>>  addressminHeap; // min Heap using built in queue and vectors

    vector<FileName> fileDirectoryList;
    unordered_map<string, int> FileNames_Set; //unorderedmap to make O(1) search <name, index>

    vector<ContentWriter> fileContent;

    static const int FILE_SYSTEM_SIZE = 10 * 1024 * 1024;
    static const int FILE_TABLE_SIZE = 1 * 1024 * 1024;
    static const int FREE_LIST_SIZE = 2 * 1024 * 1024;
    static const int DATA_SIZE = 8 * 1024 * 1024;
    const int totalBlocks = 8192;
    const int dataBlockSize = 1024;
    int currentAddress = 2097152;
public:
   

    FileSystemManager(const string& fileName) : fileName(fileName) {}

    void initialize() {


        // Check if the file exists and is empty BEFORE creating or truncating it
        bool isEmpty = true;
        ifstream infile(fileName, ios::ate | ios::binary); // Open existing file in read-only mode
        if (infile.is_open()) {
            if (infile.tellg() > 0) {
                isEmpty = false;
            }
            infile.close();
        }

        ofstream file(fileName, ios::in | ios::out | ios::binary); // Now safe to open
        if (!file) {
            file.open(fileName, ios::out | ios::binary);
            if (!file) {
                cerr << "Error creating file!" << endl;
                return;
            }
        }
  
        // Check if the file contains only spaces or spaces at the 2,097,152nd byte
        ifstream readFile(fileName, ios::binary);
        if (!readFile) {
            cerr << "Error opening file for reading!" << endl;
            return;
        }

        char byte;
        readFile.seekg(0, ios::beg); // Start from the beginning
        bool allSpaces = true;

        // Check if the file is filled only with spaces
        while (readFile.get(byte)) {
            if (byte != ' ') {
                allSpaces = false;
                break;
            }
        }

        

        readFile.close();
        if (isEmpty || allSpaces) {
            auto writePadding = [&](int sizeInBytes) {
                for (int i = 0; i < sizeInBytes; ++i) {
                    file.put(' ');
                }

                };
            writePadding(FILE_SYSTEM_SIZE);
            setMinHeap();
        }
        else {
            ifstream readFile(fileName, ios::binary);
            if (!readFile) {
                cerr << "Error opening file for reading!" << endl;
                return;
            }

            for (int i = FILE_TABLE_SIZE; i < (FREE_LIST_SIZE-127); i += 128) {
                readFile.seekg(i, ios::beg);  // Move to the correct block

                char buffer[128];
                readFile.read(buffer, 128);  // Read the block of 128 bytes

                if (readFile.gcount() >= 8) {
                    // Extract the first 7 bytes as a string
                    string addressStr(buffer, 8);

                    // Convert the string to a long long value (ASCII number to integer)
                    long long address = atoll(addressStr.c_str());

                    if (address < 2097152) continue;
                    // Create a FileAddress object and set the address
                    FileAddress fa;
                    fa.setAddress(address);
                    // Push it into the min-heap
                    addressminHeap.push(fa);
                }
             
               
            }

            char buffer[500];

            for (int i = 0; i < FILE_TABLE_SIZE; i += 500) {
                readFile.seekg(i, ios::beg);
                readFile.read(buffer, 500);

                // Check if the block is empty (all spaces or zeros)
                bool isEmptyBlock = true;
                for (int j = 0; j < 500; ++j) {
                    if (buffer[j] != ' ' && buffer[j] != '\\0') {
                        isEmptyBlock = false;
                        break;
                    }
                }

                // If the block is empty, break out of the loop
                if (isEmptyBlock) {
                    cout << "Empty block found at position " << i << ", exiting loop.\n";
                    break;
                }

                string temp(buffer, 500);
                string name = "";
                long long address = -1;

                // Scan manually for last 7-digit number
                for (size_t j = 0; j <= temp.size() - 7; ++j) {
                    if (isdigit(temp[j]) &&
                        isdigit(temp[j + 1]) &&
                        isdigit(temp[j + 2]) &&
                        isdigit(temp[j + 3]) &&
                        isdigit(temp[j + 4]) &&
                        isdigit(temp[j + 5]) &&
                        isdigit(temp[j + 6]) &&
                        !isdigit(temp[j + 7]))  // Make sure it's exactly 7 digits
                    {
                        string possibleAddr = temp.substr(j, 7);
                        address = atoll(possibleAddr.c_str());
                        name = temp.substr(0, j);
                    }
                }

                // Trim trailing spaces from name
                size_t end = name.find_last_not_of(" \t\r\n");
                if (end != string::npos)
                    name = name.substr(0, end + 1);

                cout << "Entry " << (i / 500) << ": Name = '" << name << "', Address = " << address << endl;
                FileAddress first_address;
                first_address.setAddress(address);
                long long currentAddress = address;
                string cont = "";

                ifstream readFile(fileName, ios::binary);
                if (!readFile) {
                    cerr << "Error opening file for reading!" << endl;
                    return;
                }
                priority_queue<FileAddress, vector<FileAddress>, greater<FileAddress>>  tempAddr; // min Heap using built in queue and vectors
                FileAddress fa;
                fa.setAddress(address);
                tempAddr.push(fa);
                while (true) {
                    if (currentAddress < 0) break;

                    readFile.seekg(currentAddress, ios::beg);
                    char buffer[1024];
                    readFile.read(buffer, 1024);

                    // Look for \0 in buffer (corrected)
                    int nullPos = -1;
                    for (int j = 0; j < 1024; ++j) {
                        if (buffer[j] == '\\' && buffer[j + 1] == '0') {  
                            nullPos = j-1;
                            break;
                        }

                    }

                    if (nullPos != -1) {
                        cout << "Found null terminator at position: " << nullPos << endl;
                        for (int k = 0; k < nullPos; ++k) {
                            cont += buffer[k];  // Only append up to \0
                        }
                        break;
                    }
                    else {
                        cont.append(buffer, 1016);  // Add 1016 bytes if no \0 found

                        // Read next address from last 7 bytes
                        string nextAddrStr(buffer + 1016, 7);
                        long long nextAddr = atoll(nextAddrStr.c_str());

                        if (nextAddr == 0 || nextAddr == currentAddress) break;
                        currentAddress = nextAddr;
                        FileAddress fa;
                        fa.setAddress(address);
                        tempAddr.push(fa);
                    }
                }


                readFile.close();

                // Clean trailing spaces
                size_t lastChar = cont.find_last_not_of(" \t\r\n");
                if (lastChar != string::npos)
                    cont = cont.substr(0, lastChar + 1);

                cout << "Full content: " << cont << endl;

                fileDirectoryList.push_back(FileName(name, first_address));  // Add to list
                FileNames_Set.emplace(name, FileNames_Set.size()); // add to unordered map

                //insert content 
                fileContent.push_back(ContentWriter(cont, tempAddr, first_address, name));  // Add to content list 
                
            }
            auto writePadding = [&](int sizeInBytes) {
                for (int i = 0; i < sizeInBytes; ++i) {
                    file.put(' ');
                }

                };
            writePadding(FILE_SYSTEM_SIZE);



            file.close();
        }

    }

    void setMinHeap() {
        for (int i = 0; i < totalBlocks; ++i) {
            FileAddress fa;
            fa.setAddress(currentAddress);
            addressminHeap.push(fa);
            currentAddress += dataBlockSize;
        }
    }

    
    void writeSecondBlock() {
        fstream file(fileName, ios::in | ios::out);
        if (!file) {
            cerr << "Unable to open file for writing FileAddress blocks.\n";
            return;
        }
        priority_queue<FileAddress, vector<FileAddress>, greater<FileAddress>>  tempHeap = addressminHeap; // min Heap using built in queue and vectors

        file.seekp(FILE_TABLE_SIZE, ios::beg);

        while (!tempHeap.empty()) {
            FileAddress fa;
            fa.setAddress(tempHeap.top());
            fa.serialize(file);
            tempHeap.pop();
        }

        file.close();
    }

 

    void writingToFirstBlock() {
        fstream file(fileName, ios::in | ios::out);
        if (!file) {
            cerr << "Unable to open file for writing FileAddress blocks.\n";
            return;
        }

        vector<FileName> tempName = fileDirectoryList; // Copy the list

        file.seekp(0, ios::beg);

        while (!tempName.empty()) {
            FileName fa = tempName.front();  // Get the first FileName
            fa.serialize(file);             // Serialize into the file
            tempName.erase(tempName.begin()); // Remove the processed element
        }

        file.close();
    }


    void writingToLasttBlock() {
        fstream file(fileName, ios::in | ios::out);
        if (!file) {
            cerr << "Unable to open file for writing FileAddress blocks.\n";
            return;
        }

        if (!file.is_open()) {
            cerr << "Failed to open the file!" << endl;
            return;
        }

        // Copy the list to process
        vector<ContentWriter> tempName = fileContent;

        file.seekp(0, ios::beg);

        while (!tempName.empty()) {
            ContentWriter fa = tempName.front(); // Get the first ContentWriter in the list
            fa.writeToFile(fileName);           // Process it
            tempName.erase(tempName.begin());               // Remove the processed element
        }

        file.close();
        if (file.fail()) {
            cerr << "Failed to close the file properly.\n";
        }
        else {
            //cout << "All content blocks written successfully.\n";
        }
    }

    bool isFileNameUnique(const string& name) {
        return (FileNames_Set.find(name) == FileNames_Set.end()); // here unordered set help in quick search reduced time complexity to O(1)
    }


    void printMinHeap() {
        priority_queue<FileAddress, vector<FileAddress>, greater<FileAddress>> tempQueue = addressminHeap; // Make a copy
        while (!tempQueue.empty()) {
            cout << tempQueue.top().getAddress() << endl; // Print the address of the top element
            tempQueue.pop(); // Remove the top element
        }
    }

    void addFileToDirectory(const string& name, string cont = "RidaMawaTazeen", long long addr=0) {
        if (isFileNameUnique(name)) {
             addr = addressminHeap.top();
            fileDirectoryList.push_back(FileName(name, addr));  // Add to list
            FileNames_Set.emplace(name, FileNames_Set.size()); // add to unordered map

            //insert content 
            fileContent.push_back(ContentWriter(cont, addressminHeap, addr, name));  // Add to content list 
        }
        else {
            cout << "File name already exists." << endl;
        }
    }

    string getFileContent(string n) {
        if (FileNames_Set.find(n) != FileNames_Set.end()) {
            int idx = FileNames_Set[n];
            return fileContent[idx].getContent();
        }
        return " "; // File not found
    }

    void viewFile(string n) {
        if (FileNames_Set.find(n) == FileNames_Set.end()) {
            cout << "File is not available!" << endl;
        }
        else {
            cout << "File content: ";
            cout << getFileContent(n) << endl;
        }
    }


    void copyFilefromWindow(string name, string dir) {
        // Construct the full path to the file
        string filePath = dir + "\\" + name;

        // Open the file in read mode
        ifstream file(filePath);

        // Check if the file was opened successfully
        if (!file) {
            cout << "Error: File could not be opened." << endl;  // Return error message if file can't be opened
            return;
        }

        // Read the file's content into the fileContent string
        string line;
        string fileContent;
        while (getline(file, line)) {
            fileContent += line;  // Append each line to fileContent with newline
        }


        // Close the file
        file.close();

        addFileToDirectory(name, fileContent);
    }

    void copyFileToWindow(const string& n) {
        if (isFileNameUnique(n)) {
            cout << "File is not available!" << endl;
            return;
        }

        string fileContent = getFileContent(n);

        ofstream outFile(n);

        if (!outFile) {
            cout << "Error: Could not open the file for writing." << endl;
            return;
        }

        outFile << fileContent;

        outFile.close();

        cout << "File successfully written to: " << n << endl;
    }


    void printDirectoryList() const {
        for (const auto& file : fileDirectoryList) {
            cout << file.getName() << " " << file.getAddress() << endl;
        }
    }
    void printFileName() const {
        for (const auto& file : fileDirectoryList) {
            cout << file.getName() << endl;
        }
    }
   
    void deleteFile(const string& name) {
        if (FileNames_Set.find(name) == FileNames_Set.end()) {
            cout << "Invalid file!" << endl;
            return;
        }

        int idx = FileNames_Set[name]; // Get the index of the file

        // Return address to heap
        fileContent[idx].addrInMinHeap(addressminHeap);

        // Remove from fileDirectoryList and fileContent
        fileDirectoryList.erase(fileDirectoryList.begin() + idx);
        fileContent.erase(fileContent.begin() + idx);

        // Remove from map
        FileNames_Set.erase(name);

        // Update indices in the map for files after the deleted index
        for (int i = idx; i < fileDirectoryList.size(); ++i) {
            FileNames_Set[fileDirectoryList[i].getName()] = i;
        }

        cout << "File \"" << name << "\" deleted successfully." << endl;
    }

    void modifyFile(const string& filename, const string& newContent) {
        if (FileNames_Set.find(filename) == FileNames_Set.end()) return;

        int idx = FileNames_Set[filename];
        fileContent[idx].modify(newContent, addressminHeap);
    }

    void defragmentation() {
        for (size_t i = 0; i < fileContent.size(); ++i) {
            vector<long long> blocks = fileContent[i].getUsedBlocks();

            for (int j = 0; j < blocks.size(); ++j) {
                long long currentAdr = blocks[j];

                if (addressminHeap.empty()) break;

                long long freeAdr = addressminHeap.top();

                if (currentAdr > freeAdr) {
                    addressminHeap.pop();

                    // Move content
                    fileContent[i].changeBlock(freeAdr, j);    // Update block address


                    FileAddress fa;
                    fa.setAddress(currentAdr);
                    addressminHeap.push(fa); // Reclaim old address
                }
            }
            fileDirectoryList[i].changeAdr(fileContent[i].getUsedBlocks()[0]);   // Update directory

        }
    }



    void writeToFile() {
        defragmentation();
        writingToFirstBlock();
        writeSecondBlock();
        writingToLasttBlock();
    }

};