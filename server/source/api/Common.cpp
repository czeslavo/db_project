#include "api/Common.h"
#include "common/http_headers/AuthToken.h"

namespace common
{

std::pair<std::string, std::string> getLoginInfoFromRequest(const Net::Rest::Request& req)
{
    using json = nlohmann::json;

    json reqBody = json::parse(req.body());
    return { reqBody["mail"].get<std::string>(),
             reqBody["password"].get<std::string>() };
}

std::pair<std::string, std::string> getTokenInfoFromRequest(const Net::Rest::Request& req){
    using json = nlohmann::json;

    auto authToken = req.headers().get<AuthToken>();

    json reqBody = json::parse(req.body());
    return { authToken->getMail(),
             authToken->getToken() };
}

void prepareCommonResponse(Net::Http::ResponseWriter& resp)
{
    resp.setMime(MIME(Application, Json));
}

}
