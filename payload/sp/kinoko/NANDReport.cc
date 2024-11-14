#include "NANDReport.hh"

extern "C" {
#include <revolution.h>
}

#include <cstring>

namespace SP::Kinoko::NANDReport {

void Fail(const char *msg) {
    // Result of all NAND operations
    s32 result;

    result = NANDPrivateCreate("fail", NAND_PERM_ALL_MASK, 0);
    if (result != NAND_RESULT_OK) {
        SP_LOG("CATASTROPHIC: NANDPrivateCreate returns %d on fail", result);
        goto fail_shutdown;
    }

    // If we don't have a fail reason, simply create the file and leave it at that
    if (!msg) {
        goto fail_shutdown;
    }

    // If the message isn't 0x20 byte aligned, we can't write it
    if (reinterpret_cast<uintptr_t>(msg) % 0x20 != 0) {
        SP_LOG("CATASTROPHIC: A message was provided, but it was not 0x20 byte aligned!");
        goto fail_shutdown;
    }

    NANDFileInfo fileInfo;
    result = NANDPrivateOpen("fail", &fileInfo, NAND_ACCESS_WRITE);
    if (result != NAND_RESULT_OK) {
        SP_LOG("CATASTROPHIC: NANDPrivateOpen returns %d on fail", result);
        goto fail_close;
    }

    // We don't care about null terminators with NANDWrite
    result = NANDWrite(&fileInfo, msg, strlen(msg));
    if (static_cast<size_t>(result) != strlen(msg)) {
        SP_LOG("CATASTROPHIC: NANDWrite returns %d on fail", result);
    }

fail_close:
    result = NANDClose(&fileInfo);
    if (result != NAND_RESULT_OK) {
        SP_LOG("CATASTROPHIC: NANDClose returns %d on fail", result);
    }

fail_shutdown:
    OSShutdownSystem();
}

void Success() {
    // Result of all NAND operations
    s32 result;

    result = NANDPrivateCreate("ok", NAND_PERM_ALL_MASK, 0);
    if (result != NAND_RESULT_OK) {
        SP_LOG("CATASTROPHIC: NANDPrivateCreate returns %d on success", result);
    }

    OSShutdownSystem();
}

const char *SetNANDMsg(const char *msg) {
    static constexpr size_t REASON_LEN = 0x100;

    // Anything that writes to the NAND must be 0x20 byte aligned
    static char s_buffer[REASON_LEN] __attribute__((__aligned__(0x20)));
    if (reinterpret_cast<uintptr_t>(s_buffer) % 0x20 != 0) {
        SP_LOG("CATASTROPHIC: Buffer is not aligned correctly!");
        Fail();
    }

    // Include null terminator
    size_t msgLen = strlen(msg) + 1;

    if (msgLen > REASON_LEN) {
        SP_LOG("Message doesn't fit in message buffer! No message will be provided");
        return nullptr;
    }

    for (size_t i = 0; i < msgLen; ++i) {
        s_buffer[i] = msg[i];
    }

    return s_buffer;
}

} // namespace SP::Kinoko::NANDReport
