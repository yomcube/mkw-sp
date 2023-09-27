#pragma once

#include <egg/core/eggSceneManager.hh>

namespace System {

class RKSceneManager : public EGG::SceneManager {
public:
    REPLACE void changeSceneWithCreator(int sceneId, void *creator);

private:
    u8 _2c[0x30 - 0x2c];
};
static_assert(sizeof(RKSceneManager) == 0x30);

} // namespace System
