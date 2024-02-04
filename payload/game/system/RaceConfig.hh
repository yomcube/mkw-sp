#pragma once

#include <Common.hh>

namespace System {

class RaceConfig {
public:
    bool isTimeAttack() const;

    static RaceConfig *Instance();

private:
    static RaceConfig *s_instance;
};

} // namespace System
