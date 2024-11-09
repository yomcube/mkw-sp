#include <Common.S>

PATCH_BL_START(KartItem_activateMushroom, 0x10)
    mr r31, r3 // Original instruction

    // Check that the player id is 0
    lbz r4, 0x18 (r3)
    cmpwi r4, 0x0
    bnelr

    // Get lap
    lis r3, s_raceManager@ha
    lwz r3, s_raceManager@l (r3)
    lwz r3, 0xc (r3)
    lwz r3, 0x0 (r3)
    lbz r3, 0x26 (r3)

    bl SPFooter_OnShroom

    mr r3, r31
    b KartItem_activateMushroom + 0x14
PATCH_BL_END(KartItem_activateMushroom, 0x10)

// Task 8 Infinite Mushroom Code [vabold, Gaberboo]
// https://pastebin.com/qUyvt4ZW
PATCH_BL_START(_ZN4Item8KartItem4calcEv, 0x890)
    stw r0, 569(r29) // stw instead of stb (original instruction)
    li r0, 0x3
    stw r0, 144(r29)
    li r0, 0x5
    stw r0, 140(r29)
PATCH_BL_END(_ZN4Item8KartItem4calcEv, 0x890)
