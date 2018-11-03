#pragma once

#include <memory>
#include "pistache/http.h"
#include "pistache/endpoint.h"
#include "pistache/description.h"

#include "db/DatabaseAccessor.h"
#include "api/AuthService.h"

namespace api
{

class FlatHandler
{
public:
    FlatHandler(std::shared_ptr<db::DatabaseAccessor> db,
                std::shared_ptr<api::AuthService> auth);

    void create(const Pistache::Rest::Request& req,
                Pistache::Http::ResponseWriter resp);

    void update(const Pistache::Rest::Request& req,
                Pistache::Http::ResponseWriter resp);

    void remove(const Pistache::Rest::Request& req,
                Pistache::Http::ResponseWriter resp);

    void addUser(const Pistache::Rest::Request& req,
                 Pistache::Http::ResponseWriter resp);

    void removeUser(const Pistache::Rest::Request& req,
                    Pistache::Http::ResponseWriter resp);

    void getUsers(const Pistache::Rest::Request& req,
                  Pistache::Http::ResponseWriter resp);

    void getUsersFlats(const Pistache::Rest::Request& req,
                       Pistache::Http::ResponseWriter resp);



private:
    std::shared_ptr<db::DatabaseAccessor> db;
    std::shared_ptr<api::AuthService> auth;
};

}
