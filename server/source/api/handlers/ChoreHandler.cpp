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

    auto updateChore = body["chore"];
    models::Chore chore{
        updateChore["id"],
        updateChore["name"],
        updateChore["frequency_id"],
        body["flat_id"]
    };

    auto choreAccess = db->getChoreAccessor();
    choreAccess->update(chore);

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

    auto choreId = req.param(":chore_id").as<int>();

    auto choreAccess = db->getChoreAccessor();
    auto chore = choreAccess->get(choreId);

    auth->forceIsFlatUser(chore.flatId, req);

    json respBody{{"response", "Got chore by id"},
                  {"chore", chore.toJson()}};
    resp.send(Net::Http::Code::Ok, respBody.dump());
}

void ChoreHandler::schedule(const Net::Rest::Request& req,
             Net::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);

    auto choreId = req.param(":chore_id").as<int>();

    auto choreAccess = db->getChoreAccessor();
    auto chore = choreAccess->get(choreId);
    auth->forceIsFlatUser(chore.flatId, req);

    auto body = json::parse(req.body());
    const int from = body["from"];
    const int to = body["to"];

    const auto result = choreAccess->schedule(choreId, from, to);

    json respBody{{"response",
        result ? "Successfully scheduled chore" : "Failed to schedule"
    }};

    resp.send(
        result ? Net::Http::Code::Ok : Net::Http::Code::Not_Modified,
        respBody.dump()
    );
}

void ChoreHandler::toggleDone(const Net::Rest::Request& req,
         Net::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);
    auth->forceIsFlatUser(req);

    const auto choreId = req.param(":chore_id").as<int>();
    const auto date = req.param(":date").as<int>();

    auto choreAccess = db->getChoreAccessor();
    choreAccess->toggleDone(choreId, date);

    json respBody{{"response", "Successfully toggled chore's done flag"}};
    resp.send(Net::Http::Code::Ok, respBody.dump());
}

void ChoreHandler::resetScheduled(const Net::Rest::Request& req,
         Net::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);
    auth->forceIsFlatUser(req);

    const auto choreId = req.param(":chore_id").as<int>();

    auto choreAccess = db->getChoreAccessor();
    choreAccess->resetScheduled(choreId);

    json respBody{{"response", "Successfully reset chore schedule"}};
    resp.send(Net::Http::Code::Ok, respBody.dump());
}

void ChoreHandler::getScheduledForFlat(const Net::Rest::Request& req,
         Net::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);
    auth->forceIsFlatUser(req);

    const auto flatId = req.param(":flat_id").as<int>();

    auto choreAccess = db->getChoreAccessor();
    auto chores = choreAccess->getScheduledForFlat(flatId);

    json choresJson = json::array();
    std::for_each(std::cbegin(chores), std::cend(chores), [&](const models::ScheduledChore c)
        { choresJson.push_back(c.toJson()); });

    json respBody{{"response", "Got chores for flat"},
                  {"chores", choresJson}};
    resp.send(Net::Http::Code::Ok, respBody.dump());
}

void ChoreHandler::getRecentlyDoneForFlat(const Net::Rest::Request& req,
         Net::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);
    auth->forceIsFlatUser(req);

    const auto flatId = req.param(":flat_id").as<int>();

    auto choreAccess = db->getChoreAccessor();
    const bool done = true;
    auto chores = choreAccess->getScheduledForFlat(flatId, done);

    json choresJson = json::array();
    std::for_each(std::cbegin(chores), std::cend(chores), [&](const models::ScheduledChore c)
        { choresJson.push_back(c.toJson()); });

    json respBody{{"response", "Got recently done chores for flat"},
                  {"chores", choresJson}};
    resp.send(Net::Http::Code::Ok, respBody.dump());
}

}
