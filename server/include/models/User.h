#pragma once

#include <string>

namespace models 
{

struct User
{
    std::string username;
    std::string name;
    std::string surname;
    std::string mail;
    std::string password;

    bool operator==(const User& rhs) const;
};
}
