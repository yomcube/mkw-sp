#include "KartObjectManager.hh"

#include "game/system/RaceConfig.hh"

#include <sp/kinoko/NANDReport.hh>
#include <sp/kinoko/TestBuilder.hh>

extern "C" {
#include <revolution.h>
}

namespace Kart {

void KartObjectManager::end(u32 playerIdx) {
    REPLACED(end)(playerIdx);
    if (!System::RaceConfig::Instance()->isTimeAttack()) {
        return;
    }

    auto result = SP::Kinoko::TestBuilder::Instance()->save();
    if (!result) {
        const char *msg = SP::Kinoko::NANDReport::SetNANDMsg(result.error());
        SP::Kinoko::NANDReport::Fail(msg);
    } else {
        SP::Kinoko::NANDReport::Success();
    }
}

const KartObject *KartObjectManager::object(size_t idx) const {
    return m_objects[idx];
}

KartObjectManager *KartObjectManager::CreateInstance() {
    if (System::RaceConfig::Instance()->isTimeAttack()) {
        SP::Kinoko::TestBuilder::CreateInstance();
    }

    return REPLACED(CreateInstance)();
}

KartObjectManager *KartObjectManager::Instance() {
    return s_instance;
}

} // namespace Kart
