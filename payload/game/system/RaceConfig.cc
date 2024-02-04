#include "RaceConfig.hh"

namespace System {

RaceConfig *RaceConfig::Instance() {
    return s_instance;
}

} // namespace System
