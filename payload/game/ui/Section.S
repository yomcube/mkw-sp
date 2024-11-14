#include <Common.S>

// Prevent constructing the system pages
// This prevents the controller page from popping up when no controller is present
PATCH_B_START(Section_init, 0x22c)
    b Section_init + 0x260
PATCH_B_END(Section_init, 0x22c)
