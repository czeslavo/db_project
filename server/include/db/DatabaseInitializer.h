#pragma once

#include <string>
#include <pqxx/pqxx>

namespace db
{

class DatabaseInitializer
{
public:
    DatabaseInitializer(const std::string& opts);

    void initializeFromFile(const std::string& file);
    void fillFromFile(const std::string& file);

private:
    pqxx::connection connection;
};
}
