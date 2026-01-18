#include <gtest/gtest.h>

#include <limits>
#include <vector>

#include <mcutils/misc/Check.h>

class TestCheck : public ::testing::Test
{
protected:

    TestCheck() {}
    virtual ~TestCheck() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestCheck, CanCheckIfIsInf)
{
    double zero = 0.0;

    EXPECT_FALSE(mc::isInf(0.0));
    EXPECT_FALSE(mc::isInf(DBL_MIN));
    EXPECT_FALSE(mc::isInf(DBL_MAX));
    EXPECT_FALSE(mc::isInf(std::numeric_limits<double>::min()));
    EXPECT_FALSE(mc::isInf(std::numeric_limits<double>::max()));

    EXPECT_TRUE(mc::isInf(std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(mc::isInf(1.0 / zero));
}

TEST_F(TestCheck, CanCheckIfIsNaN)
{
    EXPECT_FALSE(mc::isNaN(0.0));
    EXPECT_FALSE(mc::isNaN(DBL_MIN));
    EXPECT_FALSE(mc::isNaN(DBL_MAX));
    EXPECT_FALSE(mc::isNaN(std::numeric_limits<double>::min()));
    EXPECT_FALSE(mc::isNaN(std::numeric_limits<double>::max()));

    EXPECT_TRUE(mc::isNaN(std::numeric_limits<double>::quiet_NaN()));
}

TEST_F(TestCheck, CanCheckIfIsValid)
{
    double zero = 0.0;

    EXPECT_TRUE(mc::isValid(0.0));
    EXPECT_TRUE(mc::isValid(DBL_MIN));
    EXPECT_TRUE(mc::isValid(DBL_MAX));
    EXPECT_TRUE(mc::isValid(std::numeric_limits<double>::min()));
    EXPECT_TRUE(mc::isValid(std::numeric_limits<double>::max()));

    EXPECT_FALSE(mc::isValid(std::numeric_limits<double>::quiet_NaN()));
    EXPECT_FALSE(mc::isValid(std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(mc::isValid(1.0 / zero));
}

TEST_F(TestCheck, CanCheckIfIsValidArray)
{
    double zero = 0.0;

    double a1[] = { 0.0, 1.0, 2.0 };
    EXPECT_TRUE(mc::isValid(a1, 3));

    double a2[] = { 0.0, 1.0, DBL_MIN };
    EXPECT_TRUE(mc::isValid(a2, 3));

    double a3[] = { 0.0, 1.0, DBL_MAX };
    EXPECT_TRUE(mc::isValid(a3, 3));

    double a4[] = { 0.0, 1.0, std::numeric_limits<double>::min() };
    EXPECT_TRUE(mc::isValid(a4, 3));

    double a5[] = { 0.0, 1.0, std::numeric_limits<double>::max() };
    EXPECT_TRUE(mc::isValid(a5, 3));

    double a6[] = { 0.0, 1.0, std::numeric_limits<double>::quiet_NaN() };
    EXPECT_FALSE(mc::isValid(a6, 3));

    double a7[] = { 0.0, 1.0, std::numeric_limits<double>::infinity() };
    EXPECT_FALSE(mc::isValid(a7, 3));

    double a8[] = { 0.0, 1.0, 1.0 / zero };
    EXPECT_FALSE(mc::isValid(a8, 3));
}
