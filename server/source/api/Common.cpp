#include "api/Common.h"

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

    json reqBody = json::parse(req.body());
    return { reqBody["mail"].get<std::string>(),
             reqBody["apiToken"].get<std::string>() };
}

void setJsonMime(Net::Http::ResponseWriter& resp)
{
    resp.setMime(MIME(Application, Json));
}

}
