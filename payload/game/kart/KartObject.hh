#pragma once

#include "game/kart/KartBody.hh"
#include "game/kart/KartMove.hh"

namespace Kart {

class KartObject {
public:
    const EGG::Vector3f &pos() const;
    const EGG::Vector3f &extVel() const;
    const EGG::Vector3f &angVel0() const;
    const EGG::Vector3f &angVel2() const;
    const EGG::Quatf &mainRot() const;
    const EGG::Quatf &fullRot() const;
    const EGG::Vector3f &intVel() const;
    f32 softSpeedLimit() const;
    f32 speed() const;
    f32 acceleration() const;

private:
    u8 _00[0x24 - 0x00];
    KartBody *body;
    u8 _28[0x44 - 0x28];
    KartMove *move;
};

} // namespace Kart
