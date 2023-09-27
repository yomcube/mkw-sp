#include <Common.S>

#define EXCEPTION_CONSOLE_ATTR_NO_LINE_WRAP (1 << 0)
#define EXCEPTION_CONSOLE_ATTR_TAB_SIZE_4   (1 << 2)

PATCH_B_START(RKSystem_main, 0x90)
    bl Rel_Run
    b RKSystem_main + 0x94
PATCH_B_END(RKSystem_main, 0x90)

// Increase the number of characters that a line can hold
PATCH_REPLACE_START(RKSystem_initialize, 0x18C)
    li r3, 75
PATCH_REPLACE_END(RKSystem_initialize, 0x18C)

// Increase the number of lines that the exception console can hold
PATCH_REPLACE_START(RKSystem_initialize, 0x190)
    li r4, 97 + 1
PATCH_REPLACE_END(RKSystem_initialize, 0x190)

PATCH_REPLACE_START(RKSystem_initialize, 0x194)
    li r5, EXCEPTION_CONSOLE_ATTR_NO_LINE_WRAP | EXCEPTION_CONSOLE_ATTR_TAB_SIZE_4
PATCH_REPLACE_END(RKSystem_initialize, 0x194)

// Automatically display exception information on the television screen when an exception occurs
PATCH_REPLACE_START(RKSystem_initialize, 0x1A0)
    nop
    li r3, 0
PATCH_REPLACE_END(RKSystem_initialize, 0x1A0)

// Don't create a heap for the rel because we already allocate some space from the arena for it. The
// function we are patching is still RKSystem_initialize but the NTSC-K offset is different so as a
// workaround we reference it from the next function instead.
PATCH_REPLACE_START(RKSystem_run, 0xFFFFFFD8)
    li r3, 0
PATCH_REPLACE_END(RKSystem_run, 0xFFFFFFD8)
