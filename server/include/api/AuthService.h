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

    virtual std::string login(const std::string& username,
                              const std::string& password) = 0;
    virtual void logout(const std::string& username) = 0;

    virtual bool authCookies(const std::string& username,
                             const std::string& apikey) = 0;
    virtual bool authPassword(const std::string& username,
                              const std::string& password) = 0;

};

class AuthServiceImpl : public AuthService
{
public:
    AuthServiceImpl(std::shared_ptr<db::DatabaseAccessor> db);

    std::string login(const std::string& username, 
               const std::string& password) override;
    void logout(const std::string& username) override;

    bool authCookies(const std::string& username, 
                     const std::string& apikey) override;
    bool authPassword(const std::string& username, 
                      const std::string& password) override;

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
