#include "gtest/gtest.h"

#include "db/DatabaseAccessor.h"
#include "db/PostgreConfig.h"
#include "db/DatabaseInitializer.h"

using namespace ::testing;

class FlatAccessorTest : public Test
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
    models::User existingUser{"czeslavo@gmail.com", "czeslavo",
        "Grzegorz", "Burzynski", "pass"};
    models::User existingUser2{"andrzej@gmail.com", "Andrew",
        "Andrzej", "Andrzejowski", "pass3"};

    models::Flat newFlat{0, "Szkolna 52", "czeslavo@gmail.com"};
    models::Flat existingFlat{1, "Symfoniczna 1/13", "czeslavo@gmail.com"};

    std::shared_ptr<pqxx::connection>
        connection{std::make_shared<pqxx::connection>(config::db_opts)};

    db::FlatAccessorImpl sut{connection};
};

TEST_F(FlatAccessorTest, shouldCreateFlat)
{
    sut.create(newFlat);
}

TEST_F(FlatAccessorTest, shouldDeleteFlat)
{
    sut.drop(existingFlat.id);
}

TEST_F(FlatAccessorTest, shouldUpdateFlat)
{
    existingFlat.name = "Changed name";
    sut.update(existingFlat);
}

TEST_F(FlatAccessorTest, shouldGetFlatById)
{
    const auto flat = sut.get(1);
    EXPECT_EQ(flat, existingFlat);
}

TEST_F(FlatAccessorTest, whenUserIsAlreadyInFlat_shouldThrowUniqueViolation)
{
    EXPECT_THROW(
        sut.addUser(existingFlat.id, existingUser.mail),
        pqxx::unique_violation);
}

TEST_F(FlatAccessorTest, shouldAddUserToFlat)
{
    sut.addUser(existingFlat.id, existingUser2.mail);
}

TEST_F(FlatAccessorTest, shouldRemoveUserFromFlat)
{
    sut.removeUser(existingFlat.id, existingUser.mail);
}

TEST_F(FlatAccessorTest, shouldGetFlatUsers)
{
    const auto users = sut.getUsers(1);
    EXPECT_EQ(users.size(), 4);
}

TEST_F(FlatAccessorTest, shouldCheckIfUserIsFlatUser)
{
    EXPECT_TRUE(sut.isFlatUser(existingFlat.id, existingUser.mail));
}

TEST_F(FlatAccessorTest, whenUserIsNotFlatUser_shouldTellThatIsNot)
{
    EXPECT_FALSE(sut.isFlatUser(existingFlat.id, newUser.mail));
}
