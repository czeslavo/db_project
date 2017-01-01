#include "models/User.h"
#include "json.hpp"
#include <tuple>

using json = nlohmann::json;

namespace models
{
    
bool User::operator==(const User& rhs) const
{
    return std::tie(mail, username, name, surname) ==
           std::tie(rhs.mail, rhs.username, rhs.name, rhs.surname);
}

std::ostream& operator<<(std::ostream& os, const User& u)
{ 
    os << u.toJson();
    return os;
}

json User::toJson() const
{    
    return json{
        {"mail", mail},
        {"username", username},
        {"name", name},
        {"surname", surname}
    }; 
}
}

