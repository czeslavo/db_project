#include "api/handlers/UserHandler.h"
#include "common/Logger.h"
#include "json.hpp"

using json = nlohmann::json;

namespace api
{

void setJsonMime(Net::Http::ResponseWriter& resp)
{
    resp.setMime(MIME(Application, Json));
}

UserHandler::UserHandler(std::shared_ptr<db::DatabaseAccessor> db)
    : db(db)
{
}

void UserHandler::getByEmail(const Net::Rest::Request& req, 
                    Net::Http::ResponseWriter resp)
{
    LOG_DEBUG << "Handling request in UserHandler::getByEmail";
    setJsonMime(resp);

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

void UserHandler::create(const Net::Rest::Request& req, 
                    Net::Http::ResponseWriter resp)
{
    LOG_DEBUG << "Handling request in UserHandler::create";
    setJsonMime(resp); 

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
        resp.send(Net::Http::Code::Not_Modified);
    }
}

void UserHandler::deleteByEmail(const Net::Rest::Request& req,
                                Net::Http::ResponseWriter resp)
{
    LOG_DEBUG << "Handling request in UserHandler::deleteByEmail";
    setJsonMime(resp);

    json reqBody = json::parse(req.body()); 
    // should auth here on username and password

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
    setJsonMime(resp);

    json reqBody = json::parse(req.body());

    models::User user{
        reqBody["mail"],
        reqBody["username"],
        reqBody["name"],
        reqBody["surname"],
        reqBody["password"]
    };

    // should auth here

    try
    {
        auto userAccess = db->getUserAccessor();
        userAccess->update(user);
        
        json respBody = {{"response", "User successfully updated"}};
        resp.send(Net::Http::Code::Ok, respBody.dump());
    }
    catch (const std::exception& e)
    {
        resp.send(Net::Http::Code::Not_Found, "User with given email not found");
    }
}


}
