#include "KartObject.hh"

namespace Kart {

const EGG::Vector3f &KartObject::pos() const {
    return body->physics->dynamics->pos;
}

const EGG::Vector3f &KartObject::extVel() const {
    return body->physics->dynamics->extVel;
}

const EGG::Vector3f &KartObject::angVel2() const {
    return body->physics->dynamics->angVel2;
}

const EGG::Quatf &KartObject::mainRot() const {
    return body->physics->dynamics->mainRot;
}

const EGG::Quatf &KartObject::fullRot() const {
    return body->physics->dynamics->fullRot;
}

const EGG::Vector3f &KartObject::intVel() const {
    return body->physics->dynamics->intVel;
}

f32 KartObject::softSpeedLimit() const {
    return move->softSpeedLimit;
}

f32 KartObject::speed() const {
    return move->speed;
}

f32 KartObject::acceleration() const {
    return move->acceleration;
}

} // namespace Kart
