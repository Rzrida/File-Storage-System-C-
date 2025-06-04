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
#include <unordered_set>
using namespace std;

// ------------------------- FILE ADDRESS BLOCK (128B) -------------------------
class FileAddress {
private:
    int address;

public:
    FileAddress() : address(-1) {}

    void setAddress(int byteOffset) {
        address = byteOffset;
    }

    int getAddress() const {
        return address;
    }

    void print() const {
        cout << address << "\n";
    }

    string padToSize(const string& data, int size) const {
        if (data.size() < size) {
            return data + string(size - data.size(), ' ');
        }
        return data.substr(0, size);
    }

    void serialize(ostream& out) const {
        string result = padToSize(to_string(address), 128);
        out << result;
    }

    bool operator<(const FileAddress& f) const {
        return address < f.address;
    }

    bool operator>(const FileAddress& f) const {
        return address > f.address;
    }

    operator long long() const {  
        return static_cast<long long>(address); 
    }

};



struct FileName {
    string name;
    long long addr;
    char block[500]; // Fixed 500B block: [0–491] name, [492–499] addr

    FileName(string n = " ", long long a = 0) : name(n), addr(a) {

        memset(block, 0, 500);  // Clear the block to ensure no junk data

        // Truncate the name to fit within 491 bytes (including null terminator)
        name = n.substr(0, 491);  // Store only the first 491 characters of the name
        addr = a;
    }

    const char* getBlock() const {
        return block;
    }

    string getFileName() const {
        return name + ' ' + to_string(addr);
    }

    string getName() const {
        return name;
    }

    long long getAddress() const {
        return addr;
    }
    void changeAdr(long long a) {
        addr = a;
    }
    string padToSize(const string& data, int size) const {
        if (data.size() < size) {
            return data + string(size - data.size(), ' ');
        }
        return data.substr(0, size);
    }

    void serialize(ostream& out) const {
        // Ensure the result has a total of 500 characters (name + space + addr)
        string result = padToSize(getFileName(), 500);
        out.write(result.c_str(), result.size());
    }
};

class ContentArea {
    string content;
    long long addr;
    string block;

public:
    ContentArea(string c = " ", long long adr = 0) : content(c), addr(adr) {}

    string returnDetail() const {
        return (content + ' ');
    }

    void display() const {
        cout << "Content: " << returnDetail() << "\n";
    }
    string getData() const {
        return content;
    }
    void setData(string c) {
        content = c;
    }

    long long getAddress() {
        return addr;
    }
};

class ContentWriter {


    //const int HEADER_SIZE = 2097152;     // 2MB
    //const int RESERVED_SIZE = 8388608;   // 8MB
    const int block_size = 1024;
    int numBlocks;
    string fileName;
    string data;
    vector<long long> usedBlocks;
    list<ContentArea> contentChains;

public:
   
    ContentWriter(string content, priority_queue<FileAddress, vector<FileAddress>, greater<FileAddress>>& freeBlock, long long adr, string f) {
        data = content;
        string fullData = content;
        fileName = f;
        float totalLength1 = static_cast<float>(fullData.length());
        long long startOffset = adr;
        int blockSize = 1016;

        /*   size_t is an unsigned integer type used to represent sizes or lengths in C++.It's commonly used with functions like sizeof or when working with arrays and container sizes.

               It's always non-negative (no negative values).

               Its size depends on the system(32 - bit or 64 - bit), so it can handle large sizes safely.*/

               //cout << totalLength1;
        float x = (totalLength1) / 1016;
        int numB = ceil(static_cast<float>(x));
        numBlocks = numB;

        size_t totalLength = static_cast<size_t> (totalLength1);
        int i = 0;
        do {
            adr = freeBlock.top();
            freeBlock.pop();
            size_t start = i * blockSize;
            size_t end = min(start + blockSize, totalLength);
            string block = fullData.substr(start, end - start);
            ContentArea c = ContentArea(block, adr);
            contentChains.push_back(c);
            usedBlocks.push_back(adr);
            i++;
        } while (i < numBlocks);


    }
    
    vector<long long> getUsedBlocks() {
        return usedBlocks;
    }

    void changeBlock(long long data, int loc) {
        cout << "Inside:" << data  << " At loc "<< loc << endl;
        usedBlocks[loc] = data;
    }


    long long getBlock(int loc) {
        return usedBlocks.at(loc);
    }
    void addrInMinHeap(priority_queue<FileAddress, vector<FileAddress>, greater<FileAddress>>& freeBlock) {
        for (const auto& addr : usedBlocks) {
            FileAddress fa;
            fa.setAddress(addr);
            freeBlock.push(fa);
        }
        usedBlocks.clear(); // Clear the usedBlocks set after re-adding
    }

    void modify(string cont, priority_queue<FileAddress, vector<FileAddress>, greater<FileAddress>>& freeBlock) {
        // Define block size here
        const size_t block_size = 1016;
        data += cont;
        // Calculate the total length of the new content
        string fullData = cont;
        size_t totalLength = fullData.length();

        // If there's existing content in contentChains, check if the last block can accommodate more data
        if (!contentChains.empty()) {
            ContentArea& lastContent = contentChains.back();
            size_t remainingSpaceInLastBlock = block_size - lastContent.getData().length();

            // If the last block has enough space, we can append content to it
            if (remainingSpaceInLastBlock >= totalLength) {
                lastContent.setData(lastContent.getData() + fullData); // Append content to the last block
                return;
            }
            else {
                // If content doesn't fit in the last block, place part of it in the last block
                lastContent.setData(lastContent.getData() + fullData.substr(0, remainingSpaceInLastBlock));
                fullData = fullData.substr(remainingSpaceInLastBlock); // Remaining content
                totalLength -= remainingSpaceInLastBlock; // Remaining content size
            }
        }

        // Now, handle the remaining content in fullData
        while (totalLength > 0) {
            // Allocate a new block from the freeBlock heap
            long long adr = freeBlock.top();
            freeBlock.pop();

            // Get the content to fit in the current block
            size_t sizeToWrite = std::min(block_size, totalLength); // Ensure same type
            string block = fullData.substr(0, sizeToWrite);

            // Create the new ContentArea and add it to the contentChains
            ContentArea newContentArea(block, adr);
            contentChains.push_back(newContentArea);

            // Update the remaining content and totalLength
            fullData = fullData.substr(sizeToWrite);
            totalLength -= sizeToWrite;

            // Mark this block as used
            usedBlocks.push_back(adr);
        }
    }





    string padToSize(const string& data, int size) {
        if (data.size() < size) {
            return data + string(size - data.size(), ' ');
        }
        return data.substr(0, size);
    }

    void serialize(ostream& out, const ContentArea& c, string x) {
        if (!out) {
            cerr << "Error: Output stream is not in a valid state.\n";
            return;
        }

        string serializedData = padToSize(c.returnDetail() + x, 1024);
        out.write(serializedData.c_str(), serializedData.size());
    }


    void writeToFile(const string& filename) {
        fstream file(filename, ios::in | ios::out | ios::binary);
        if (!file) {
            cerr << "Unable to open file for writing FileAddress blocks.\n";
            return;
        }

        // Ensure the sizes of contentChains and usedBlocks match
        if (contentChains.size() != usedBlocks.size()) {
            cerr << "Mismatch between content chains and used block addresses.\n";
            file.close();
            return;
        }

        // Use iterators to traverse both the content chains and the used block addresses
        auto chainIt = contentChains.begin();
        auto blockIt = usedBlocks.begin();
        string x;
        int i = 0;

        while (chainIt != contentChains.end() && blockIt != usedBlocks.end()) {
            long long currentAdr = *blockIt;

            // Seek to the appropriate location in the file
            file.seekp(currentAdr, ios::beg);
            if (file.fail()) {
                cerr << "Error: Could not seek to address " << currentAdr << ".\n";
                break;
            }

            // Determine the value of `x` based on the next block address
            if (next(blockIt) != usedBlocks.end()) {
                x = to_string(*next(blockIt));
            }
            else {
                x = "\\0";
            }

            // Serialize and overwrite the current ContentArea at the specified address
            serialize(file, *chainIt, x);

            // Move to the next content block and address
            ++chainIt;
            ++blockIt;
            ++i;
        }

        file.close();
        if (file.fail()) {
            cerr << "Failed to close the file properly.\n";
        }
    }




    void displayListForward() const {
        cout << "\nTraversing content chains (forward):\n";
        int chainNum = 1;
        for (const auto& chain : contentChains) {
            cout << "\nChain " << chainNum++ << ":\n";
            chain.display(); // Directly call display() on each ContentArea
        }
    }

    ContentWriter& operator=(const ContentWriter& other) {
        if (this != &other) {
            fileName = other.fileName;
            data = other.data;
            usedBlocks = other.usedBlocks;
            contentChains = other.contentChains;  
        }
        return *this;
    }

    string getContent() const {
        return data;
    }
    string getName() const {
        return fileName;
    }

};

