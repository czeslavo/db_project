#include "gtest/gtest.h"

#include "db/DatabaseAccessor.h"
#include "db/PostgreConfig.h"

using namespace ::testing;
using namespace std::literals;

class DatabaseAccessorTest : public Test
{
public:
    db::DatabaseAccessorImpl getSut(const std::string& opts)
    {
        return db::DatabaseAccessorImpl{opts};
    }
};

TEST_F(DatabaseAccessorTest, shouldConnectToDb)
{
    auto sut = getSut(config::db_opts); 
}

TEST_F(DatabaseAccessorTest, whenWrongOptsProvided_shouldThrow)
{
    EXPECT_THROW(getSut("wrong opts string"), std::runtime_error);
}

