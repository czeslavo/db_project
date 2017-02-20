#include "db/ChoreAccessor.h"
#include "db/Helpers.h"

namespace
{
constexpr auto createChoreQuery{
    "INSERT INTO flat_mate.chore (name, frequency_id, flat_id) \
	    VALUES($1, $2, $3);"};

constexpr auto removeChoreQuery{
    "DELETE FROM flat_mate.chore \
        WHERE id = $1;"};

constexpr auto updateChoreQuery{
    "UPDATE flat_mate.chore \
        SET name = $1, frequency_id = $2 \
        WHERE id = $3;"};

constexpr auto getChoresForFlatQuery{
    "SELECT id, name, frequency_id, flat_id \
        FROM flat_mate.chore \
        WHERE flat_id = $1;"};

constexpr auto getChoreByIdQuery{
    "SELECT c.id, c.name, c.frequency_id, c.flat_id \
        FROM flat_mate.chore c \
        WHERE c.id = $1;"};

constexpr auto scheduleChoreQuery{
    "SELECT schedule_chore_from_to($1, $2, $3) as result;"};

constexpr auto getScheduledChoresForFlatQuery{
    "SELECT * FROM get_scheduled_chores_for_flat($1);"};

}

namespace db
{

ChoreAccessorImpl::ChoreAccessorImpl(std::shared_ptr<pqxx::connection_base> connection)
    : connection(connection)
{
    prepareStatements();
}

void ChoreAccessorImpl::prepareStatements()
{
    connection->prepare("createChore", createChoreQuery);
    connection->prepare("removeChore", removeChoreQuery);

    connection->prepare("updateChore", updateChoreQuery);
    connection->prepare("getChoresForFlat", getChoresForFlatQuery);
    connection->prepare("getChoreById", getChoreByIdQuery);

    connection->prepare("scheduleChore", scheduleChoreQuery);
    connection->prepare("getScheduledChoresForFlat", getScheduledChoresForFlatQuery);

}

void ChoreAccessorImpl::create(const models::Chore& chore)
{
   pqxx::work w{*connection};
   const auto result = w.prepared("createChore")
                                 (chore.name)
                                 (chore.frequencyId)
                                 (chore.flatId).exec();
   w.commit();
   helpers::logStatementResult(result);
}

void ChoreAccessorImpl::drop(const int choreId)
{
   pqxx::work w{*connection};
   const auto result = w.prepared("removeChore")
                                 (choreId).exec();
   w.commit();
   helpers::logStatementResult(result);
}

void ChoreAccessorImpl::update(const models::Chore& chore)
{

   pqxx::work w{*connection};
   const auto result = w.prepared("updateChore")
                                 (chore.name)
                                 (chore.frequencyId)
                                 (chore.id).exec();
   w.commit();
   helpers::logStatementResult(result);
}

std::vector<models::Chore> ChoreAccessorImpl::getForFlat(const int flatId)
{
    pqxx::work w{*connection};
    const auto result = w.prepared("getChoresForFlat")
                                 (flatId).exec();

    w.commit();
    helpers::logStatementResult(result);

    std::vector<models::Chore> chores;
    chores.reserve(result.size());

    std::for_each(std::cbegin(result), std::cend(result),
        [&](const pqxx::tuple row) {
            chores.push_back(models::Chore{
                row["id"].as<int>(),
                row["name"].as<std::string>(),
                row["frequency_id"].as<std::string>(),
                row["flat_id"].as<int>()
            });
        }
    );

    return chores;
}

models::Chore ChoreAccessorImpl::get(const int choreId)
{
    pqxx::work w{*connection};
    const auto result = w.prepared("getChoreById")
                                 (choreId).exec();

    w.commit();
    helpers::logStatementResult(result);

    auto row = result.at(0);

    return models::Chore{
        row["id"].as<int>(),
        row["name"].as<std::string>(),
        row["frequency_id"].as<std::string>(),
        row["flat_id"].as<int>()
    };
}

bool ChoreAccessorImpl::schedule(const int choreId, const int from, const int to)
{
    pqxx::work w{*connection};
    const auto result = w.prepared("scheduleChore")
                                  (choreId)
                                  (from)
                                  (to).exec();

    w.commit();
    helpers::logStatementResult(result);

    return result.at(0)["result"].as<bool>();
}

std::vector<models::ScheduledChore> ChoreAccessorImpl::getScheduledForFlat(const int flatId)
{
    pqxx::work w{*connection};
    const auto result = w.prepared("getScheduledChoresForFlat")
                                 (flatId).exec();

    w.commit();
    helpers::logStatementResult(result);

    std::vector<models::ScheduledChore> chores;
    chores.reserve(result.size());

    std::for_each(std::cbegin(result), std::cend(result),
        [&](const pqxx::tuple row) {
            chores.push_back(models::ScheduledChore{
                row["chore_id"].as<int>(),
                row["name"].as<std::string>(),
                row["date"].as<int>(),
                row["assigned_mail"].as<std::string>(),
                row["done"].as<bool>()
            });
        }
    );

    return chores;
}

}
