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

    void create(const Net::Rest::Request& req,
                Net::Http::ResponseWriter resp);

    void update(const Net::Rest::Request& req,
                Net::Http::ResponseWriter resp);

    void remove(const Net::Rest::Request& req,
                Net::Http::ResponseWriter resp);

    void addUser(const Net::Rest::Request& req,
                 Net::Http::ResponseWriter resp);

    void removeUser(const Net::Rest::Request& req,
                    Net::Http::ResponseWriter resp);

    void getUsers(const Net::Rest::Request& req,
                  Net::Http::ResponseWriter resp);

    void getUsersFlats(const Net::Rest::Request& req,
                       Net::Http::ResponseWriter resp);

    void isAdmin(const Net::Rest::Request& req,
                       Net::Http::ResponseWriter resp);

private:
    std::shared_ptr<db::DatabaseAccessor> db;
    std::shared_ptr<api::AuthService> auth;
};

}
