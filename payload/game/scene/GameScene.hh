#pragma once

#include <Common.hh>

extern "C" {
REPLACE void FUN_80564adc();
}

namespace Scene {

class GameScene {
    REPLACE void draw();
};

} // namespace Scene
