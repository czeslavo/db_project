#include "api/RequestHandler.h"

int main()
{
    Net::Http::listenAndServe<RequestHandler>("*:8080");
}
