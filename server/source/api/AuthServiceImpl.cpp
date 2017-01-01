#include "api/AuthService.h"

namespace api
{

AuthServiceImpl::AuthServiceImpl(std::shared_ptr<db::DatabaseAccessor> db)
    : db(db)
{
}

std::string AuthServiceImpl::login(const std::string& username, const std::string& password) 
{
    auto userAccess = db->getUserAccessor();
     
    if (not userAccess->auth(username, password))
        throw AuthServiceException("Invalid email and/or password");

    const auto token = generateApiToken();
    
    loggedIn.emplace(
        username,
        token
    );

    return loggedIn[username];
}

std::string AuthServiceImpl::generateApiToken() const
{
    // implement generating random keys
    return "dummyapitoken"; 
}

void AuthServiceImpl::logout(const std::string& username)
{    
    forceUserLoggedIn(username);
    loggedIn.erase(username); 
}

bool AuthServiceImpl::authCookies(const std::string& username,
                                  const std::string& apikey)
{
    forceUserLoggedIn(username);
    return loggedIn[username].compare(apikey) == 0;
}

bool AuthServiceImpl::authPassword(const std::string& username,
                                   const std::string& password)
{
    auto userAccess = db->getUserAccessor();
    return userAccess->auth(username, password);
}

void AuthServiceImpl::forceUserLoggedIn(const std::string& username) const
{
    if (loggedIn.count(username) != 1)
        throw AuthServiceException(
            "The user is not logged in: " + username);
}
}
