#include "common/http_headers/AccessControlAllowOrigin.h"


AccessControlAllowOrigin::AccessControlAllowOrigin()
    : domain("*")
{
}

AccessControlAllowOrigin::AccessControlAllowOrigin(const std::string& domain)
    : domain(domain)
{
}

void AccessControlAllowOrigin::parse(const std::string& str)
{
    domain = str;
}

void AccessControlAllowOrigin::write(std::ostream& os) const
{
    os << domain;
}
