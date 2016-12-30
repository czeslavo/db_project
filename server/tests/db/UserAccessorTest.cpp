#include "gtest/gtest.h"

#include "db/DatabaseAccessor.h"
#include "db/PostgreConfig.h"
#include "db/DatabaseInitializer.h"

using namespace ::testing;

class UserAccessorTest : public Test
{
public:
    void SetUp()
    {
        initializeDatabase();
    }

    void initializeDatabase()
    {
        db::DatabaseInitializer dbInitializer{config::db_opts};
        dbInitializer.init();
        dbInitializer.fill();
    }

protected:
    models::User newUser{"test@gmail.com", "Testy", "Test", "TestMe", "pass"};
    models::User existingUser{"czeslavo@gmail.com", "czeslavo", "Grzegorz", "Burzynski", "pass"};

    std::shared_ptr<pqxx::connection> 
        connection{std::make_shared<pqxx::connection>(config::db_opts)};

    db::UserAccessorImpl sut{connection};
};

TEST_F(UserAccessorTest, shouldCreateUser)
{
    sut.create(newUser);
}

TEST_F(UserAccessorTest, shouldDeleteUserByEmail)
{
    const std::string mail{"czeslavo@gmail.com"};
    sut.drop(mail);
}

TEST_F(UserAccessorTest, shouldUpdateUser)
{
    existingUser.password = "changed password";
    sut.update(existingUser); 
}

TEST_F(UserAccessorTest, shouldGetUserByEmail)
{
    const auto user = sut.getByEmail("czeslavo@gmail.com");
    EXPECT_EQ(user, existingUser);
}
