#pragma once

#include <string>

#include "models/User.h"

namespace db
{

class UserAccessor
{
    virtual ~UserAccessor() = default;

    virtual void createUser(const User& user) = 0;
    virtual void deleteUser(const std::string& email) = 0;
    virtual void updateUser(const User& user) = 0;
    virtual User getUserByEmail(const std::string& email) = 0;
    virtual User getUserByUsername(const std::string& username) = 0;
};
}
