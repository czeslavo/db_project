#include "api/ApiEndpoint.h"
#include "common/Logger.h"

int main(int argc, char* argv[])
{
    Net::Port port{9080};

    int thr = 2;
    
    if (argc >= 2)
    {
        port = std::stol(argv[1]);

        if (argc == 3)
            thr = std::stol(argv[2]);
    }

    Net::Address addr(Net::Ipv4::any(), port);

    LOG_INFO << "Using " << thr << " threads";

    api::ApiEndpoint api{addr};

    api.init(thr);
    api.start();

    api.shutdown();
}
