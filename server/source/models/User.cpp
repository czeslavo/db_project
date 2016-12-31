#include "models/User.h"
#include "json.hpp"

using json = nlohmann::json;

namespace models
{
    
bool User::operator==(const User& rhs) const
{
    return mail == rhs.mail && username == rhs.username &&
           name == rhs.name && surname == rhs.surname &&
           password == rhs.password;
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

