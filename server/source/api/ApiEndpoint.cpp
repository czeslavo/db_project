#include <sstream>

#include "api/ApiEndpoint.h"

namespace api
{

ApiEndpoint::ApiEndpoint(Net::Address address)
    : httpEndpoint(std::make_shared<Net::Http::Endpoint>(address))
{

}

void ApiEndpoint::init(std::size_t threads)
{
    auto opts = Net::Http::Endpoint::options()
        .threads(threads)
        .flags(Net::Tcp::Options::InstallSignalHandler);
    httpEndpoint->init(opts);
    setupRoutes();
}

void ApiEndpoint::start()
{
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void ApiEndpoint::shutdown()
{
    httpEndpoint->shutdown();
}

void ApiEndpoint::setupRoutes()
{
    using namespace Net::Rest;

    Routes::Get(router, "/user/:mail", Routes::bind(&ApiEndpoint::getUser, this));
}

 
void ApiEndpoint::getUser(const Net::Rest::Request& req, 
             Net::Http::ResponseWriter response)
{
    const auto mail = req.param(":mail").as<std::string>();

    auto userAccess = db->getUserAccessor();
    
    try 
    {
        const auto user = userAccess->getByEmail(mail);
        std::stringstream output;
        output << user;

        response.send(Net::Http::Code::Ok, output.str());
    }
    catch (const std::exception& e)
    {
        response.send(Net::Http::Code::Not_Found);
    }
    
}


}
