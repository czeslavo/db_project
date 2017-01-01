#include "api/AuthService.h"

namespace api
{

AuthServiceImpl::AuthServiceImpl(std::shared_ptr<db::DatabaseAccessor> db)
    : db(db)
{
}

void AuthServiceImpl::login(const std::string& username, const std::string& password) 
{
    auto userAccess = db->getUserAccessor();
    // userAccess->login(username, password);
    loggedIn.emplace(
        username,
        generateApiKey()
    );
}

std::string AuthServiceImpl::generateApiKey() const
{

}

void AuthServiceImpl::logout(const std::string& username)
{
}

bool AuthServiceImpl::authCookies(const std::string& username, std::string& apikey)
{
    return true;
}

bool AuthServiceImpl::authPassword(const std::string& username, std::string& password)
{
    return true;
}

}
