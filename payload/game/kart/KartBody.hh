#pragma once

#include "game/kart/KartPhysics.hh"

namespace Kart {

struct KartBody {
    u8 _00[0x90 - 0x00];
    KartPhysics *physics;
};

} // namespace Kart
