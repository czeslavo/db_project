#include "gtest/gtest.h"
#include "common/http_headers/AuthToken.h"

TEST(AuthToken, shouldParseProperly)
{
    auto token = AuthToken();
    token.parse("mail@gmail.com:tokentoken");
    EXPECT_EQ(token.getToken(), "tokentoken");
    EXPECT_EQ(token.getMail(), "mail@gmail.com");
}
