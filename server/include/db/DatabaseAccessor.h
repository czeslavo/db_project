#pragma once

#include <string>
#include <memory>

#include "db/UserAccessor.h"
#include "db/FlatAccessor.h"
#include "db/NoteAccessor.h"

namespace db
{

class DatabaseAccessor
{
public:
    virtual ~DatabaseAccessor() = default;

    virtual std::unique_ptr<UserAccessor> getUserAccessor() = 0;
    virtual std::unique_ptr<FlatAccessor> getFlatAccessor() = 0;
    virtual std::unique_ptr<NoteAccessor> getNoteAccessor() = 0;
};

class DatabaseAccessorImpl : public DatabaseAccessor
{
public:
    DatabaseAccessorImpl(const std::string& opts);

    std::unique_ptr<UserAccessor> getUserAccessor() override;
    std::unique_ptr<FlatAccessor> getFlatAccessor() override;
    std::unique_ptr<NoteAccessor> getNoteAccessor() override;

private:
    const std::string dbOpts;
};
}
