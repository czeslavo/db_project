#pragma once

#include <memory>
#include "pistache/http.h"
#include "pistache/endpoint.h"
#include "pistache/description.h"

#include "db/DatabaseAccessor.h"
#include "api/AuthService.h"

namespace api
{

class ChoreHandler
{
public:
    ChoreHandler(std::shared_ptr<db::DatabaseAccessor> db,
                std::shared_ptr<api::AuthService> auth);

    void add(const Net::Rest::Request& req,
                   Net::Http::ResponseWriter resp);

    void remove(const Net::Rest::Request& req,
                Net::Http::ResponseWriter resp);

    void update(const Net::Rest::Request& req,
                Net::Http::ResponseWriter resp);

    void getForFlat(const Net::Rest::Request& req,
                    Net::Http::ResponseWriter resp);

    void get(const Net::Rest::Request& req,
             Net::Http::ResponseWriter resp);

    void schedule(const Net::Rest::Request& req,
             Net::Http::ResponseWriter resp);

    void toggleDone(const Net::Rest::Request& req,
             Net::Http::ResponseWriter resp);

    void getScheduledForFlat(const Net::Rest::Request& req,
             Net::Http::ResponseWriter resp);

private:
    std::shared_ptr<db::DatabaseAccessor> db;
    std::shared_ptr<api::AuthService> auth;
};

}
