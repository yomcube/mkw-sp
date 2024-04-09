#pragma once

#include <Common.hh>

namespace Kart {

struct KartMove {
    u8 _00[0x18 - 0x00];
    f32 softSpeedLimit;
    u8 _1c[0x20 - 0x1c];
    f32 speed;
    u8 _24[0x30 - 0x24];
    f32 acceleration;
};

} // namespace Kart
