#include "RacePage.h"

#include "../ctrl/CtrlRaceNameBalloon.h"
#include "../ctrl/CtrlRaceSpeed.h"

void RacePage_initSpeedControl(RacePage *this, u32 controlId, u32 localPlayerCount, u32 localPlayerId) {
    CtrlRaceSpeed *control = new(sizeof(CtrlRaceSpeed));
    CtrlRaceSpeed_ct(control);
    Page_insertChild(this, controlId, control, 0);
    CtrlRaceSpeed_load(control, localPlayerCount, localPlayerId);
}

extern void RacePage_initControls;
extern void RacePage_afterCalc;
extern void RacePage_calcNameBalloons;
extern void RacePage_calcItemBalloons;

PATCH_S16(RacePage_initControls, 0x566, sizeof(BalloonManager));
PATCH_S16(RacePage_initControls, 0x57e, sizeof(BalloonManager));
PATCH_S16(RacePage_initControls, 0x5a2, sizeof(BalloonManager));
PATCH_S16(RacePage_initControls, 0x626, sizeof(BalloonManager));
PATCH_S16(RacePage_initControls, 0x72a, sizeof(BalloonManager));
PATCH_S16(RacePage_afterCalc, 0x5e, sizeof(BalloonManager));
PATCH_S16(RacePage_calcNameBalloons, 0x76, sizeof(BalloonManager));
PATCH_S16(RacePage_calcItemBalloons, 0x72, sizeof(BalloonManager));

enum {
    CONTROL_TIME = 1 << 1,
    CONTROL_COUNT = 1 << 2,
    CONTROL_MAP = 1 << 3,
    CONTROL_RANK_NUM = 1 << 4,
    CONTROL_LAP = 1 << 5,
    CONTROL_ITEM_WINDOW = 1 << 6,
    CONTROL_POINT = 1 << 7,
    CONTROL_GHOST_TIME_DIFF = 1 << 8,
    CONTROL_LIVE = 1 << 9,
    CONTROL_SCORE = 1 << 10,
    CONTROL_ITEM_BALLOON = 1 << 11,
    CONTROL_GHOST_MESSAGE = 1 << 12,
};

u32 GhostReplayRacePage_getControls(RacePage *this);

static u32 my_GhostReplayRacePage_getControls(RacePage *UNUSED(this)) {
    u32 controls = 0;
    controls |= CONTROL_TIME;
    controls |= CONTROL_COUNT;
    controls |= CONTROL_MAP;
    controls |= CONTROL_LAP;
    controls |= CONTROL_ITEM_WINDOW;
    return controls;
}
PATCH_B(GhostReplayRacePage_getControls, my_GhostReplayRacePage_getControls);

u32 VsMultiRacePage_getControls(RacePage *this);

static u32 my_VsMultiRacePage_getControls(RacePage *UNUSED(this)) {
    u32 controls = 0;
    controls |= CONTROL_TIME;
    controls |= CONTROL_COUNT;
    controls |= CONTROL_MAP;
    controls |= CONTROL_RANK_NUM;
    controls |= CONTROL_LAP;
    controls |= CONTROL_ITEM_WINDOW;
    controls |= CONTROL_ITEM_BALLOON;
    return controls;
}
PATCH_B(VsMultiRacePage_getControls, my_VsMultiRacePage_getControls);
