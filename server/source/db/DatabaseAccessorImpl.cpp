#include "db/DatabaseAccessor.h"
#include "common/Logger.h"

namespace db
{

DatabaseAccessorImpl::DatabaseAccessorImpl(const std::string& opts)
    : dbOpts(opts)
{
    pqxx::connection c(dbOpts);

    if (not c.is_open())
        throw std::runtime_error("Cannot connect to \
            database with opts: " + dbOpts);
}

std::unique_ptr<UserAccessor> DatabaseAccessorImpl::getUserAccessor()
{
    return std::make_unique<UserAccessorImpl>(
        std::make_shared<pqxx::connection>(dbOpts)
    );
}

std::unique_ptr<FlatAccessor> DatabaseAccessorImpl::getFlatAccessor()
{
    return std::make_unique<FlatAccessorImpl>(
        std::make_unique<pqxx::connection>(dbOpts)
    );
}
}
