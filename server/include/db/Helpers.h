#pragma once

#include <pqxx/pqxx>

namespace helpers 
{

void logStatementResult(const pqxx::result& result);

} 
