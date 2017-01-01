#pragma once

#include "gmock/gmock.h"
#include "db/UserAccessor.h"

namespace db 
{

class UserAccessorMock : public UserAccessor 
{
public:
    MOCK_METHOD2(auth, bool(const std::string&, const std::string&));
    MOCK_METHOD1(create, void(const models::User&));
    MOCK_METHOD1(drop, void(const std::string&));
    MOCK_METHOD1(update, void(const models::User&));
    MOCK_METHOD1(getByEmail, models::User(const std::string&));
    MOCK_METHOD1(getByUsername, models::User(const std::string&));
};
}
