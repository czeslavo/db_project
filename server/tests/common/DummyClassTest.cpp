#include "gtest/gtest.h"

#include "common/DummyClass.h"

using namespace ::testing;

class DummyClassTest : public Test 
{
};

TEST_F(DummyClassTest, shouldSayHello)
{
    DummyClass sut;

    EXPECT_EQ(sut.sayHello(), "Hello, World!");
}
