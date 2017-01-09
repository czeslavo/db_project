#include "common/http_headers/AuthToken.h"

AuthToken::AuthToken(const std::string& token, const std::string& mail)
    : token(token), mail(mail)
{
}

void AuthToken::parse(const std::string& str)
{
    auto colon = str.find(':');
    mail = str.substr(0, colon);
    token = str.substr(colon + 1, str.length());
}

void AuthToken::write(std::ostream& os) const
{
    os << mail << ":" << token;
}

std::string AuthToken::getToken() const
{
    return token;
}

std::string AuthToken::getMail() const
{
    return mail;
}
