#pragma once

#include <memory>
#include <pqxx/pqxx>

#include "models/Flat.h"
#include "models/User.h"

namespace db
{

class FlatAccessor
{
public:
    virtual ~FlatAccessor() = default;

    virtual void create(const models::Flat& flat) = 0;
    virtual void update(const models::Flat& flat) = 0;
    virtual void drop(const int id) = 0;
    virtual models::Flat get(const int id) = 0;
    
    virtual void addUser(const models::User& user) = 0;
    virtual void removeUser(const models::User& user) = 0;
};


class FlatAccessorImpl : public FlatAccessor
{
public:
    FlatAccessorImpl(std::shared_ptr<pqxx::connection_base> connection);

    void create(const models::Flat& flat) override;
    void update(const models::Flat& flat) override;
    void drop(const int id) override;
    models::Flat get(const int id) override;

    void addUser(const models::User& user) override;
    void removeUser(const models::User& user) override;

private:
    std::shared_ptr<pqxx::connection_base> connection;    
};
}
