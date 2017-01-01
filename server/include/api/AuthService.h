#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include <db/DatabaseAccessor.h>

namespace api
{

class AuthService 
{ 
public:
    virtual ~AuthService() = default;

    virtual void login(const std::string& username, const std::string& password) = 0;
    virtual void logout(const std::string& username) = 0;

    virtual bool authCookies(const std::string& username, std::string& apikey) = 0;
    virtual bool authPassword(const std::string& username, std::string& password) = 0;

};

class AuthServiceImpl : public AuthService
{
public:
    AuthServiceImpl(std::shared_ptr<db::DatabaseAccessor> db);

    void login(const std::string& username, const std::string& password) override;
    void logout(const std::string& username) override;

    bool authCookies(const std::string& username, std::string& apikey) override;
    bool authPassword(const std::string& username, std::string& password) override;

private:
    std::string generateApiKey() const;
    
    std::unordered_map<std::string, std::string> loggedIn;
    std::shared_ptr<db::DatabaseAccessor> db;
    
};

}
