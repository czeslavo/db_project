#include "db/FlatAccessor.h"

namespace db 
{

FlatAccessorImpl::FlatAccessorImpl(std::shared_ptr<pqxx::connection> connection)
    : connection(connection)
{
    
}

void FlatAccessorImpl::create(const models::Flat& flat)
{

}

void FlatAccessorImpl::update(const models::Flat& flat)
{

}

void FlatAccessorImpl::drop(const int id)
{

}

models::Flat FlatAccessorImpl::get(const int id)
{

}

void FlatAccessorImpl::addUser(const models::User& user)
{

}

void FlatAccessorImpl::removeUser(const models::User& user)
{

}

}
