#include "db/UserAccessor.h"


namespace db
{

UserAccessorImpl::UserAccessorImpl(std::shared_ptr<pqxx::connection> connection)
    : connection(connection)
{
}

void UserAccessorImpl::create(const models::User& user)
{}

void UserAccessorImpl::drop(const std::string& email)
{}

void UserAccessorImpl::update(const models::User& user)
{}

models::User UserAccessorImpl::getByEmail(const std::string& email)
{}

models::User UserAccessorImpl::getByUsername(const std::string& username)
{}

}
