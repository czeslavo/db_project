#include "models/User.h"

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
    os << "user: {\n" <<
              "\tmail: " << u.mail << ",\n" << 
              "\tusername: " << u.username << ",\n" << 
              "\tname: " << u.name << ",\n" << 
              "\tsurname: " << u.surname << ",\n" << 
          "}";

    return os;
}
}

