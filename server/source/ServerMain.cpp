#include <thread>

#include "api/ApiEndpoint.h"
#include "common/Logger.h"

int main(int argc, char* argv[])
{
    Pistache::Port port{9090};

    int thr = std::thread::hardware_concurrency();
    Pistache::Address addr(Pistache::Ipv4::any(), port);

    LOG_INFO << "Using " << thr << " threads";

    api::ApiEndpoint api{addr};

    api.init(thr);
    api.start();

    api.shutdown();
}
