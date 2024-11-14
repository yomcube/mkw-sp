#pragma once

#include <Common.hh>

namespace System {

struct RawGhostFile {
    REPLACE bool isValid() const;
    bool readFromNAND(const char *path);

    bool decompress(RawGhostFile *dst);

    union {
        u8 buffer[0x2800];
        struct {
            // 0x0
            u32 signature;

            // 0x4
            u32 _04_00 : 24 - 0;
            u32 course : 6;
            u32 _04_30 : 32 - 30;

            // 0x8
            u32 vehicle : 6;
            u32 character : 6;
            u32 year : 7;
            u32 month : 4;
            u32 day : 5;
            u32 _08_28 : 32 - 28;

            // 0xc
            u16 _0c_00 : 4 - 0;
            u16 isCompressed : 1;
            u16 _0c_05 : 16 - 5;

            u8 _0e[0x88 - 0x0e];
            u32 compressedInputSize;
        };
    };
};
static_assert(sizeof(RawGhostFile) == 0x2800);
static_assert(offsetof(RawGhostFile, compressedInputSize) == 0x88);

} // namespace System
