#include "api/ApiEndpoint.h"

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

    createDescription();
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
        .route(desc.post("/"))
        .bind(&UserHandler::create, &userHandler)
        .produces(MIME(Application, Json))
        .response(Net::Http::Code::Created, "Successfully created the user"); 

    userPath
        .route(desc.get("/:mail"))
        .bind(&UserHandler::getByEmail, &userHandler)
        .produces(MIME(Application, Json))
        .response(Net::Http::Code::Ok, "User with a given e-mail");

    userPath
        .route(desc.del("/"))
        .bind(&UserHandler::deleteByEmail, &userHandler)
        .produces(MIME(Application, Json))
        .response(Net::Http::Code::Ok, "User deleted.");

    userPath
        .route(desc.put("/"))
        .bind(&UserHandler::update, &userHandler)
        .produces(MIME(Application, Json))
        .response(Net::Http::Code::Ok, "User updated.");
}



}
