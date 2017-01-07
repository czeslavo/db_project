#pragma once

#include <json.hpp>
#include <utility>
#include "pistache/description.h"

namespace common
{

std::pair<std::string, std::string> getLoginInfoFromRequest(const Net::Rest::Request& req);

std::pair<std::string, std::string> getTokenInfoFromRequest(const Net::Rest::Request& req);

void setJsonMime(Net::Http::ResponseWriter& resp);

}
