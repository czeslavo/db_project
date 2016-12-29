#include "api/RequestHandler.h"

using namespace Net;

void RequestHandler::onRequest(const Http::Request &request, 
                               Http::ResponseWriter response)
{
    if (request.method() == Http::Method::Post)
    {
        response.send(Http::Code::Ok, "Hello Post");        

    }
    else if (request.method() == Http::Method::Get)
    {
        response.send(Http::Code::Ok, "Hello Get");
    }

    response.send(Http::Code::Ok, "Hello, World!");
}
