#include "api/handlers/UserHandler.h"
#include "common/Logger.h"
#include "json.hpp"
#include "api/Common.h"

using json = nlohmann::json;

namespace api
{

UserHandler::UserHandler(std::shared_ptr<db::DatabaseAccessor> db,
                         std::shared_ptr<api::AuthService> auth)
    : db(db), auth(auth)
{
}

void UserHandler::getByEmail(const Net::Rest::Request& req,
                    Net::Http::ResponseWriter resp)
{
    LOG_DEBUG << "Handling request in UserHandler::getByEmail";
    common::setJsonMime(resp);

    const auto mail = req.param(":mail").as<std::string>();

    auto userAccess = db->getUserAccessor();

    try
    {
        const auto user = userAccess->getByEmail(mail).toJson();
        resp.send(Net::Http::Code::Ok, user.dump());
    }
    catch (const std::exception& e)
    {
        resp.send(Net::Http::Code::Not_Found);
    }
}

void UserHandler::signup(const Net::Rest::Request& req,
                    Net::Http::ResponseWriter resp)
{
    LOG_DEBUG << "Handling request in UserHandler::create";
    common::setJsonMime(resp);

    json reqBody = json::parse(req.body());

    models::User user{
        reqBody["mail"],
        reqBody["username"],
        reqBody["name"],
        reqBody["surname"],
        reqBody["password"]
    };

    try
    {
        auto userAccess = db->getUserAccessor();
        userAccess->create(user);

        json respBody = {{"response", "User " + user.mail +
            " created successfully"}};
        resp.send(Net::Http::Code::Created, respBody.dump());
    }
    catch (const std::exception& e)
    {
        resp.send(Net::Http::Code::Not_Modified, "Couldn't create user");
    }
}

void UserHandler::deleteByEmail(const Net::Rest::Request& req,
                                Net::Http::ResponseWriter resp)
{
    LOG_DEBUG << "Handling request in UserHandler::deleteByEmail";
    common::setJsonMime(resp);

    json reqBody = json::parse(req.body());
    auth->authPassword(req);

    try
    {
        auto userAccess = db->getUserAccessor();
        userAccess->drop(reqBody["mail"]);

        json respBody = {{"response", "User deleted successfully"}};
        resp.send(Net::Http::Code::Ok, respBody.dump());
    }
    catch (const std::exception& e)
    {
        resp.send(Net::Http::Code::Not_Found, "User with given email not found");
    }
}

void UserHandler::update(const Net::Rest::Request& req,
                         Net::Http::ResponseWriter resp)
{
    LOG_DEBUG << "Handling request in UserHandler::update";
    common::setJsonMime(resp);

    json reqBody = json::parse(req.body());

    try
    {
        auth->authPassword(req);

        auto newValues = reqBody["update"];
        models::User user{
            reqBody["mail"],
            newValues["username"],
            newValues["name"],
            newValues["surname"],
            newValues["password"]
        };

        auto userAccess = db->getUserAccessor();
        userAccess->update(user);

        json respBody = {{"response", "User successfully updated"}};
        resp.send(Net::Http::Code::Ok, respBody.dump());
    }
    catch (const std::exception& e)
    {
        resp.send(Net::Http::Code::Not_Found, "Failed to update user");
    }
}

void UserHandler::login(const Net::Rest::Request& req,
                        Net::Http::ResponseWriter resp)
{
    LOG_DEBUG << "Handling request in UserHandler::login";
    common::setJsonMime(resp);

    try
    {
        const auto apiToken = auth->login(req);

        json respBody = {{"response", "Successfully logged in"},
                         {"apiToken", apiToken}};

        resp.send(Net::Http::Code::Ok, respBody.dump());
    }
    catch (const api::AuthServiceImpl::AuthServiceException& e)
    {
        json respBody = {{"response",
                          "Couldn't log in. Invalid credentials provided."}};
        resp.send(Net::Http::Code::Unauthorized, respBody.dump());
    }
}

void UserHandler::logout(const Net::Rest::Request& req,
                         Net::Http::ResponseWriter resp)
{
    LOG_DEBUG << "Handling request in UserHandler::logout";
    common::setJsonMime(resp);

    std::string mail, apiToken;
    std::tie(mail, apiToken) = common::getTokenInfoFromRequest(req);

    try
    {
        auth->authToken(req);
        auth->logout(mail);

        json respBody = {{"response", "Successfully logged out"}};
        resp.send(Net::Http::Code::Ok, respBody.dump());
    }
    catch (const api::AuthServiceImpl::AuthServiceException& e)
    {
        json respBody = {{"response",
                          "You are not logged in"}};
        resp.send(Net::Http::Code::Unauthorized, respBody.dump());
    }
}


}
