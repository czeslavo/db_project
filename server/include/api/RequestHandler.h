#pragma once

#include "pistache/endpoint.h"

class RequestHandler : public Net::Http::Handler
{
public:
    HTTP_PROTOTYPE(RequestHandler)

    void onRequest(const Net::Http::Request& request, 
                   Net::Http::ResponseWriter response);

};
