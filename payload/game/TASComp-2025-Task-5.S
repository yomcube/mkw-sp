#include <Common.S>

// Don't lose items on respawn
PATCH_REPLACE_START(TASComp2025Task5_A, 0)
    nop
PATCH_REPLACE_END(TASComp2025Task5_A, 0)

// Don't wait for respawn timer
PATCH_REPLACE_START(TASComp2025Task5_B, 0)
    li r0, 0
PATCH_REPLACE_END(TASComp2025Task5_B, 0)

// ?
PATCH_REPLACE_START(TASComp2025Task5_C, 0)
    li r4, 1
PATCH_REPLACE_END(TASComp2025Task5_C, 0)
