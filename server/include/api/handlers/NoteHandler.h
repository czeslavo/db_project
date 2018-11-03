#pragma once

#include <memory>
#include "pistache/http.h"
#include "pistache/endpoint.h"
#include "pistache/description.h"

#include "db/DatabaseAccessor.h"
#include "api/AuthService.h"

namespace api
{

class NoteHandler
{
public:
    NoteHandler(std::shared_ptr<db::DatabaseAccessor> db,
                std::shared_ptr<api::AuthService> auth);

    void add(const Pistache::Rest::Request& req,
                   Pistache::Http::ResponseWriter resp);

    void remove(const Pistache::Rest::Request& req,
                Pistache::Http::ResponseWriter resp);

    void update(const Pistache::Rest::Request& req,
                Pistache::Http::ResponseWriter resp);

    void getForFlat(const Pistache::Rest::Request& req,
                    Pistache::Http::ResponseWriter resp);

    void get(const Pistache::Rest::Request& req,
             Pistache::Http::ResponseWriter resp);

private:
    std::shared_ptr<db::DatabaseAccessor> db;
    std::shared_ptr<api::AuthService> auth;
};

}
