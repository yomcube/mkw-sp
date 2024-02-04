#pragma once

#include "game/kart/KartDynamics.hh"

namespace Kart {

struct KartPhysics {
    u8 _0[0x4 - 0x0];
    KartDynamics *dynamics;
};

} // namespace Kart
