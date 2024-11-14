#pragma once

#include <optional>
#include <string>

namespace SP::Kinoko::NANDReport {

void Fail(const char *msg = nullptr);
void Success();

const char *SetNANDMsg(const char *msg);

} // namespace SP::Kinoko::NANDReport
