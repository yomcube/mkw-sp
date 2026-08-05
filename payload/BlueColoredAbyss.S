#include <Common.S>

PATCH_REPLACE_START(BlueColoredAbyss, 0)
    .short 0x440F
    .short 0xFF00
PATCH_REPLACE_END(BlueColoredAbyss, 0)

