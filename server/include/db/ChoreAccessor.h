#pragma once

#include <memory>
#include <pqxx/pqxx>
#include <vector>

#include "models/Chore.h"

namespace db
{

class ChoreAccessor
{
public:
    virtual ~ChoreAccessor() = default;

    virtual void create(const models::Chore& chore) = 0;
    virtual void drop(const int choreId) = 0;
    virtual void update(const models::Chore& chore) = 0;
    virtual std::vector<models::Chore> getForFlat(const int flatId) = 0;
    virtual models::Chore get(const int choreId) = 0;
};

class ChoreAccessorImpl : public ChoreAccessor
{
public:
    ChoreAccessorImpl(std::shared_ptr<pqxx::connection_base> connection);

    void create(const models::Chore& chore) override;
    void drop(const int choreId) override;
    void update(const models::Chore& chore) override;
    std::vector<models::Chore> getForFlat(const int flatId) override;
    models::Chore get(const int choreId) override;

private:
    void prepareStatements();
    std::shared_ptr<pqxx::connection_base> connection;

};
}
