#include "gtest/gtest.h"

#include "common/DummyClass.h"

using namespace ::testing;

class DummyClassTest : public Test 
{
protected:
    DummyClass sut;
};

TEST_F(DummyClassTest, shouldSayHello)
{
    EXPECT_EQ(sut.sayHello(), "Hello, World!");
}

TEST_F(DummyClassTest, shouldAddNumbers)
{
    EXPECT_EQ(sut.addNumbers(2, 5), 7);
}

TEST_F(DummyClassTest, shouldAddNegativeNumbers)
{
    EXPECT_EQ(sut.addNumbers(-2, -5), -7);
}
