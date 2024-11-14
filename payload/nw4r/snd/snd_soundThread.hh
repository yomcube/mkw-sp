#pragma once

#include <Common.hh>

namespace nw4r::snd::detail {

class SoundThread {
    REPLACE int SoundThreadFunc(void *arg);
};

} // namespace nw4r::snd::detail
