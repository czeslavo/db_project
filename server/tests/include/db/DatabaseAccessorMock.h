#pragma once

#include "gmock/gmock.h"
#include "db/DatabaseAccessor.h"
#include "db/UserAccessorMock.h"

namespace db
{

class DatabaseAccessorMock : public DatabaseAccessor
{
public:
    std::unique_ptr<UserAccessor> getUserAccessor() override
    {
        return std::unique_ptr<UserAccessor>(getUserAccessorProxy());
    }

    MOCK_METHOD0(getUserAccessorProxy, UserAccessor*());
    MOCK_METHOD0(getFlatAccessor, std::unique_ptr<FlatAccessor>());
};

}
