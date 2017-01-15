#include "api/ApiEndpoint.h"
#include "common/http_headers/AuthToken.h"

namespace api
{

ApiEndpoint::ApiEndpoint(Net::Address address)
    : httpEndpoint(std::make_shared<Net::Http::Endpoint>(address)),
      desc("Flat mate API", "0.1")
{

}

void ApiEndpoint::init(std::size_t threads)
{
    auto opts = Net::Http::Endpoint::options()
        .threads(threads)
        .flags(Net::Tcp::Options::InstallSignalHandler);
    httpEndpoint->init(opts);

    registerHttpHeaders();
    createDescription();
}

void ApiEndpoint::registerHttpHeaders()
{
    Net::Http::Header::Registry::registerHeader<AuthToken>();
}

void ApiEndpoint::start()
{
    router.initFromDescription(desc);

    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void ApiEndpoint::shutdown()
{
    httpEndpoint->shutdown();
}

void ApiEndpoint::createDescription()
{
    using namespace Net::Rest;

    desc
        .schemes(Scheme::Http)
        .basePath("/v1")
        .produces(MIME(Application, Json))
        .consumes(MIME(Application, Json));

    auto versionPath = desc.path("/v1");

    auto userPath = versionPath.path("/user");

        userPath
            .route(desc.post("/login"))
            .bind(&UserHandler::login, &userHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "Successfully logged in");

        userPath
            .route(desc.post("/logout"))
            .bind(&UserHandler::logout, &userHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "Successfully logged out");

        userPath
            .route(desc.post("/signup"))
            .bind(&UserHandler::signup, &userHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Created, "Successfully signed up");

        userPath
            .route(desc.del("/remove"))
            .bind(&UserHandler::deleteByEmail, &userHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "User deleted.");

        userPath
            .route(desc.put("/update"))
            .bind(&UserHandler::update, &userHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "User updated.");

        userPath
            .route(desc.get("/:mail"))
            .bind(&UserHandler::getByEmail, &userHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "User with a given e-mail");


    auto flatPath = versionPath.path("/flat");

        flatPath
            .route(desc.post("/create"))
            .bind(&FlatHandler::create, &flatHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Created, "Successfully created flat");

        flatPath
            .route(desc.put("/update"))
            .bind(&FlatHandler::update, &flatHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "Successfully updated flat");

        flatPath
            .route(desc.del("/remove/:flat_id"))
            .bind(&FlatHandler::remove, &flatHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "Successfully removed flat");

        flatPath
            .route(desc.post("/adduser"))
            .bind(&FlatHandler::addUser, &flatHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "Successfuly added user");

        flatPath
            .route(desc.del("/removeuser"))
            .bind(&FlatHandler::removeUser, &flatHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "Successfuly removed user from flat");

        flatPath
            .route(desc.get("/:flat_id/getusers"))
            .bind(&FlatHandler::getUsers, &flatHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "Users of flat");

        flatPath
            .route(desc.get("/getforuser"))
            .bind(&FlatHandler::getUsersFlats, &flatHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "User's flats");

    auto notePath = versionPath.path("/note");

        notePath
            .route(desc.post("/add"))
            .bind(&NoteHandler::add, &noteHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Created, "Successfully created note");

        notePath
            .route(desc.put("/update"))
            .bind(&NoteHandler::update, &noteHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "Successfully updated note");

        notePath
            .route(desc.del("/remove/:flat_id/:note_id"))
            .bind(&NoteHandler::remove, &noteHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "Successfully removed note");

        notePath
            .route(desc.get("/getforflat/:flat_id"))
            .bind(&NoteHandler::getForFlat, &noteHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "Notes which belong to the flat");

        notePath
            .route(desc.get("/get/:note_id"))
            .bind(&NoteHandler::get, &noteHandler)
            .produces(MIME(Application, Json))
            .response(Net::Http::Code::Ok, "Note with given id");

}



}
