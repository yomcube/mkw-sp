#pragma once

#include <egg/math/eggQuat.hh>
#include <egg/math/eggVector.hh>

namespace Kart {

struct KartDynamics {
    u8 _000[0x068 - 0x000];
    EGG::Vector3f pos;
    EGG::Vector3f extVel;
    u8 _080[0x0a4 - 0x080];
    EGG::Vector3f angVel0;
    u8 _0B0[0x0e4 - 0x0b0];
    EGG::Vector3f angVel2;
    EGG::Quatf mainRot;
    EGG::Quatf fullRot;
    u8 _110[0x14c - 0x110];
    EGG::Vector3f intVel;
};

} // namespace Kart
