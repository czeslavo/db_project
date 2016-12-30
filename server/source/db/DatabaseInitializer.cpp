#include <fstream>

#include "db/DatabaseInitializer.h"
#include "common/Logger.h"

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

void DatabaseInitializer::initializeFromFile(const std::string& file)
{
    LOG_INFO << "Initializing db from file " << file;

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
    
    LOG_DEBUG << "--- Database initialization ---\n" + inputString;
        
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

void DatabaseInitializer::fillFromFile(const std::string& file)
{

}

}
