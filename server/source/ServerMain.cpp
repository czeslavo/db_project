#include <thread>

#include "api/ApiEndpoint.h"
#include "common/Logger.h"

int main(int argc, char* argv[])
{
    Net::Port port{9080};

    int thr = std::thread::hardware_concurrency();
    Net::Address addr(Net::Ipv4::any(), port);

    LOG_INFO << "Using " << thr << " threads";

    api::ApiEndpoint api{addr};

    api.init(thr);
    api.start();

    api.shutdown();
}
