#include "api/handlers/FlatHandler.h"
#include "models/Flat.h"
#include "common/Logger.h"
#include "api/Common.h"

using json = nlohmann::json;

namespace api
{

FlatHandler::FlatHandler(std::shared_ptr<db::DatabaseAccessor> db,
            std::shared_ptr<api::AuthService> auth)
    : db(db), auth(auth)
{
}

void FlatHandler::create(const Pistache::Rest::Request& req,
            Pistache::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);

    auto flatAccess = db->getFlatAccessor();

    std::string mail;
    std::tie(mail, std::ignore) = common::getTokenInfoFromRequest(req);
    auto body = json::parse(req.body());
    models::Flat flat{
        0,
        body["flat"]["name"],
        mail
    };

    flatAccess->create(flat);

    json respBody{{"response", "Successfully created flat"}};
    resp.send(Pistache::Http::Code::Created, respBody.dump());
}

void FlatHandler::update(const Pistache::Rest::Request& req,
            Pistache::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->forceIsFlatAdmin(req);

    auto flatAccess = db->getFlatAccessor();

    auto flatNewValues = json::parse(req.body())["update"];
    models::Flat updateFlat{
        flatNewValues["name"],
        flatNewValues["admin_mail"]
    };

    flatAccess->update(updateFlat);

    json respBody{{"response", "Successfully updated flat"}};
    resp.send(Pistache::Http::Code::Ok, respBody.dump());
}

void FlatHandler::remove(const Pistache::Rest::Request& req,
            Pistache::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->forceIsFlatAdmin(req);

    auto flatAccess = db->getFlatAccessor();

    const auto flatId = req.param(":flat_id").as<int>();
    flatAccess->drop(flatId);

    json respBody{{"response", "Successfully removed flat"}};
    resp.send(Pistache::Http::Code::Ok, respBody.dump());
}

void FlatHandler::addUser(const Pistache::Rest::Request& req,
             Pistache::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->forceIsFlatAdmin(req);

    auto flatAccess = db->getFlatAccessor();
    auto reqBody = json::parse(req.body());

    LOG_DEBUG << reqBody;

    const std::string userMail = reqBody["add"]["user_mail"];
    const int flatId = reqBody["flat_id"];

    flatAccess->addUser(flatId, userMail);

    json respBody{{"response", "Successfully added user " + userMail}};
    resp.send(Pistache::Http::Code::Ok, respBody.dump());
}

void FlatHandler::removeUser(const Pistache::Rest::Request& req,
                Pistache::Http::ResponseWriter resp)
{

}

void FlatHandler::getUsers(const Pistache::Rest::Request& req,
              Pistache::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    LOG_DEBUG << "Handling request in FlatHandler::getUsers";

    auth->forceIsFlatUser(req);

    const int flatId = req.param(":flat_id").as<int>();

    auto flatAccess = db->getFlatAccessor();
    const auto users = flatAccess->getUsers(flatId);
    json usersJson = json::array();

    std::for_each(std::cbegin(users), std::cend(users), [&](const models::User u)
        { usersJson.push_back(u.toJson()); });

    json respBody{{"response", "Got users of flat"},
                  {"users", usersJson}};

    resp.send(Pistache::Http::Code::Ok, respBody.dump());
}

void FlatHandler::getUsersFlats(const Pistache::Rest::Request& req,
                                Pistache::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    LOG_DEBUG << "Handling request in FlatHandler::getUsersFlats";

    std::string mail, apiToken;
    std::tie(mail, apiToken) = common::getTokenInfoFromRequest(req);

    auto flatAccess = db->getFlatAccessor();
    const auto users = flatAccess->getUsersFlats(mail);
    json usersJson = json::array();

    std::for_each(std::cbegin(users), std::cend(users), [&](const models::Flat f)
        { usersJson.push_back(f.toJson()); });

    json respBody{{"response", "Got user's flats"},
                  {"flats", usersJson}};

    resp.send(Pistache::Http::Code::Ok, respBody.dump());
}

}
