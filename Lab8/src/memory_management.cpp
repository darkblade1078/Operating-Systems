#include "memory_management.hpp"
#include "invalid_page_table_entry_exception.hpp"
#include "invalid_virtual_address_exception.hpp"
#include "page_table_entry_not_found_exception.hpp"
#include <iostream>

struct page_table_entry {
    bool valid; // Valid bit
    unsigned int page_frame_number; // Page Frame Number (PFN)
};

namespace cse4733
{

    memory_management::memory_management()
    {
        /** TODO: Implement the constructor for the memory_management class
         * 1. Create an empty page table as a map with pairs
         *    of unsigned integers as keys and page_table_entry
         *    as values.
         * 2. Loop over the range from 0 to PAGE_DIRECTORY_SIZE
         *    a. Nested loop over the range from 0 to PAGE_TABLE_SIZE
         *       1) Create a pair of unsigned integers (i, j)
         *          as the key.
         *       2) Assign a new page_table_entry to the page table
         *          at the key.
         *       3) Set the valid bit of the page_table_entry to true
         *          and assign the page frame number as j.
         */

         // Create an empty page table as a map with pairs of unsigned integers as keys and page_table_entry as values.
         m_pageTable = std::map<std::pair<unsigned int, unsigned int>, page_table_entry>();

        // Loop over the range from 0 to PAGE_DIRECTORY_SIZE
        for(unsigned int i = 0; i < PAGE_DIRECTORY_SIZE; i++) {

            // Nested loop over the range from 0 to PAGE_TABLE_SIZE
            for(unsigned int j = 0; j < PAGE_TABLE_SIZE; j++) {
                // Create a pair of unsigned integers (i, j) as the key.
                std::pair<unsigned int, unsigned int> key = std::make_pair(i, j);

                // Assign a new page_table_entry to the page table at the key.
                page_table_entry entry;

                // Set the valid bit of the page_table_entry to true
                entry.valid = true; 

                // Assign the page frame number as j.
                entry.page_frame_number = j;
                
                m_pageTable[key] = entry;
            }
        }
    }

    auto memory_management::pageTableLookup(unsigned int virtualAddress) -> unsigned int
    {
        // TODO: Implement the pageTableLookup method
        /**
         * 1. Function `pageTableLookup` takes an unsigned integer
         *    `virtualAddress` as a parameter
         * 2. Check if the `virtualAddress` is valid
         *    1. If the `virtualAddress` is greater than `MAX_VIRTUAL_ADDRESS`
         *       or less than 0, throw `invalid_virtual_address_exception`
         * 3. Calculate the `pageTableIndex`, `pageDirectoryIndex`, and
         *    `pageOffset` from the `virtualAddress`
         * 4. Create a pair of unsigned integers (`pageDirectoryIndex`, `pageTableIndex`)
         *    as the key
         * 5. Find the page table entry using the key
         *    a. If the entry does not exist in the page table, throw 
         *       `page_table_entry_not_found_exception`
         * 6. Access the page table entry
         * 7. Check if the page table entry is valid
         *    a. If the page table entry is not valid,
         *       throw `invalid_page_table_entry_exception`
         * 8. Calculate the physical address using the page frame number
         *    from the page table entry and the `pageOffset`
         * 9. Print the virtual address, page directory index, page table index,
         *    and page offset
         * 10. Print the physical address
         * 11. Return the physical address
         */

        // Check if the `virtualAddress` is valid
        if (virtualAddress > MAX_VIRTUAL_ADDRESS || virtualAddress < 0)
            throw cse4733::invalid_virtual_address_exception();

        // Calculate the `pageTableIndex`, `pageDirectoryIndex`, and `pageOffset` from the `virtualAddress`
        unsigned int pageTableIndex = (virtualAddress & PAGE_TABLE_MASK) >> PAGE_TABLE_BIT_SHIFT;
        unsigned int pageDirectoryIndex = (virtualAddress & PAGE_DIRECTORY_MASK) >> PAGE_DIRECTORY_BIT_SHIFT;
        unsigned int pageOffset = (virtualAddress & PAGE_OFFSET_MASK);

        // Create a pair of unsigned integers (`pageDirectoryIndex`, `pageTableIndex`) as the key
        std::pair<unsigned int, unsigned int> key = std::make_pair(pageDirectoryIndex, pageTableIndex);

        // Find the page table entry using the key
        auto it = m_pageTable.find(key);

        // If the entry does not exist in the page table, throw `page_table_entry_not_found_exception`
        if (it == m_pageTable.end())
            throw cse4733::page_table_entry_not_found_exception();

        // Access the page table entry
        page_table_entry entry = it->second;

        // Check if the page table entry is valid
        if (!entry.valid)
            throw cse4733::invalid_page_table_entry_exception();

        // Number of bits for page offset (usually 12)
        const unsigned int PAGE_OFFSET_BITS = 12;

        // Calculate the physical address using the page frame number from the page table entry and the `pageOffset`

        // This was wrong so I changed it to offset the bits by 12 which fixed this issue as
        // As the physical address was not being calculated using the instructions.

        // I also had AI help me figure out how to fix this issue with the physical address
        // not being displayed correctly.

        // output following instructions: Physical Address: 0x1000823(16779299)
        // Correct Output: Physical Address: 0x4823(18467)
        unsigned int physicalAddress = (pageTableIndex << PAGE_OFFSET_BITS) | pageOffset;

    // Print the virtual address, page directory index, page table index, and page offset with hexadecimal format
    std::cout << "Virtual Address: 0x" << std::hex << virtualAddress << "(" << std::dec << virtualAddress << ")" << std::endl;
    std::cout << "Page Directory Index:.. 0x" << std::hex << pageDirectoryIndex << " (" << std::dec << pageDirectoryIndex << ") " << std::endl;
    std::cout << "Page Table Index:... 0x" << std::hex << pageTableIndex << " (" << std::dec << pageTableIndex << ") " << std::endl;
    std::cout << "Page offset:..... 0x" << std::hex << pageOffset << " (" << std::dec << pageOffset << ")" << std::endl;

    // Print the physical address
    std::cout << "Physical Address: 0x" << std::hex << physicalAddress << "(" << std::dec << physicalAddress << ")" << std::endl;
    std::cout << std::endl;

        // Return the physical address
        return physicalAddress;
    }

} // namespace cse4733