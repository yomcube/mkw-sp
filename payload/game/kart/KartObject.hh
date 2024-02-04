#pragma once

#include "game/kart/KartBody.hh"

namespace Kart {

class KartObject {
public:
    const EGG::Vector3f &pos() const;
    const EGG::Quatf &fullRot() const;

private:
    u8 _00[0x24 - 0x00];
    KartBody *body;
};

} // namespace Kart
