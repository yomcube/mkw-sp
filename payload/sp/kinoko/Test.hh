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
    // Added in maj0 min1
    EGG::Vector3f pos;
    EGG::Quatf fullRot;
    // Added in maj0 min2
    EGG::Vector3f extVel;
    // Added in maj0 min3
    EGG::Vector3f intVel;
};

} // namespace SP::Kinoko
