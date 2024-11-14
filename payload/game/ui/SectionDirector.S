#include <Common.S>

// Load directly into time trials, rather than into the main menu
PATCH_B_START(SectionDirector_init, 0xfc)
    // Replace the section ID
    li r0, 0x1f
    b SectionDirector_init + 0x100
PATCH_B_END(SectionDirector_init, 0xfc)

