#include <Common.S>

PATCH_BL_START(Task10_A, 0)
    bl loc_0x8
    .word 0x47435000

    loc_0x8:
        mflr r10
        lwz r3, 0(r3)
        lwz r3, 8(r3)
        lwz r3, 144(r3)
        lwz r3, 4(r3)
        lfs f1, 108(r3)
        lfs f10, 0(r10)
        fcmpu cr0, f1, f10
        ble- loc_0x30
        fneg f10, f10

    loc_0x30:
        fadds f1, f1, f10
        stfs f1, 108(r3)
        li r10, 0x3
        stb r10, 375(r3)
PATCH_BL_END(Task10_A, 0)

PATCH_BL_START(Task10_B, 0)
    loc_0x0:
        lfs f1, 116(r31)
        lbz r10, 375(r31)
        subi r10, r10, 0x1
        cmpwi r10, 0x0
        ble- loc_0x24
        fsubs f0, f1, f1
        stfd f0, 80(r1)
        stfs f0, 88(r1)
        stb r10, 375(r31)

    loc_0x24:
PATCH_BL_END(Task10_B, 0)

PATCH_BL_START(Task10_C, 0)
    .word 5
PATCH_BL_END(Task10_C, 0)


