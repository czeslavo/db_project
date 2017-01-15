#include "api/AuthService.h"
#include "common/Logger.h"
#include "common/http_headers/AuthToken.h"

namespace api
{

AuthServiceImpl::AuthServiceImpl(std::shared_ptr<db::DatabaseAccessor> db)
    : db(db)
{
}

std::string AuthServiceImpl::login(const std::string& mail, const std::string& password)
{
    auto userAccess = db->getUserAccessor();

    if (not userAccess->auth(mail, password))
        throw AuthServiceException("Invalid email and/or password");

    const auto token = generateApiToken();

    loggedIn.emplace(
        mail,
        token
    );

    LOG_INFO << "User [" << mail << "] logged in";

    return loggedIn[mail];
}

std::string AuthServiceImpl::login(const Net::Rest::Request& req)
{
    std::string mail, password;
    std::tie(mail, password) = common::getLoginInfoFromRequest(req);
    return login(mail, password);
}

std::string AuthServiceImpl::generateApiToken() const
{
    // implement generating random keys
    return "dummyapitoken";
}

void AuthServiceImpl::logout(const std::string& mail)
{
    forceUserLoggedIn(mail);
    loggedIn.erase(mail);

    LOG_INFO << "User [" << mail << "] logged in";
}

void AuthServiceImpl::logout(const Net::Rest::Request& req)
{
    authToken(req);

    std::string mail;
    std::tie(mail, std::ignore) = common::getTokenInfoFromRequest(req);
    logout(mail);
}

void AuthServiceImpl::authToken(const Net::Rest::Request& req)
{
    std::string mail, token;
    std::tie(mail, token) = common::getTokenInfoFromRequest(req);
    authToken(mail, token);
}

void AuthServiceImpl::authToken(const std::string& mail,
                                const std::string& apikey)
{
    forceUserLoggedIn(mail);
    if (loggedIn[mail].compare(apikey) != 0)
    {
        LOG_INFO << "User [" << mail << "] token auth failed.";
        throw AuthServiceException("Token authentication failed");
    }
}

void AuthServiceImpl::authPassword(const std::string& mail,
                                   const std::string& password)
{
    auto userAccess = db->getUserAccessor();
    if (not userAccess->auth(mail, password))
    {
        LOG_INFO << "User [" << mail << "] password auth failed.";
        throw AuthServiceException("Password authentication failed");
    }
}

void AuthServiceImpl::forceUserLoggedIn(const std::string& username) const
{
    if (loggedIn.count(username) != 1)
        throw AuthServiceException(
            "The user is not logged in: " + username);
}

void AuthServiceImpl::authPassword(const Net::Rest::Request& req)
{
    std::string mail, password;
    std::tie(mail, password) = common::getLoginInfoFromRequest(req);
    authPassword(mail, password);
}

void AuthServiceImpl::forceIsFlatAdmin(const Net::Rest::Request& req)
{
    using json = nlohmann::json;

    authToken(req);

    auto flatAccess = db->getFlatAccessor();

    const auto flatId = getFlatIdFromRequest(req);
    auto flat = flatAccess->get(flatId);

    std::string mail;
    std::tie(mail, std::ignore) = common::getTokenInfoFromRequest(req);
    if (flat.admin_mail.compare(mail) != 0)
        throw AuthServiceException("You are not this flat's owner");
}

int AuthServiceImpl::getFlatIdFromRequest(const Net::Rest::Request& req) const
{
    LOG_DEBUG << "In getFlatIdFromRequest";
    using json = nlohmann::json;

    int flatId;
    try {
        auto body = json::parse(req.body());
        flatId = body["flat_id"];
    }
    catch (...)
    {
        // as fallback get id from url
        flatId = req.param(":id").as<int>();
    }

    LOG_DEBUG << "Got flat id: " << flatId;
    return flatId;
}

void AuthServiceImpl::forceIsFlatUser(const Net::Rest::Request& req)
{
    using json = nlohmann::json;

    authToken(req);

    auto flatAccess = db->getFlatAccessor();

    const auto flatId = getFlatIdFromRequest(req);

    std::string mail;
    std::tie(mail, std::ignore) = common::getTokenInfoFromRequest(req);

    if (not flatAccess->isFlatUser(flatId, mail))
        throw AuthServiceException("You are not this flat's user");
}


}
