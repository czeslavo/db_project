#include "db/DatabaseInitializer.h"
#include "db/PostgreConfig.h"

int main()
{
    db::DatabaseInitializer initializer{config::db_opts};
    initializer.init();
    initializer.fill();
}
