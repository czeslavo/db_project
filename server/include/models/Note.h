#pragma once

#include <string>
#include <json.hpp>

namespace models
{

struct Note
{
    int id;
    std::string content;
    int flatId;
    int date;
    bool active;
    std::string authorMail;


    nlohmann::json toJson() const;
    bool operator==(const Note& rhs) const;
};

}
