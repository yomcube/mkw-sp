#pragma once

#include "game/system/GhostFile.hh"

namespace System {

class RaceConfig {
public:
    struct Player {
        enum class Type {
            RealLocal = 0,
            Ghost = 3,
            None = 5,
        };

        u8 _00[0x05 - 0x00];
        u8 screenID;
        u8 _06[0x08 - 0x06];
        int vehicle;
        int character;
        Type type;
        u8 _14[0xf0 - 0x14];
    };
    static_assert(sizeof(Player) == 0xf0);

    struct Scenario {
        enum class EngineClass {
            Speed150cc = 2,
        };

        enum class GameMode {
            TimeAttack = 2,
        };

        enum class CameraMode {
            GameplayNoIntro = 0,
        };

        u8 _000[0x004 - 0x000];
        u8 playerCount;
        u8 _005[0x008 - 0x005];
        std::array<Player, 12> players;
        int course;
        EngineClass engineClass;
        GameMode gameMode;
        CameraMode cameraMode;
        u8 _b58[0xb64 - 0xb58];
        std::array<u8, 4> hudPlayerIDs;
        u8 _b68[0xbec - 0xb68];
        void *ghost;
    };
    static_assert(sizeof(Scenario) == 0xbf0);

    REPLACE void initRace();
    void REPLACED(initRace)();

    bool isTimeAttack() const;

    static RaceConfig *Instance();

private:
    u8 _0000[0x0020 - 0x0000];
    Scenario m_raceScenario;
    Scenario m_menuScenario;
    u8 _1800[0x23f0 - 0x1800];
    std::array<RawGhostFile, 2> m_ghosts;

    static RaceConfig *s_instance;
};
static_assert(sizeof(RaceConfig) == 0x73f0);

} // namespace System
