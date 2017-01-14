#include "db/FlatAccessor.h"
#include "common/Logger.h"
#include "db/Helpers.h"

namespace
{
constexpr auto createFlatQuery{
    "INSERT INTO flat_mate.flat \
        (name, flat_admin_mail) \
        VALUES($1, $2) \
        RETURNING id;"};

constexpr auto updateFlatQuery{
    "UPDATE flat_mate.flat \
        SET name = $1, flat_admin_mail = $2 \
        WHERE id = $3;"};

constexpr auto deleteFlatQuery{
    "DELETE FROM flat_mate.flat \
        WHERE id = $1;"};

constexpr auto getFlatByIdQuery{
    "SELECT id, name, flat_admin_mail \
        FROM flat_mate.flat \
        WHERE id = $1;"};

constexpr auto addUserToFlatQuery{
    "INSERT INTO flat_mate.flat_user \
        (flat_id, user_mail) \
        VALUES($1, $2);"};

constexpr auto deleteUserFromFlatQuery{
    "DELETE FROM flat_mate.flat_user \
        WHERE flat_id = $1 AND user_mail = $2;"};

constexpr auto getFlatUsersQuery{
    "SELECT u.mail, u.nickname, u.name, u.surname, u.password \
        FROM flat_mate.flat_user fu \
        JOIN flat_mate.system_user u ON \
            u.mail = fu.user_mail \
        WHERE fu.flat_id = $1;"};

constexpr auto isFlatUserQuery{
    "SELECT u.mail FROM flat_mate.flat_user fu \
        JOIN flat_mate.system_user u ON \
            u.mail = fu.user_mail \
        WHERE fu.flat_id = $1 AND \
              u.mail = $2;"};

constexpr auto getUsersFlatsQuery{
    "SELECT f.id, f.name, f.flat_admin_mail FROM flat_mate.flat_user fu \
        JOIN flat_mate.flat f ON \
            f.id = fu.flat_id \
        WHERE fu.user_mail = $1;"};

}


namespace db
{

FlatAccessorImpl::FlatAccessorImpl(std::shared_ptr<pqxx::connection_base> connection)
    : connection(connection)
{
   LOG_INFO << "Creating flat accessor";
   prepareStatements();
}

void FlatAccessorImpl::prepareStatements()
{
    connection->prepare("createFlat", createFlatQuery);
    connection->prepare("updateFlat", updateFlatQuery);
    connection->prepare("deleteFlat", deleteFlatQuery);
    connection->prepare("getFlatById", getFlatByIdQuery);
    connection->prepare("addUserToFlat", addUserToFlatQuery);
    connection->prepare("deleteUserFromFlat", deleteUserFromFlatQuery);
    connection->prepare("getFlatUsers", getFlatUsersQuery);
    connection->prepare("isFlatUser", isFlatUserQuery);
    connection->prepare("getUsersFlats", getUsersFlatsQuery);
}


void FlatAccessorImpl::create(const models::Flat& flat)
{
    LOG_DEBUG << "FlatAccessor::create";
    pqxx::work w(*connection);

    const auto creatingResult = w.prepared("createFlat")
                                          (flat.name)
                                          (flat.admin_mail).exec();
    LOG_DEBUG << "creating flat";

    const auto flatId = creatingResult.at(0)["id"].as<int>();
    LOG_DEBUG << "reading result of creating";

    const auto addingToFlatResult = w.prepared("addUserToFlat")
                                              (flatId)
                                              (flat.admin_mail).exec();

    LOG_DEBUG << "adding user result";
    w.commit();
    helpers::logStatementResult(creatingResult);
}

void FlatAccessorImpl::update(const models::Flat& flat)
{
    pqxx::work w(*connection);

    const auto result = w.prepared("updateFlat")
                                  (flat.name)
                                  (flat.admin_mail)
                                  (flat.id).exec();
    w.commit();
    helpers::logStatementResult(result);
}

void FlatAccessorImpl::drop(const int id)
{
    pqxx::work w(*connection);

    const auto result = w.prepared("deleteFlat")
                                  (id).exec();
    w.commit();
    helpers::logStatementResult(result);
}

models::Flat FlatAccessorImpl::get(const int id)
{
    pqxx::work w(*connection);

    const auto result = w.prepared("getFlatById")(id).exec();

    w.commit();
    helpers::logStatementResult(result);

    const auto row = result.at(0);

    return models::Flat{
        row["id"].as<int>(),
        row["name"].as<std::string>(),
        row["flat_admin_mail"].as<std::string>()
    };
}

void FlatAccessorImpl::addUser(const int flatId, const std::string& userMail)
{
    pqxx::work w(*connection);

    const auto result = w.prepared("addUserToFlat")
                                  (flatId)
                                  (userMail).exec();
    w.commit();
    helpers::logStatementResult(result);
}

void FlatAccessorImpl::removeUser(const int flatId, const std::string& userMail)
{
    pqxx::work w(*connection);

    const auto result = w.prepared("deleteUserFromFlat")
                                  (flatId)
                                  (userMail).exec();
    w.commit();
    helpers::logStatementResult(result);
}

std::vector<models::User> FlatAccessorImpl::getUsers(const int id)
{
    pqxx::work w(*connection);

    const auto result = w.prepared("getFlatUsers")(id).exec();

    w.commit();
    helpers::logStatementResult(result);

    std::vector<models::User> users;
    users.reserve(result.size());

    std::for_each(std::cbegin(result), std::cend(result),
        [&](const pqxx::tuple row){
            users.push_back(models::User{
                row["mail"].as<std::string>(),
                row["nickname"].as<std::string>(),
                row["name"].as<std::string>(),
                row["surname"].as<std::string>(),
                row["password"].as<std::string>()
            });
        }
    );

    return users;
}

bool FlatAccessorImpl::isFlatUser(const int flatId, const std::string& userMail)
{
    pqxx::work w(*connection);

    const auto result = w.prepared("isFlatUser")
                                  (flatId)
                                  (userMail).exec();
    w.commit();
    helpers::logStatementResult(result);

    return result.size() == 1;
}

std::vector<models::Flat> FlatAccessorImpl::getUsersFlats(const std::string& userMail)
{
    pqxx::work w(*connection);

    const auto result = w.prepared("getUsersFlats")
                                  (userMail).exec();
    w.commit();
    helpers::logStatementResult(result);

    std::vector<models::Flat> flats;
    flats.reserve(result.size());

    std::for_each(std::cbegin(result), std::cend(result),
        [&](const pqxx::tuple row){
            flats.push_back(models::Flat{
                row["id"].as<int>(),
                row["name"].as<std::string>(),
                row["flat_admin_mail"].as<std::string>()
            });
        }
    );

    return flats;
}

}
