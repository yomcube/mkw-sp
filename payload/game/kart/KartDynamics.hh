#pragma once

#include <egg/math/eggQuat.hh>
#include <egg/math/eggVector.hh>

namespace Kart {

struct KartDynamics {
    u8 _00[0x068 - 0x000];
    EGG::Vector3f pos;
    u8 _74[0x100 - 0x074];
    EGG::Quatf fullRot;
};

} // namespace Kart
