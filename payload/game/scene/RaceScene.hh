#pragma once

#include <Common.hh>

namespace Scene {

class RaceScene {
public:
    REPLACE void initEngines();
    void REPLACED(initEngines)();

    REPLACE void calcEnginesUnpaused();
    void REPLACED(calcEnginesUnpaused)();
};

} // namespace Scene
