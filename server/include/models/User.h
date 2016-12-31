#pragma once

#include <string>
#include <iostream>
#include "json.hpp"

namespace models 
{

struct User
{
    std::string mail;
    std::string username;
    std::string name;
    std::string surname;
    std::string password;

    nlohmann::json toJson() const;
    bool operator==(const User& rhs) const;

    friend std::ostream& operator<<(std::ostream& os, const User& user);
};
}

