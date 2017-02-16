#include "api/handlers/ChoreHandler.h"

#include "common/Logger.h"
#include "api/Common.h"
#include "models/Chore.h"

using json = nlohmann::json;

namespace api
{

ChoreHandler::ChoreHandler(std::shared_ptr<db::DatabaseAccessor> db,
                         std::shared_ptr<api::AuthService> auth)
    : db(db), auth(auth)
{
}

void ChoreHandler::add(const Net::Rest::Request& req,
                      Net::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);
    auth->forceIsFlatUser(req);

    try
    {
        auto body = json::parse(req.body());

        LOG_DEBUG << "Parsed request body";
        auto newChore = body["chore"];

        models::Chore chore{
            0,
            newChore["name"],
            newChore["frequency_id"],
            body["flat_id"],
        };

        auto choreAccess = db->getChoreAccessor();
        choreAccess->create(chore);
    }
    catch (const std::exception& e)
    {
        LOG_DEBUG << "Exception caught" << e.what();
        throw;
    }

    json respBody{{"response", "Successfully created chore"}};
    resp.send(Net::Http::Code::Created, respBody.dump());
}

void ChoreHandler::remove(const Net::Rest::Request& req,
                         Net::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);
    auth->forceIsFlatUser(req);

    const int choreId = req.param(":chore_id").as<int>();
    const int flatId = req.param(":flat_id").as<int>();

    auto choreAccess = db->getChoreAccessor();
    choreAccess->drop(choreId);

    json respBody{{"response", "Successfully removed chore"}};
    resp.send(Net::Http::Code::Ok, respBody.dump());
}

void ChoreHandler::update(const Net::Rest::Request& req,
                         Net::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);
    auth->forceIsFlatUser(req);

    auto body = json::parse(req.body());
/*
    auto updateChore = body["chore"];
    models::Chore chore{
        updateChore["id"],
        updateChore["content"],
        body["flat_id"],
        0,
        updateChore["active"],
        ""
    };

    auto choreAccess = db->getChoreAccessor();
    choreAccess->update(chore);
*/
    json respBody{{"response", "Successfully updated chore"}};
    resp.send(Net::Http::Code::Ok, respBody.dump());
}

void ChoreHandler::getForFlat(const Net::Rest::Request& req,
                             Net::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);
    auth->forceIsFlatUser(req);

    const auto flatId = req.param(":flat_id").as<int>();

    auto choreAccess = db->getChoreAccessor();
    auto chores = choreAccess->getForFlat(flatId);

    json choresJson = json::array();
    std::for_each(std::cbegin(chores), std::cend(chores), [&](const models::Chore c)
        { choresJson.push_back(c.toJson()); });

    json respBody{{"response", "Got chores for flat"},
                  {"chores", choresJson}};
    resp.send(Net::Http::Code::Ok, respBody.dump());
}

void ChoreHandler::get(const Net::Rest::Request& req,
                      Net::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);
    auth->forceIsFlatUser(req);

    auto choreId = req.param(":chore_id").as<int>();

    auto choreAccess = db->getChoreAccessor();
    auto chore = choreAccess->get(choreId);

    json respBody{{"response", "Got chore by id"},
                  {"chore", chore.toJson()}};
    resp.send(Net::Http::Code::Ok, respBody.dump());
}

}
