#include "db/DatabaseAccessor.h"
#include "common/Logger.h"

namespace db
{

DatabaseAccessorImpl::DatabaseAccessorImpl(const std::string& opts)
    : connection(std::make_shared<pqxx::connection>(opts))
{
    if (connection->is_open())
    {
        LOG_INFO << "Successfully connected to the database: " << connection->dbname() <<
                    "as user: " << connection->username();
    }
    else
    {
        const auto err = "Cannot connect to the database";
        LOG_ERROR << err;
        throw std::runtime_error(err);
    }
}

std::shared_ptr<UserAccessor> DatabaseAccessorImpl::getUserAccessor()
{
   return std::make_shared<UserAccessorImpl>(connection); 
}

std::shared_ptr<FlatAccessor> DatabaseAccessorImpl::getFlatAccessor()
{
    return std::make_shared<FlatAccessorImpl>(connection); 
}
}
