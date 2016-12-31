#include "models/Flat.h"

using json = nlohmann::json;

namespace models
{

bool Flat::operator==(const Flat& rhs) const
{
    return id == rhs.id and name == rhs.name and
           admin_mail == rhs.admin_mail;
}

std::ostream& operator<<(std::ostream& os, const Flat& flat)
{
    os << flat.toJson(); 
    return os;
}

json Flat::toJson() const
{
    return json{
        {"id", id},
        {"name", name},
        {"admin_mail", admin_mail}
    };
}

}
