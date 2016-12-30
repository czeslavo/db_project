#include "db/Helpers.h"
#include "common/Logger.h"

namespace helpers
{

void logStatementResult(const pqxx::result& result)
{
    LOG_DEBUG << "Executed query: " << result.query() << ", affected rows: " 
              << result.affected_rows(); 
}
}
