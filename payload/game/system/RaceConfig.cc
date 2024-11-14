#include "RaceConfig.hh"

#include <sp/kinoko/NANDReport.hh>

extern "C" {
#include <revolution.h>
}

#include <cstring>

namespace System {

void RaceConfig::initRace() {
    m_menuScenario.gameMode = Scenario::GameMode::TimeAttack;
    m_menuScenario.cameraMode = Scenario::CameraMode::GameplayNoIntro;
    m_menuScenario.engineClass = Scenario::EngineClass::Speed150cc;
    for (auto &player : m_menuScenario.players) {
        player.type = Player::Type::None;
    }

    auto &mainPlayer = m_menuScenario.players[0];
    mainPlayer.type = Player::Type::Ghost;

    // Read ghost from the NAND
    // The final result will be in m_ghosts[1]
    if (!m_ghosts[0].readFromNAND("test.rkg")) {
        const char *msg = SP::Kinoko::NANDReport::SetNANDMsg("Could not read RKG from NAND!");
        SP::Kinoko::NANDReport::Fail(msg);
    }

    if (!m_ghosts[0].isValid()) {
        const char *msg = SP::Kinoko::NANDReport::SetNANDMsg("Ghost file is invalid!");
        SP::Kinoko::NANDReport::Fail(msg);
    }

    if (m_ghosts[0].isCompressed) {
        m_ghosts[0].decompress(&m_ghosts[1]);
    } else {
        memcpy(&m_ghosts[1], &m_ghosts[0], sizeof(RawGhostFile));
    }

    // We need to set the course here, so the rest of the initialization works correctly
    m_menuScenario.course = m_ghosts[0].course;
    m_menuScenario.ghost = &m_ghosts[1];

    REPLACED(initRace)();

    auto &racePlayer = m_raceScenario.players[0];
    racePlayer.type = Player::Type::RealLocal;
}

// The base game checks if the player is a ghost, so we rewrite the function
bool RaceConfig::isTimeAttack() const {
    // We remove ghost race because it would mean something went wrong in initialization
    if (m_raceScenario.gameMode != Scenario::GameMode::TimeAttack) {
        return false;
    }

    // Backporting the original check
    if (m_raceScenario.playerCount == 0) {
        return false;
    }

    if (m_raceScenario.players[0].type != Player::Type::RealLocal) {
        return false;
    }

    return true;
}

RaceConfig *RaceConfig::Instance() {
    return s_instance;
}

} // namespace System
