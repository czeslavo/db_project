#pragma once

#include <string>
#include <json.hpp>

namespace models
{

struct Chore
{
    int id;
    std::string name;
    std::string frequencyId;
    int flatId;

    nlohmann::json toJson() const;
    bool operator==(const Chore& rhs) const;
};

}
