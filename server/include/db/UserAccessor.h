#pragma once

#include <memory>
#include <pqxx/pqxx>

#include "models/User.h"

namespace db
{

class UserAccessor
{
public:
    virtual ~UserAccessor() = default;

    virtual bool auth(const std::string& mail, 
                      const std::string& password) = 0;
    virtual void create(const models::User& user) = 0;
    virtual void drop(const std::string& email) = 0;
    virtual void update(const models::User& user) = 0;
    virtual models::User getByEmail(const std::string& email) = 0;
    virtual models::User getByUsername(const std::string& username) = 0;
};

class UserAccessorImpl : public UserAccessor
{
public:
    UserAccessorImpl(std::shared_ptr<pqxx::connection_base> connection);

    bool auth(const std::string& mail, 
              const std::string& password) override;
    void create(const models::User& user) override;
    void drop(const std::string& email) override;
    void update(const models::User& user) override;
    models::User getByEmail(const std::string& email) override;
    models::User getByUsername(const std::string& username) override;

private:
    void prepareStatements();
    std::shared_ptr<pqxx::connection_base> connection;

};
}
