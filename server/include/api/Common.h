#pragma once

#include <json.hpp>
#include <utility>
#include "pistache/description.h"

namespace common
{

std::pair<std::string, std::string> getLoginInfoFromRequest(const Pistache::Rest::Request& req);

std::pair<std::string, std::string> getTokenInfoFromRequest(const Pistache::Rest::Request& req);

void prepareCommonResponse(Pistache::Http::ResponseWriter& resp);

}
