#pragma once

namespace System {

class RaceManager {
public:
    bool isStageReached(int) const;

    static RaceManager *Instance();

private:
    static RaceManager *s_instance;
};

} // namespace System
