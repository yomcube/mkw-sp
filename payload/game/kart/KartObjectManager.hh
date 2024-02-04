#pragma once

#include "game/kart/KartObject.hh"

namespace Kart {

class KartObjectManager {
public:
    REPLACE void init();
    void REPLACED(init)();
    REPLACE void calc();
    void REPLACED(calc)();
    REPLACE void end(u32 playerIdx);
    void REPLACED(end)(u32 playerIdx);

    static REPLACE KartObjectManager *CreateInstance();
    static KartObjectManager *REPLACED(CreateInstance)();

private:
    u8 _00[0x20 - 0x00];
    KartObject **m_objects;
};

} // namespace Kart
