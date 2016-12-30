#include "models/Flat.h"

namespace models
{

bool Flat::operator==(const Flat& rhs) const
{
    return id == rhs.id and name == rhs.name and
           admin_mail == rhs.admin_mail;
}
}
