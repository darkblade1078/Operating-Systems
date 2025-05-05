#include <algorithm>
#include <iostream> // For error messages (optional)

#include "cse4733/FileSystem.hpp"
#include "cse4733/FileAlreadyExistsException.hpp"
#include "cse4733/FileMissingException.hpp"
#include "cse4733/NoAvailableInodeException.hpp"
#include "cse4733/UnformattedFilesystemException.hpp"

namespace cse4733
{

    FileSystem::FileSystem(size_t diskSize, size_t blockSize)
        : diskSize(diskSize), blockSize(blockSize),
          blockManager(diskSize / blockSize), inodeTable(diskSize / (blockSize * 10))
    {
        // Initialize the filesystem with a root directory and empty inode table.
    }

    FileSystem::~FileSystem()
    {
        // Destructor - no special cleanup needed for this in-memory filesystem
    }

    bool FileSystem::createFile(const std::string &filename)
    {
        // TODO:
        // 1. Check if the filesystem has been formatted
        //    a. If not, throw an UnformattedFilesystemException
        // 2. Try: Attempt to allocate a new inode
        //    a. If successful, add the file to the root directory, return true
        // 3. Any exceptions thrown should be caught and handled and return false

        // Check if the filesystem has been formatted
        if (!isFormatted)
            throw UnformattedFilesystemException();

        // Attempt to allocate a new inode
        try 
        {

            // Allocate a new inode
            int inodeIndex = allocateInode();

            // If successful, add the file to the root directory, return true
            rootDirectory.addFile(filename, inodeIndex);

            return true;
        }
        // Any exceptions thrown should be caught and handled and return false
        catch (const FileAlreadyExistsException &e)
        {
            std::cerr << "File already exists: " << e.what() << std::endl;
            return false;
        }
        catch (const NoAvailableInodeException &e)
        {
            std::cerr << "No available inode: " << e.what() << std::endl;
            return false;
        }
        catch (const std::exception &e)
        {
            std::cerr << "An error occurred: " << e.what() << std::endl;
            return false;
        }
    }

    bool FileSystem::deleteFile(const std::string &filename)
    {
        // TODO:
        // 1. Check if the filesystem has been formatted
        //    a. If not, throw an UnformattedFilesystemException
        // 2. Try: Find the inode index for the file
        //    a. Get the inode for the file
        //    b. Free the blocks associated with the file
        //    c. Release the inode
        //    d. Remove the file from the root directory
        //    e. Return true
        // 3. Catch: FileMissingException and return false

        // Check if the filesystem has been formatted
        if (!isFormatted)
            throw UnformattedFilesystemException();

        // Try: Find the inode index for the file
        try
        {

            int inodeIndex = findInode(filename);

            // Get the inode for the file
            Inode &inode = inodeTable[inodeIndex];

            // Free the blocks associated with the file
            for (int blockIndex : inode.directBlocks)
                blockManager.freeBlock(blockIndex);

            // Release the inode
            releaseInode(inodeIndex);

            // Remove the file from the root directory
            rootDirectory.removeFile(filename);

            // Return true
            return true;
        }
        // Catch: FileMissingException and return false
        catch (const FileMissingException &e)
        {
            return false;
        }
    }

    bool FileSystem::writeFile(const std::string &filename, const std::string &data)
    {
        // TODO:
        // 1. Check if the filesystem has been formatted
        //    a. If not, throw an UnformattedFilesystemException
        // 2. Find the inode index for the file
        // 3. Get the inode for the file
        // 4. Free the blocks associated with the file
        // 5. Write the data to blocks
        // 6. Update inode with new block information
        // 7. Return true

        // Check if the filesystem has been formatted
        if (!isFormatted)
            throw UnformattedFilesystemException();

        // Find the inode index for the file
        int inodeIndex = findInode(filename);

        // Get the inode for the file
        Inode &inode = inodeTable[inodeIndex];

        // Free the blocks associated with the file
        for (int blockIndex : inode.directBlocks)
            blockManager.freeBlock(blockIndex);

        // Write the data to blocks
        std::vector<int> blockIndexes = writeDataToBlocks(data);

        // Update inode with new block information
        inode.directBlocks = blockIndexes;

        return true;
    }

    std::string FileSystem::readFile(const std::string &filename)
    {
        // TODO:
        // 1. Check if the filesystem has been formatted
        //    a. If not, throw an UnformattedFilesystemException
        // 2. Try: Find the inode index for the file
        //    a. Get the inode for the file
        //    b. Read the data from the blocks
        //    c. Return the data
        // 3. Catch: FileMissingException and return empty string

        // Check if the filesystem has been formatted
        if (!isFormatted)
            throw UnformattedFilesystemException();

        // Try: Find the inode index for the file
        try
        {
            int inodeIndex = findInode(filename);

            // Get the inode for the file
            Inode &inode = inodeTable[inodeIndex];

            // Read the data from the blocks
            std::string data = readDataFromBlocks(inode.directBlocks);

            return data;
        }
        // Catch: FileMissingException and return empty string
        catch (const FileMissingException &e)
        {
            return "";
        }
    }

    std::vector<std::string> FileSystem::listFiles()
    {
        if (!isFormatted)
        {
            throw UnformattedFilesystemException(); // Return empty if the filesystem has not been formatted
        }

        return rootDirectory.listFiles();
    }

    bool FileSystem::format()
    {
        // TODO:
        // 1. Clear the inode table
        // 2. Reset the root directory
        // 3. Reset the block manager
        // 4. Set the filesystem as formatted
        // 5. Return true

        // Clear the inode table
        inodeTable.clear();

        // Reset the root directory
        rootDirectory = Directory();

        // Reset the block manager
        blockManager = BlockManager(diskSize / blockSize);

        // Set the filesystem as formatted
        isFormatted = true;

        // Return true
        return true;
    }

    int FileSystem::findInode(const std::string &filename)
    {
        if (!isFormatted)
        {
            throw UnformattedFilesystemException(); // Filesystem has not been formatted
        }
        return rootDirectory.getInodeIndex(filename);
    }

    unsigned int FileSystem::allocateInode()
    {
        // TODO:
        // 1. Check if the filesystem has been formatted
        //    a. If not, throw an UnformattedFilesystemException
        // 2. Find the first available inode
        // 3. If found, allocate the inode and return the index
        // 4. If not found, throw a NoAvailableInodeException

        // Check if the filesystem has been formatted
        if (!isFormatted)
            throw UnformattedFilesystemException();

        
        // If the inode table is empty after formatting, initialize it with new inodes
        if (inodeTable.empty()) {
            // Add enough inodes to match the initial capacity
            size_t inodeCapacity = diskSize / (blockSize * 10);
            for (size_t i = 0; i < inodeCapacity; i++) {
                Inode newInode;
                newInode.isAllocated = false;
                inodeTable.push_back(newInode);
            }
        }

         // Find the first available inode
        for (size_t i = 0; i < inodeTable.size(); ++i)
        {
            if (!inodeTable[i].isAllocated)
            {
                // Allocate the inode
                inodeTable[i].isAllocated = true;
                return i; // Return the index of the allocated inode
            }
        }

        throw NoAvailableInodeException();
    }

    void FileSystem::releaseInode(int inodeIndex)
    {
        if (inodeIndex >= 0 && static_cast<size_t>(inodeIndex) < inodeTable.size())
        {
            inodeTable[inodeIndex].deallocate();
        }
    }

    std::vector<int> FileSystem::writeDataToBlocks(const std::string &data)
    {
        //TODO:
        // 1. Create vector to store block indexes
        // 2. Calculate the number of blocks needed
        // 3. For each block needed
        //    a. Allocate a block
        //    b. If allocation fails, free already allocated blocks and return empty vector
        //    c. Calculate the offset and length of the data to write
        //    d. Write the data to the block
        // 4. Return the vector of block indexes

        // Create vector to store block indexes
        std::vector<int> blockIndexes;

        // Calculate the number of blocks needed
        size_t dataSize = data.size();

        // For each block needed
        size_t blocksNeeded = (dataSize + blockSize - 1) / blockSize;

        for (size_t i = 0; i < blocksNeeded; ++i)
        {
            // Allocate a block
            int blockIndex = blockManager.allocateBlock();
            if (blockIndex == -1)
            {
                // If allocation fails, free already allocated blocks and return empty vector
                for (int index : blockIndexes)
                    blockManager.freeBlock(index);

                return {};
            }

            // Calculate the offset and length of the data to write
            size_t offset = i * blockSize;
            size_t length = std::min(blockSize, dataSize - offset);

            // Write the data to the block
            blockManager.writeBlock(blockIndex, data.substr(offset, length));

            // Store the block index
            blockIndexes.push_back(blockIndex);
        }

        // Return the vector of block indexes
        return blockIndexes;
    }

    std::string FileSystem::readDataFromBlocks(const std::vector<int> &blockIndexes)
    {
        // TODO:
        // 1. Create a string to store the data
        // 2. Get the block size
        // 3. For each block index
        //    a. Read the block data and append to the string
        // 4. Return the data

        // Create a string to store the data
        std::string data;

        // Get the block size
        // No need for this since we can just do a for each loop instead
        //size_t blockSize = this->blockSize;

        // For each block index
        for (int blockIndex : blockIndexes)
        {
            // Read the block data and append to the string
            std::string blockData = blockManager.readBlock(blockIndex);
            data.append(blockData);
        }

        // Return the data
        return data;
    }

    size_t FileSystem::getFreeBlockCount() const
    {
        return blockManager.getFreeBlockCount(); // Retrieve the count of free blocks from BlockManager
    }

    size_t FileSystem::getTotalBlockCount() const
    {
        return blockManager.getTotalBlocks(); // Retrieve the total count of blocks from BlockManager
    }

} // namespace cse4733
