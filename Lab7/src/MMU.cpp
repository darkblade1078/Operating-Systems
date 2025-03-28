#include <cse4733/MMU.hpp>

#include <iostream>
#include <stdexcept>

namespace cse4733 {

MMU::MMU(int numPages, unsigned int base_address) :
    pageTable(),
    tlbHits{0},
    tlbMisses{0},
    m_base_address(base_address)
{}

auto MMU::addEntry(unsigned int virtualAddress) -> unsigned int
{
    // TODO: Implement this function
    // 1. Create the physical address equal to the virtual address plus the base address
    // 2. Add the translation to the TLB
    // 3. Calculate where to insert the physical address into the page table
    // 4. Add the physical address to the page table

    // Create the physical address equal to the virtual address plus the base address
    unsigned int physicalAddress = virtualAddress + m_base_address;

    tlb.addEntry(virtualAddress, physicalAddress);

    // Calculate where to insert the physical address into the page table
    unsigned int location = virtualAddress % pageTable.size();

    // Add the physical address to the page table
    pageTable[location] = physicalAddress;

    return physicalAddress;
}

unsigned int MMU::translateAddress(unsigned int virtualAddress) {

    // TODO:
    //
    // This function should translate a given virtual address to a physical address:
    //
    // 1. It should check that the address is within the 0 to offset range bounds.
    // Throw an exception of std::out_of_range if it is not.
    //
    // 2. It should check if the translation is in the TLB (a TLB hit).
    //    a. If it is, it should return the physical address from the TLB
    //       and increment the count of TLB hits.

    // 3. If it is NOT in the TLB (a TLB miss), it should:
    //    a. It should look up the physical address in the page table with
    //       the 'virtual address' variable.
    //    b. If the physical address IS NOT in the page table, it should
    //       1) Set the physical address to the virtual address plus the base address
    //       2) Add the translation to the TLB
    //       3) Store the physical address in the page table
    //    c. Otherwise, the physical address IS in the page table, it should
    //       1) Create an entry in the TLB table
    //    d. Increment the count of TLB misses.
    //
    // 4. Return the physical address.

    unsigned int physicalAddress = 0;

    // Check that the address is within the 0 to offset range bounds
    if (virtualAddress > 0x9)
        throw std::out_of_range("Address out of range");

    // Check if the translation is in the TLB (a TLB hit)
    if (tlb.searchTLB(virtualAddress)) {
        tlbHits++;
        return tlb.searchTLB(virtualAddress).value();
    }

    // Dit not find the translation in the TLB (a TLB miss)
    tlbMisses++;

    unsigned int location = virtualAddress % pageTable.size();

    // Look up the physical address in the page table with the 'virtual address' variable
    if(pageTable[location] == 0) {
        physicalAddress = virtualAddress + m_base_address;
        tlb.addEntry(virtualAddress, physicalAddress);
        pageTable[location] = physicalAddress;
    } else {
        physicalAddress = pageTable[location];
        tlb.addEntry(virtualAddress, pageTable[location]);
    }

    return physicalAddress;
}

auto MMU::getHitRatio() const -> double
{
    // TODO:
    //   - Calculate HIT ratio
    
    if (tlbHits + tlbMisses == 0)
        return 0.0;  // Avoid division by zero

return static_cast<double>(tlbHits) / static_cast<double>(tlbHits + tlbMisses);
}

auto MMU::getMissRatio() const -> double
{
    // TODO:
    //   - Calculate MISS ratio
    
    if (tlbHits + tlbMisses == 0)
        return 0.0;  // Avoid division by zero

return static_cast<double>(tlbMisses) / static_cast<double>(tlbHits + tlbMisses);
}

}  // namespace cse4733
