#include "api/handlers/NoteHandler.h"

#include "common/Logger.h"
#include "api/Common.h"
#include "models/Note.h"

using json = nlohmann::json;

namespace api
{

NoteHandler::NoteHandler(std::shared_ptr<db::DatabaseAccessor> db,
                         std::shared_ptr<api::AuthService> auth)
    : db(db), auth(auth)
{
}

void NoteHandler::add(const Pistache::Rest::Request& req,
                      Pistache::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);
    auth->forceIsFlatUser(req);

    try {
    auto body = json::parse(req.body());

    LOG_DEBUG << "Parsed request body";
    auto newNote = body["note"];
    LOG_DEBUG << "Extracted note from body";
    models::Note note{
        0,
        newNote["content"],
        body["flat_id"],
        0,
        newNote["active"],
        newNote["author_mail"]
    };

    auto noteAccess = db->getNoteAccessor();
    noteAccess->create(note);
    }
    catch (const std::exception& e)
    {
        LOG_DEBUG << "Exception caught" << e.what();
        throw;
    }
    json respBody{{"response", "Successfully created note"}};
    resp.send(Pistache::Http::Code::Created, respBody.dump());
}

void NoteHandler::remove(const Pistache::Rest::Request& req,
                         Pistache::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);
    auth->forceIsFlatUser(req);

    const int noteId = req.param(":note_id").as<int>();
    const int flatId = req.param(":flat_id").as<int>();

    auto noteAccess = db->getNoteAccessor();
    noteAccess->drop(noteId);

    json respBody{{"response", "Successfully removed note"}};
    resp.send(Pistache::Http::Code::Ok, respBody.dump());
}

void NoteHandler::update(const Pistache::Rest::Request& req,
                         Pistache::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);
    auth->forceIsFlatUser(req);

    auto body = json::parse(req.body());

    auto updateNote = body["note"];
    models::Note note{
        updateNote["id"],
        updateNote["content"],
        body["flat_id"],
        0,
        updateNote["active"],
        ""
    };

    auto noteAccess = db->getNoteAccessor();
    noteAccess->update(note);

    json respBody{{"response", "Successfully updated note"}};
    resp.send(Pistache::Http::Code::Ok, respBody.dump());
}

void NoteHandler::getForFlat(const Pistache::Rest::Request& req,
                             Pistache::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);
    auth->forceIsFlatUser(req);

    const auto flatId = req.param(":flat_id").as<int>();

    auto noteAccess = db->getNoteAccessor();
    auto notes = noteAccess->getForFlat(flatId);

    json notesJson = json::array();
    std::for_each(std::cbegin(notes), std::cend(notes), [&](const models::Note n)
        { notesJson.push_back(n.toJson()); });

    json respBody{{"response", "Got notes for flat"},
                  {"notes", notesJson}};
    resp.send(Pistache::Http::Code::Ok, respBody.dump());
}

void NoteHandler::get(const Pistache::Rest::Request& req,
                      Pistache::Http::ResponseWriter resp)
{
    common::prepareCommonResponse(resp);
    auth->authToken(req);
    auth->forceIsFlatUser(req);

    auto noteId = req.param(":note_id").as<int>();

    auto noteAccess = db->getNoteAccessor();
    auto note = noteAccess->get(noteId);

    json respBody{{"response", "Got note by id"},
                  {"note", note.toJson()}};
    resp.send(Pistache::Http::Code::Ok, respBody.dump());
}

}
