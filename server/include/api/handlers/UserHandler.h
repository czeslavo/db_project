#pragma once

#include <memory>
#include "pistache/http.h"
#include "pistache/endpoint.h"
#include "pistache/description.h"

#include "db/DatabaseAccessor.h"
#include "api/AuthService.h"

namespace api
{

class UserHandler
{
public:
    UserHandler(std::shared_ptr<db::DatabaseAccessor> db,
                std::shared_ptr<api::AuthService> auth);

    void getByEmail(const Pistache::Rest::Request& req,
                    Pistache::Http::ResponseWriter resp);

    void signup(const Pistache::Rest::Request& req,
                    Pistache::Http::ResponseWriter resp);

    void deleteByEmail(const Pistache::Rest::Request& req,
                    Pistache::Http::ResponseWriter resp);

    void update(const Pistache::Rest::Request& req,
                    Pistache::Http::ResponseWriter resp);

    void login(const Pistache::Rest::Request& req,
                    Pistache::Http::ResponseWriter resp);

    void logout(const Pistache::Rest::Request& req,
                    Pistache::Http::ResponseWriter resp);

private:
    std::shared_ptr<db::DatabaseAccessor> db;
    std::shared_ptr<api::AuthService> auth;
};

}
