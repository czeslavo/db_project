#pragma once

#include <string>
#include <memory>

#include "db/UserAccessor.h"
#include "db/FlatAccessor.h"

namespace db 
{

class DatabaseAccessor
{
public:
    virtual ~DatabaseAccessor() = default;

    virtual std::shared_ptr<UserAccessor> getUserAccessor() = 0;
    virtual std::shared_ptr<FlatAccessor> getFlatAccessor() = 0;

};
}
