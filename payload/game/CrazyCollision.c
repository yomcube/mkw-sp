#include <Common.h>

__attribute__((section("patches"))) const Patch patch_0x80441e68_0xB = {
    .type = PATCH_TYPE_WRITE,
    .write = {
        (void *)(0x80441e68 + 0xB),
        &(u32){(0x38A00001)},
        sizeof(u32),
    },
}