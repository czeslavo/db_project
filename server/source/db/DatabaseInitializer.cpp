#include <fstream>

#include "db/DatabaseInitializer.h"
#include "common/Logger.h"

namespace
{
constexpr auto initSqlPath{"/tmp/init_db.sql"};
constexpr auto fillSqlPath{"/tmp/fill_db.sql"};
}

namespace db
{

DatabaseInitializer::DatabaseInitializer(const std::string& opts)
    : connection(opts)
{
    LOG_INFO << "Creating DatabaseInitializer";

    if (not connection.is_open())
    {
        LOG_ERROR << "Cannot connect to db";
    }
}

void DatabaseInitializer::init()
{
    execute(initSqlPath);
}

void DatabaseInitializer::fill()
{
    execute(fillSqlPath);
}

void DatabaseInitializer::execute(const std::string& file)
{
    LOG_INFO << "Executing SQL from file " << file << " on " << connection.dbname();

    std::ifstream input{file, std::ifstream::in};
    if (not input.is_open())
    {
        throw std::runtime_error("Cannot open file " + file);
    }

    pqxx::work w(connection);

    std::string inputString;
    for(std::string line; std::getline(input, line); )
    {
        inputString += line + "\n";
    }

    try
    {
        w.exec(inputString);
        w.commit();
    }
    catch (const std::exception& e)
    {
        LOG_ERROR << e.what();
        throw;
    }
}
}
