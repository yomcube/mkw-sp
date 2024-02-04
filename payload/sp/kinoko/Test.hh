#pragma once

#include <egg/math/eggQuat.hh>
#include <egg/math/eggVector.hh>

namespace SP::Kinoko {

struct TestHeader {
    u32 signature;
    u16 byteOrderMark;
    u16 frameCount;
    u32 version;
    u32 dataOffset;
};

struct TestData {
    EGG::Vector3f pos;
    EGG::Quatf fullRot;
};

} // namespace SP::Kinoko
