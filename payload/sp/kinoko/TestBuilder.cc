#include "TestBuilder.hh"

#include <egg/core/eggHeap.hh>

extern "C" {
#include <revolution.h>
}

#include <cstring>

namespace SP::Kinoko {

std::expected<void, const char *> TestBuilder::save() {
    NANDPrivateDelete("test.krkg");
    if (NANDPrivateCreate("test.krkg", NAND_PERM_ALL_MASK, 0) != NAND_RESULT_OK) {
        return std::unexpected("Could not create test file!");
    }

    NANDFileInfo fileInfo;
    if (NANDPrivateOpen("test.krkg", &fileInfo, NAND_ACCESS_WRITE) != NAND_RESULT_OK) {
        return std::unexpected("Could not open test file!");
    }

    s32 result = NANDWrite(&fileInfo, m_buffer, m_index);
    if (result < 0 || static_cast<u32>(result) != m_index) {
        NANDClose(&fileInfo);
        return std::unexpected("Error writing file contents!");
    }

    if (NANDClose(&fileInfo) != NAND_RESULT_OK) {
        return std::unexpected("Could not close test file!");
    }

    return {};
}

void TestBuilder::writeData(const TestData &data) {
    TestData *pData = findNextEntry();

    pData->pos = data.pos;
    pData->fullRot = data.fullRot;
    pData->extVel = data.extVel;
    pData->intVel = data.intVel;
    pData->speed = data.speed;
    pData->acceleration = data.acceleration;
    pData->softSpeedLimit = data.softSpeedLimit;
    pData->mainRot = data.mainRot;
    pData->angVel2 = data.angVel2;

    incFrameCount();
    m_index += sizeof(TestData);
}

void TestBuilder::writeDataNoFrameInc(const TestData &data) {
    writeData(data);
    --m_frameCount;
}

TestData *TestBuilder::findNextEntry() const {
    return reinterpret_cast<TestData *>(m_buffer + m_index);
}

u32 TestBuilder::version() const {
    constexpr u16 major = 0;
    constexpr u16 minor = 5;
    return major << 16 | minor;
}

TestBuilder *TestBuilder::CreateInstance() {
    assert(!s_instance);
    s_instance = new TestBuilder;
    return s_instance;
}

void TestBuilder::DestroyInstance() {
    assert(s_instance);
    delete s_instance;
    s_instance = nullptr;
}

TestBuilder *TestBuilder::Instance() {
    return s_instance;
}

TestBuilder::TestBuilder() {
    // 1.5 MiB
    constexpr size_t size = 0x180000;
    m_buffer = new (0x20) u8[size];
    memset(m_buffer, 0, size);
    m_index = 0;

    writeHeader();
}

TestBuilder::~TestBuilder() {
    delete m_buffer;
}

void TestBuilder::writeHeader() {
    TestHeader *pHeader = reinterpret_cast<TestHeader *>(m_buffer);

    constexpr u32 signature = 0x4b524b47; // 'KRKG'
    pHeader->signature = signature;
    pHeader->byteOrderMark = 0xfeff;
    pHeader->frameCount = 0;
    pHeader->version = version();
    pHeader->dataOffset = sizeof(TestHeader);

    m_index += sizeof(TestHeader);
}

void TestBuilder::incFrameCount() {
    TestHeader *pHeader = reinterpret_cast<TestHeader *>(m_buffer);
    pHeader->frameCount = ++m_frameCount;
}

TestBuilder *TestBuilder::s_instance = nullptr;

} // namespace SP::Kinoko
