#include "models/Chore.h"

using json = nlohmann::json;

namespace models
{

json Chore::toJson() const
{
    return json{
        {"id", id},
        {"name", name},
        {"frequency_id", frequencyId},
        {"flat_id", flatId}
    };
}

bool Chore::operator==(const Chore& rhs) const
{
    return std::tie(id, flatId, name, frequencyId) ==
           std::tie(rhs.id, rhs.flatId, rhs.name, rhs.frequencyId);
}

}
