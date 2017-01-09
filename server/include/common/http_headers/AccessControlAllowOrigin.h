#pragma once

#include "pistache/net.h"
#include "pistache/http_headers.h"

class AccessControlAllowOrigin : public Net::Http::Header::Header
{
public:
    NAME("Access-Control-Allow-Origin");

    AccessControlAllowOrigin();
    AccessControlAllowOrigin(const std::string& domain);

    void parse(const std::string& str) override;
    void write(std::ostream& os) const override;

private:
    std::string domain;

};
