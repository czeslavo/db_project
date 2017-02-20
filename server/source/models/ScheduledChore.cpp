
#include "models/ScheduledChore.h"

using json = nlohmann::json;

namespace models
{

json ScheduledChore::toJson() const
{
    return json{
        {"id", id},
        {"name", name},
        {"date", date},
        {"assigned_mail", assignedMail},
        {"done", done}
    };
}

bool ScheduledChore::operator==(const ScheduledChore& rhs) const
{
    return std::tie(id, name, date, assignedMail, done) ==
           std::tie(rhs.id, rhs.name, rhs.date, rhs.assignedMail, rhs.done);
}

}
