#include "api/handlers/FlatHandler.h"
#include "models/Flat.h"

using json = nlohmann::json;

namespace api
{

FlatHandler::FlatHandler(std::shared_ptr<db::DatabaseAccessor> db,
            std::shared_ptr<api::AuthService> auth)
    : db(db), auth(auth)
{
}

void FlatHandler::create(const Net::Rest::Request& req,
            Net::Http::ResponseWriter resp)
{
    auth->authToken(req);

    auto flatAccess = db->getFlatAccessor();

    auto flatReq = json::parse(req.body())["flat"];
    models::Flat flat{
        flatReq["name"],
        flatReq["admin_mail"]
    };

    flatAccess->create(flat);

    json respBody{{"response", "Flat created successfuly"}};
    resp.send(Net::Http::Code::Created, respBody.dump());
}

void FlatHandler::update(const Net::Rest::Request& req,
            Net::Http::ResponseWriter resp)
{
    auth->forceIsFlatAdmin(req);

    auto flatAccess = db->getFlatAccessor();

    auto flatNewValues = json::parse(req.body())["update"];
    models::Flat updateFlat{
        flatNewValues["name"],
        flatNewValues["admin_mail"]
    };

    flatAccess->update(updateFlat);

    json respBody{{"response", "Flat updated successfuly"}};
    resp.send(Net::Http::Code::Ok, respBody.dump());
}

void FlatHandler::remove(const Net::Rest::Request& req,
            Net::Http::ResponseWriter resp)
{
    auth->forceIsFlatAdmin(req);

    auto flatAccess = db->getFlatAccessor();

    const int flatId = json::parse(req.body())["flat_id"];

    flatAccess->drop(flatId);

    json respBody{{"response", "Flat removed successfuly"}};
    resp.send(Net::Http::Code::Ok, respBody.dump());
}

void FlatHandler::addUser(const Net::Rest::Request& req,
             Net::Http::ResponseWriter resp)
{
    auth->forceIsFlatAdmin(req);

    auto flatAccess = db->getFlatAccessor();
    auto reqBody = json::parse(req.body());

    const std::string userMail = reqBody["add"]["user_mail"];
    const int flatId = reqBody["flat_id"];

    flatAccess->addUser(flatId, userMail);

    json respBody{{"response", "Successfuly added user " + userMail}};
    resp.send(Net::Http::Code::Ok, respBody.dump());
}

void FlatHandler::removeUser(const Net::Rest::Request& req,
                Net::Http::ResponseWriter resp)
{

}

void FlatHandler::getUsers(const Net::Rest::Request& req,
              Net::Http::ResponseWriter resp)
{
    auth->forceIsFlatUser(req);

    auto flatAccess = db->getFlatAccessor();
    auto reqBody = json::parse(req.body());

    const int flatId = reqBody["flat_id"];

    const auto users = flatAccess->getUsers(flatId);
    json usersJson = json::array();

    std::for_each(std::cbegin(users), std::cend(users), [&](const models::User u)
        { usersJson.push_back(u.toJson()); });

    json respBody{{"response", "Got users of flat id " + std::to_string(flatId)},
                  {"users", usersJson.dump()}};

    resp.send(Net::Http::Code::Ok, respBody.dump());
}

}