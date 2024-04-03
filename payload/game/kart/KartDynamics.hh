#pragma once

#include <egg/math/eggQuat.hh>
#include <egg/math/eggVector.hh>

namespace Kart {

struct KartDynamics {
    u8 _000[0x068 - 0x000];
    EGG::Vector3f pos;
    EGG::Vector3f extVel;
    u8 _080[0x100 - 0x080];
    EGG::Quatf fullRot;
    u8 _110[0x14c - 0x110];
    EGG::Vector3f intVel;
};

} // namespace Kart
