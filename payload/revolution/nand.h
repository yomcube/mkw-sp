#pragma once

#include <Common.h>

#define NAND_RESULT_OK 0

#define NAND_PERM_ALL_MASK 0x3f

#define NAND_ACCESS_READ 0x1
#define NAND_ACCESS_WRITE 0x2

typedef struct {
    u8 _00[0x8c - 0x00];
} NANDFileInfo;
static_assert(sizeof(NANDFileInfo) == 0x8c);

s32 NANDPrivateCreate(const char *path, u8 perm, u8 attr);
s32 NANDPrivateDelete(const char *path);
s32 NANDRead(NANDFileInfo *info, void *buf, u32 length);
s32 NANDWrite(NANDFileInfo *info, const void *buf, u32 length);
s32 NANDOpen(const char *path, NANDFileInfo *info, u8 accType);
s32 NANDPrivateOpen(const char *path, NANDFileInfo *info, u8 accType);
s32 NANDClose(NANDFileInfo *info);
