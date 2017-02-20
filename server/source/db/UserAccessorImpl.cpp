#include "db/UserAccessor.h"
#include "db/Helpers.h"
#include "common/Logger.h"

namespace
{
constexpr auto createUserQuery{
    "INSERT INTO flat_mate.system_user \
        (mail, nickname, name, surname, password) \
        VALUES($1, $2, $3, $4, \
        crypt($5, gen_salt('bf', 8)));"}; // hash with random salt

constexpr auto deleteUserQuery{
    "DELETE FROM flat_mate.system_user \
        WHERE mail = $1;"};

constexpr auto updateUserQuery{
    "UPDATE flat_mate.system_user \
        SET nickname = $1, name = $2, surname = $3, \
            password = crypt($4, gen_salt('bf', 8)) \
        WHERE mail = $5;"};

constexpr auto getUserByEmailQuery{
    "SELECT mail, nickname, name, surname, password \
        FROM flat_mate.system_user \
        WHERE mail = $1;"};

constexpr auto authUserQuery{
    "SELECT mail, nickname, name, surname, password \
        FROM flat_mate.system_user \
        WHERE mail = $1 AND \
              password = crypt($2, password);"};
}

namespace db
{

UserAccessorImpl::UserAccessorImpl(std::shared_ptr<pqxx::connection_base> connection)
    : connection(connection)
{
    prepareStatements();
    LOG_INFO << "Creating user accessor connected to " << connection->dbname();
}

void UserAccessorImpl::prepareStatements()
{
    connection->prepare("createUser", createUserQuery);
    connection->prepare("deleteUser", deleteUserQuery);
    connection->prepare("updateUser", updateUserQuery);
    connection->prepare("getUserByEmail", getUserByEmailQuery);
    connection->prepare("authUser", authUserQuery);
}

bool UserAccessorImpl::auth(const std::string& mail,
                            const std::string& password)
{
    pqxx::work w{*connection};
    const auto result = w.prepared("authUser")
                                  (mail)
                                  (password).exec();

    return result.size() == 1;
}

void UserAccessorImpl::create(const models::User& user)
{
    pqxx::work w{*connection};

    const auto result = w.prepared("createUser")
                            (user.mail)
                            (user.username)
                            (user.name)
                            (user.surname)
                            (user.password).exec();
    w.commit();
    helpers::logStatementResult(result);
}

void UserAccessorImpl::drop(const std::string& email)
{
    pqxx::work w{*connection};

    const auto result = w.prepared("deleteUser")(email).exec();

    w.commit();
    helpers::logStatementResult(result);
}

void UserAccessorImpl::update(const models::User& user)
{
    pqxx::work w{*connection};

    const auto result = w.prepared("updateUser")
                            (user.username)
                            (user.name)
                            (user.surname)
                            (user.password)
                            (user.mail).exec();
    w.commit();
    helpers::logStatementResult(result);
}

models::User UserAccessorImpl::getByEmail(const std::string& email)
{
    pqxx::work w{*connection};

    const auto result = w.prepared("getUserByEmail")(email).exec();

    w.commit();
    helpers::logStatementResult(result);

    LOG_DEBUG << "Result size: " << result.size();

    const auto row = result.at(0);


    models::User user;
    user.mail = row["mail"].as<std::string>();
    user.username = row["nickname"].as<std::string>();
    user.name = row["name"].as<std::string>();
    user.surname = row["surname"].as<std::string>();
    user.password = row["password"].as<std::string>();

    LOG_DEBUG << user;

    return user;
}

models::User UserAccessorImpl::getByUsername(const std::string& username)
{
    return {};
}

}
