#pragma once

#include <string>
#include <pqxx/pqxx>

namespace db
{

class DatabaseInitializer
{
public:
    DatabaseInitializer(const std::string& opts);

    void init();
    void fill();

private:
    void execute(const std::string& file);

    pqxx::connection connection;
};
}
