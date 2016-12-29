#include "api/RequestHandler.h"
#include "common/Logger.h"

int main()
{
    LOG_INFO << "Starting server";
    Net::Http::listenAndServe<RequestHandler>("*:8080");
}
