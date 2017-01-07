#include "models/Note.h"

using json = nlohmann::json;

namespace models
{

json Note::toJson() const
{
    return json{
        {"id", id},
        {"flat_id", flatId},
        {"date", date},
        {"active", active},
        {"author_mail", authorMail}
    };
}

bool Note::operator==(const Note& rhs) const
{
    return std::tie(id, flatId, date, active, authorMail) ==
           std::tie(rhs.id, rhs.flatId, rhs.date, rhs.active, rhs.authorMail);
}

}
