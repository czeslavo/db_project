#pragma once

#include "pistache/net.h"
#include "pistache/http_headers.h"

class AccessControlAllowHeaders : public Pistache::Http::Header::Header
{
public:
    NAME("Access-Control-Allow-Headers");

    AccessControlAllowHeaders();
    AccessControlAllowHeaders(const std::string& headers);

    void parse(const std::string& str) override;
    void write(std::ostream& os) const override;

private:
    std::string headers;

};
