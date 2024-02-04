#include "RaceManager.hh"

namespace System {

RaceManager *RaceManager::Instance() {
    return s_instance;
}

} // namespace System
