#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#include <MemoryAllocator.hpp>
#include <MemoryBlock.hpp>

namespace cse4733
{

    MemoryAllocator::MemoryAllocator(std::size_t total_memory_size)
        : total_memory_size_(total_memory_size),
          free_memory_size_(total_memory_size)
    {
        std::string process_id = FREE_MEMORY_STRING;
        memory_blocks_.emplace_back(0, total_memory_size_, process_id);
    }

    auto MemoryAllocator::allocate(const std::string &process_id, std::size_t block_size) -> std::size_t
    {
        // TODO:
        //     1. Initialize `allocated_address` to 0
        //
        //     2. IF `block_size` is 0 THEN
        //         Throw an invalid argument exception with a message indicating that the block size for allocation is invalid
        //     
        //     3. IF `block_size` is greater than `total_memory_size_` THEN
        //         Throw a runtime error with a message indicating that the block size exceeds the total memory size
        //     
        //     4. Use `std::find_if` to find a memory block in `memory_blocks_` that:
        //         a. Is free (process ID is FREE_MEMORY_STRING)
        //         b. Has a size greater than or equal to `block_size`
        //
        //     5. IF the iterator returned by `std::find_if` is not equal to the end of `memory_blocks_` THEN
        //         a. Set `allocated_address` to the base address of the found memory block
        //         b. Calculate `free_base_address` as the base address of the found memory block plus `block_size`
        //         c. Update `free_memory_size_` as the size of the found memory block minus `block_size`
        //         d. Set the process ID of the found memory block to `process_id`
        //         e. Set the size of the found memory block to `block_size`
        //     
        //         f. IF `free_memory_size_` is greater than 0 THEN
        //             Add a new memory block to `memory_blocks_` with:
        //                 - `free_base_address`
        //                 - `free_memory_size_`
        //                 - `FREE_MEMORY_STRING` as the process ID
        //     
        //     6. ELSE
        //         Throw a runtime error indicating that no suitable memory block was found
        //     
        //     7. Return `allocated_address`

        //initialize allocated_address to 0
        int allocated_address = 0;

        //check if the block size is 0 and if so throw an invalid argument exception
        if(block_size == 0)
            throw std::invalid_argument("Block size for allocation is invalid");
        
        //check if the block size is greater than the total memory size and if so throw a runtime error
        if(block_size > total_memory_size_)
            throw std::runtime_error("Block size exceeds total memory size");

        //search thru the start of our memory block to the end of our memory block
        //and return the first memory block that is free and has a size that is greater than or equal to our block_size
        auto found = std::find_if(memory_blocks_.begin(), memory_blocks_.end(), [&](MemoryBlock& block) {
            return block.get_process_id() == FREE_MEMORY_STRING && block.get_size() >= block_size;
        });

        //guard clause that checks if the iterator returned is not equal to the end of memory_blocks_
        //which then throws a runtime error
        if(found == memory_blocks_.end())
            throw std::runtime_error("No suitable memory block found");

        //set allocated_address to the base address of the found memory block
        allocated_address = found->get_base_address();

        //calculate free_base_address as the base address of the found memory block plus block_size
        int free_base_address = found->get_base_address() + block_size;

        //update free_memory_size_ as the size of the found memory block minus block_size
        free_memory_size_ = found->get_size() - block_size;

        //set the process ID of the found memory block to process_id
        found->set_process_id(process_id);

        //set the size of the found memory block to block_size
        found->set_size(block_size);

        //if free_memory_size_ is greater than 0 then add a new memory block to memory_blocks_
        if(free_memory_size_ > 0)
            memory_blocks_.emplace_back(free_base_address, free_memory_size_, FREE_MEMORY_STRING);

        //return the allocated address
        return allocated_address;
    }

    void MemoryAllocator::deallocate(const std::string &process_id)
    {
        // TODO:
        // 1. Find the memory block in memory_blocks_ that has a process ID equal to process_id using std::find_if
        // 2. IF such a memory block is found THEN
        //     a. Set the process ID of the found memory block to FREE_MEMORY_STRING
        //     b. Call the function merge_free_blocks to merge adjacent free blocks
        //     c. Increase free_memory_size_ by the size of the found memory block
        // 3. ELSE 
        //     Throw an error indicating that the process ID was not found for deallocation

        //find the memory block in memory_blocks_ that has a process ID equal to process_id
        auto found = std::find_if(memory_blocks_.begin(), memory_blocks_.end(), [&](MemoryBlock& block) {
            return block.get_process_id() == process_id;
        });

        //guard clause that throws a runtime_error if the process ID was not found for deallocation
        if(found == memory_blocks_.end())
            throw std::runtime_error("Process ID was not found for deallocation");

        //set the process ID of the found memory block to FREE_MEMORY_STRING
        found->set_process_id(FREE_MEMORY_STRING);

        //call the function merge_free_blocks to merge adjacent free blocks
        merge_free_blocks();

        //increase free_memory_size_ by the size of the found memory block
        free_memory_size_ += found->get_size();
    }


    // Function to check if two blocks are free and can be merged
    bool MemoryAllocator::can_merge_blocks(const MemoryBlock& current, const MemoryBlock& next) {
        // TODO:
        // 1. IF the process ID of the current block is equal to FREE_MEMORY_STRING
        //      AND the process ID of the next block is equal to FREE_MEMORY_STRING THEN
        //      - Return true
        //    ELSE 
        //      - Return false

        //returns true or false based on if the current and next blocks are free
        return current.get_process_id() == FREE_MEMORY_STRING && next.get_process_id() == FREE_MEMORY_STRING;
    }

    // Function to merge two adjacent free blocks
    void MemoryAllocator::merge_blocks(MemoryBlock& current, const MemoryBlock& next) {
        // TODO: 
        // Set the size of the current block to the sum of:
        //   - the current size of the current block
        //   - the size of the next block

        //set the size of our current block to the sum of the current block plus the next block
        current.set_size(current.get_size() + next.get_size());
    }

    // Simplified function to merge adjacent free memory blocks
    void MemoryAllocator::merge_free_blocks() {
        // TODO: 
        // For each block from the first to the second-to-last in memory_blocks:
        //     If the current block and the next block can be merged:
        //         Merge the current block with the next block
        //         Remove the next block from memory_blocks
        //         Decrease the index by 1 to recheck the merged block
        //
        // Sort the memory_blocks by their starting address in ascending order

        //simple for loop that iterates thru each of our memory blocks
        for(int i = 0; i < memory_blocks_.size() - 1; i++) {

            //if the current block and the next block can't be merged then continue to the next iteration
            if(!can_merge_blocks(memory_blocks_[i], memory_blocks_[i + 1]))
                continue;
            
            //merge the two blocks
            merge_blocks(memory_blocks_[i], memory_blocks_[i + 1]);

            //remove the next block from memory_blocks
            memory_blocks_.erase(memory_blocks_.begin() + i + 1);

            //decrease the index by 1 to recheck the merged block
            i--;
        }
    }

    auto MemoryAllocator::get_memory_layout() -> MemoryBlockList &
    {
        return memory_blocks_;
    }

    auto MemoryAllocator::get_free_space() -> std::size_t
    {
        return free_memory_size_;
    }

} // namespace cse4733