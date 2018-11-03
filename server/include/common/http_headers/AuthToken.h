#pragma once

#include "pistache/net.h"
#include "pistache/http_headers.h"

class AuthToken : public Pistache::Http::Header::Header
{
public:
    NAME("Auth-Token");

    AuthToken() = default;
    AuthToken(const std::string& token, const std::string& mail);

    void parse(const std::string& str) override;
    void write(std::ostream& os) const override;

    std::string getToken() const;
    std::string getMail() const;

private:
    std::string token;
    std::string mail;
};
