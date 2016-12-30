#include "models/User.h"

namespace models
{
    
bool User::operator==(const User& rhs) const
{
    return mail == rhs.mail && username == rhs.username &&
           name == rhs.name && surname == rhs.surname &&
           password == rhs.password;
}

}
