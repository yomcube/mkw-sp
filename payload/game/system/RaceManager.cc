#include "RaceManager.hh"

namespace System {

const RaceManager::Player *RaceManager::player(size_t idx) const {
    return m_players[idx];
}

RaceManager *RaceManager::Instance() {
    return s_instance;
}

} // namespace System
