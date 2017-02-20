#pragma once

#include <string>
#include <json.hpp>

namespace models
{

struct ScheduledChore
{
    int id;
    std::string name;
    int date;
    std::string assignedMail;
    bool done;

    nlohmann::json toJson() const;
    bool operator==(const ScheduledChore& rhs) const;
};

}
