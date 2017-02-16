#pragma once

#include <memory>

#include "pistache/http.h"
#include "pistache/router.h"
#include "pistache/endpoint.h"
#include "pistache/description.h"

#include "db/DatabaseAccessor.h"

#include "api/AuthService.h"
#include "api/handlers/UserHandler.h"
#include "api/handlers/FlatHandler.h"
#include "api/handlers/NoteHandler.h"
#include "api/handlers/ChoreHandler.h"

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
    void createDescription();
    void registerHttpHeaders();

    std::shared_ptr<Net::Http::Endpoint> httpEndpoint;
    std::shared_ptr<db::DatabaseAccessor> db{
        std::make_shared<db::DatabaseAccessorImpl>(config::db_opts)};
    std::shared_ptr<api::AuthService> auth{
        std::make_shared<AuthServiceImpl>(db)};

    UserHandler userHandler{db, auth};
    FlatHandler flatHandler{db, auth};
    NoteHandler noteHandler{db, auth};
    ChoreHandler choreHandler{db, auth};

    Net::Rest::Description desc;
    Net::Rest::Router router;
};

}
