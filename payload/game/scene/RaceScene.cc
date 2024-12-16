#include "RaceScene.hh"

#include "game/kart/KartObjectManager.hh"

#include "game/system/RaceConfig.hh"
#include "game/system/RaceManager.hh"

#include <sp/kinoko/NANDReport.hh>
#include <sp/kinoko/TestBuilder.hh>

namespace Scene {

void RaceScene::initEngines() {
    REPLACED(initEngines)();

    if (!System::RaceConfig::Instance()->isTimeAttack()) {
        return;
    }

    SP::Kinoko::TestData data;

    const auto *kartObject = Kart::KartObjectManager::Instance()->object(0);
    data.pos = kartObject->pos();
    data.fullRot = kartObject->fullRot();
    data.extVel = kartObject->extVel();
    data.intVel = kartObject->intVel();
    data.speed = kartObject->speed();
    data.acceleration = kartObject->acceleration();
    data.softSpeedLimit = kartObject->softSpeedLimit();
    data.mainRot = kartObject->mainRot();
    data.angVel2 = kartObject->angVel2();

    const auto *raceMgrPlayer = System::RaceManager::Instance()->player(0);
    data.raceCompletion = raceMgrPlayer->raceCompletion;
    data.checkpointId = raceMgrPlayer->checkpointId;
    data.jugemId = raceMgrPlayer->jugemId;

    SP::Kinoko::TestBuilder::Instance()->writeDataNoFrameInc(data);
}

void RaceScene::calcEnginesUnpaused() {
    REPLACED(calcEnginesUnpaused)();

    if (!System::RaceConfig::Instance()->isTimeAttack()) {
        return;
    }

    auto *raceManager = System::RaceManager::Instance();
    if (raceManager->isStageReached(3)) {
        return;
    }

    SP::Kinoko::TestData data;

    const auto *kartObject = Kart::KartObjectManager::Instance()->object(0);
    data.pos = kartObject->pos();
    data.fullRot = kartObject->fullRot();
    data.extVel = kartObject->extVel();
    data.intVel = kartObject->intVel();
    data.speed = kartObject->speed();
    data.acceleration = kartObject->acceleration();
    data.softSpeedLimit = kartObject->softSpeedLimit();
    data.mainRot = kartObject->mainRot();
    data.angVel2 = kartObject->angVel2();

    const auto *raceMgrPlayer = raceManager->player(0);
    data.raceCompletion = raceMgrPlayer->raceCompletion;
    data.checkpointId = raceMgrPlayer->checkpointId;
    data.jugemId = raceMgrPlayer->jugemId;

    SP::Kinoko::TestBuilder::Instance()->writeData(data);
}

} // namespace Scene
