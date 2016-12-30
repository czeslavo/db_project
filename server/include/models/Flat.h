#pragma once

#include <string>

namespace models
{

struct Flat
{
    int id;
    std::string name;
    std::string admin_mail;

    bool operator==(const Flat& rhs) const;
};
}
