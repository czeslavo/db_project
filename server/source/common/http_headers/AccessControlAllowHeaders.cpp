#include "common/http_headers/AccessControlAllowHeaders.h"


AccessControlAllowHeaders::AccessControlAllowHeaders()
    : headers("")
{
}

AccessControlAllowHeaders::AccessControlAllowHeaders(const std::string& headers)
    : headers(headers)
{
}

void AccessControlAllowHeaders::parse(const std::string& str)
{
    headers = str;
}

void AccessControlAllowHeaders::write(std::ostream& os) const
{
    os << headers;
}
