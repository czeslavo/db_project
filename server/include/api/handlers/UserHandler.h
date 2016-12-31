#pragma once

#include <memory>
#include "pistache/http.h"
#include "pistache/endpoint.h"
#include "pistache/description.h"

#include "db/DatabaseAccessor.h"

namespace api 
{

class UserHandler
{
public:
    UserHandler(std::shared_ptr<db::DatabaseAccessor> db);

    void getByEmail(const Net::Rest::Request& req, 
                    Net::Http::ResponseWriter resp);

    void create(const Net::Rest::Request& req, 
                    Net::Http::ResponseWriter resp);

    void deleteByEmail(const Net::Rest::Request& req, 
                    Net::Http::ResponseWriter resp);
    
    void update(const Net::Rest::Request& req, 
                    Net::Http::ResponseWriter resp);

private:
    std::shared_ptr<db::DatabaseAccessor> db;
};

}
