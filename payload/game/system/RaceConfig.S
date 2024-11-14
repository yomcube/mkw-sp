#include <Common.S>

// We need the ghost buffers to be 0x20 byte aligned so we can send the buffers into NANDRead
// Because they always start at offset 0x23f0 of RaceConfig, specifying alignment will always fail
// (instance % 0x20) == 0 => ((instance + buffer_offset) % 0x20) == 0x10
// So, we're going to modify the new call to account for an additional 0x10 bytes
// This will offset thisptr so ((instance + buffer_offset) % 0x20) == 0
//
// WARN: Memory deallocation is reliant on the memory block being 0x10 bytes behind the pointer
// We do this knowing that RaceConfig's instance is never destroyed in MKW's lifespan
PATCH_B_START(RaceConfig_CreateInstance, 0x20)
    li r3, 0x7400 // sizeof(RaceConfig) + 0x10
    li r4, 0x20   // alignment
    li r5, 0x0    // use current heap
    bl EGG_Heap_alloc

    // We need to ensure nullptr comparison while still modifying thisptr
    cmpwi r3, 0x0
    addi r3, r3, 0x10

    b RaceConfig_CreateInstance + 0x2c
PATCH_B_END(RaceConfig_CreateInstance, 0x20)
