#pragma once

#include <Common.hh>

namespace System {

class RaceManager {
public:
    struct Player {
        u8 _00[0x0a - 0x00];
        u16 checkpointId;
        f32 raceCompletion;
        u8 _10[0x21 - 0x10];
        u8 jugemId;
        u8 _22[0x54 - 0x22];
    };
    static_assert(sizeof(Player) == 0x54);

    bool isStageReached(int) const;

    const Player *player(size_t idx) const;

    static RaceManager *Instance();

private:
    u8 _00[0x0c - 0x00];
    Player **m_players;
    u8 _10[0x4c - 0x10];

    static RaceManager *s_instance;
};
static_assert(sizeof(RaceManager) == 0x4c);

} // namespace System
