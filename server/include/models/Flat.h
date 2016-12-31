#pragma once

#include <string>
#include <iostream>
#include "json.hpp"

namespace models
{

struct Flat
{
    int id;
    std::string name;
    std::string admin_mail;

    nlohmann::json toJson() const;
    bool operator==(const Flat& rhs) const;
    friend std::ostream& operator<<(std::ostream& os, const Flat& flat);
};
}
