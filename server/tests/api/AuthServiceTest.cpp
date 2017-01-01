#include "gtest/gtest.h"

#include "db/DatabaseAccessorMock.h"
#include "db/UserAccessorMock.h"

#include "api/AuthService.h"


using namespace ::testing;
using namespace db;

class AuthServiceTest : public Test
{
public:
    void expectGettingUserAccessor()
    {
        EXPECT_CALL(*db, getUserAccessorProxy())
            .WillOnce(Return(userAccess));
    }

    void expectSuccessfulLogin()
    {
        EXPECT_CALL(*userAccess, auth("Valid", "credentials"))
            .WillOnce(Return(true));
    }

    void expectUnsuccessfulLogin()
    {
        EXPECT_CALL(*userAccess, auth("Invalid", "credentials"))
            .WillOnce(Return(false));
    }

protected: 
    std::shared_ptr<DatabaseAccessorMock> db{
        std::make_shared<DatabaseAccessorMock>()};

    UserAccessorMock* userAccess{new UserAccessorMock()};

    api::AuthServiceImpl sut{db};
};

TEST_F(AuthServiceTest, shouldAllowLoggingIn)
{
    expectGettingUserAccessor();
    expectSuccessfulLogin();

    const auto token = sut.login("Valid", "credentials");
    EXPECT_EQ(token, "dummyapitoken");
}

TEST_F(AuthServiceTest, whenCredentialsAreInvalid_shouldThrow)
{
    expectGettingUserAccessor();
    expectUnsuccessfulLogin();

    EXPECT_THROW(
        sut.login("Invalid", "credentials"),
        api::AuthServiceImpl::AuthServiceException);
}

TEST_F(AuthServiceTest, shouldAllowLoggingOut)
{
    expectGettingUserAccessor();
    expectSuccessfulLogin();

    sut.login("Valid", "credentials");
    sut.logout("Valid"); 
}

TEST_F(AuthServiceTest, whenNotLoggedInAndWantToLogOut_shouldThrow)
{
    EXPECT_THROW(
        sut.logout("NotLoggedInGuy"),
        api::AuthServiceImpl::AuthServiceException);
}

