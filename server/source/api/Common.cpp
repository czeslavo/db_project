#include "api/Common.h"
#include "common/http_headers/AuthToken.h"
#include "common/Logger.h"

namespace common
{

std::pair<std::string, std::string> getLoginInfoFromRequest(const Pistache::Rest::Request& req)
{
    using json = nlohmann::json;

    json reqBody = json::parse(req.body());
    return { reqBody["mail"].get<std::string>(),
             reqBody["password"].get<std::string>() };
}

std::pair<std::string, std::string> getTokenInfoFromRequest(const Pistache::Rest::Request& req){
    using json = nlohmann::json;

    auto authToken = req.headers().get<AuthToken>();

    LOG_DEBUG << "Got token info from request";
    return { authToken->getMail(),
             authToken->getToken() };
}

void prepareCommonResponse(Pistache::Http::ResponseWriter& resp)
{
    resp.setMime(MIME(Application, Json));
}

}
