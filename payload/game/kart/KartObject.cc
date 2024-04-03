#include "KartObject.hh"

namespace Kart {

const EGG::Vector3f &KartObject::pos() const {
    return body->physics->dynamics->pos;
}

const EGG::Vector3f &KartObject::extVel() const {
    return body->physics->dynamics->extVel;
}

const EGG::Quatf &KartObject::fullRot() const {
    return body->physics->dynamics->fullRot;
}

const EGG::Vector3f &KartObject::intVel() const {
    return body->physics->dynamics->intVel;
}

} // namespace Kart
