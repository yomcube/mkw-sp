#include "KartObject.hh"

extern "C" {
#include <revolution.h>
}

namespace Kart {

const EGG::Vector3f &KartObject::pos() const {
    return body->physics->dynamics->pos;
}

const EGG::Quatf &KartObject::fullRot() const {
    return body->physics->dynamics->fullRot;
}

} // namespace Kart
