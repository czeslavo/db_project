#pragma once

#include <string>
#include <iostream>

namespace models 
{

struct User
{
    std::string mail;
    std::string username;
    std::string name;
    std::string surname;
    std::string password;

    bool operator==(const User& rhs) const;
    friend std::ostream& operator<<(std::ostream& os, const User& user);
};
}

