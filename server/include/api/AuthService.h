#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "db/DatabaseAccessor.h"
#include "api/Common.h"

namespace api
{

class AuthService
{
public:
    virtual ~AuthService() = default;

    virtual std::string login(const std::string& username,
                              const std::string& password) = 0;
    virtual std::string login(const Net::Rest::Request& req) = 0;

    virtual void logout(const std::string& username) = 0;
    virtual void logout(const Net::Rest::Request& req) = 0;

    virtual void authToken(const std::string& username,
                             const std::string& apikey) = 0;
    virtual void authToken(const Net::Rest::Request& req) = 0;

    virtual void authPassword(const std::string& username,
                              const std::string& password) = 0;
    virtual void authPassword(const Net::Rest::Request& req) = 0;

    virtual void forceIsFlatAdmin(const Net::Rest::Request& req) = 0;
    virtual void forceIsFlatUser(const Net::Rest::Request& req) = 0;

};

class AuthServiceImpl : public AuthService
{
public:
    AuthServiceImpl(std::shared_ptr<db::DatabaseAccessor> db);

    std::string login(const std::string& username,
               const std::string& password) override;
    std::string login(const Net::Rest::Request& req) override;

    void logout(const std::string& username) override;
    void logout(const Net::Rest::Request& req) override;

    void authToken(const std::string& username,
                     const std::string& apikey) override;
    void authPassword(const std::string& username,
                      const std::string& password) override;

    void authToken(const Net::Rest::Request& req) override;
    void authPassword(const Net::Rest::Request& req) override;

    void forceIsFlatAdmin(const Net::Rest::Request& req) override;
    void forceIsFlatUser(const Net::Rest::Request& req) override;

    class AuthServiceException : public std::runtime_error {
    public:
        AuthServiceException(const std::string& msg)
            : std::runtime_error(msg)
        {}
    };


private:
    std::string generateApiToken() const;
    void forceUserLoggedIn(const std::string& username) const;

    std::unordered_map<std::string, std::string> loggedIn;
    std::shared_ptr<db::DatabaseAccessor> db;

};

}
