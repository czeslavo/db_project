#pragma once

#include <memory>

#include "pistache/http.h"
#include "pistache/router.h"
#include "pistache/endpoint.h"

#include "db/DatabaseAccessor.h"

#include "db/PostgreConfig.h"

namespace api
{

class ApiEndpoint 
{
public:
    ApiEndpoint(Net::Address addres);
    
    void init(std::size_t threads = 2);
    void start();
    void shutdown();


private:
    void setupRoutes();

    void getUser(const Net::Rest::Request& req, 
                 Net::Http::ResponseWriter response);

    std::shared_ptr<Net::Http::Endpoint> httpEndpoint;
    std::shared_ptr<db::DatabaseAccessor> db{
        std::make_shared<db::DatabaseAccessorImpl>(config::db_opts)};

    Net::Rest::Router router;
};

}
