#include "RKSceneManager.hh"

namespace System {

void RKSceneManager::changeSceneWithCreator(int sceneId, void *creator) {
    m_creator = creator;
    changeSiblingScene(sceneId);
}

} // namespace System
