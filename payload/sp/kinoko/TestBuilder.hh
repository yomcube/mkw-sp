#pragma once

#include "sp/kinoko/Test.hh"

#include <expected>

namespace SP::Kinoko {

class TestBuilder {
public:
    std::expected<void, const char *> save();
    void writeData(const TestData &data);
    void writeDataNoFrameInc(const TestData &data);

    TestData *findNextEntry() const;
    u32 version() const;

    static TestBuilder *CreateInstance();
    static void DestroyInstance();
    static TestBuilder *Instance();

private:
    TestBuilder();
    ~TestBuilder();

    void writeHeader();
    void incFrameCount();

    u8 *m_buffer;
    u32 m_frameCount;
    u32 m_index;

    static TestBuilder *s_instance;
};

} // namespace SP::Kinoko
