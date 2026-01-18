#include <gtest/gtest.h>

#include <mcutils/math/MathUtils.h>

class TestMathUtils : public ::testing::Test
{
protected:
    TestMathUtils() {}
    virtual ~TestMathUtils() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMathUtils, CanCheckIfIsInside)
{
    EXPECT_TRUE(mc::math::isInside(0.0, 1.0, 0.5));
    EXPECT_FALSE(mc::math::isInside(0.0, 1.0, -0.1));
    EXPECT_FALSE(mc::math::isInside(0.0, 1.0, 1.1));
}

TEST_F(TestMathUtils, CanCheckIfIsOutside)
{
    EXPECT_FALSE(mc::math::isOutside(0.0, 1.0, 0.5));
    EXPECT_TRUE(mc::math::isOutside(0.0, 1.0, -0.1));
    EXPECT_TRUE(mc::math::isOutside(0.0, 1.0, 1.1));
}

TEST_F(TestMathUtils, CanCalculateNpow)
{
    EXPECT_DOUBLE_EQ(mc::math::npow<0>(2.0),  1.0);
    EXPECT_DOUBLE_EQ(mc::math::npow<1>(2.0),  2.0);
    EXPECT_DOUBLE_EQ(mc::math::npow<2>(2.0),  4.0);
    EXPECT_DOUBLE_EQ(mc::math::npow<3>(2.0),  8.0);
    EXPECT_DOUBLE_EQ(mc::math::npow<4>(2.0), 16.0);
}

TEST_F(TestMathUtils, CanSaturateValues)
{
    EXPECT_DOUBLE_EQ(mc::math::satur( 0.0, 1.0, -0.5 ), 0.0);
    EXPECT_DOUBLE_EQ(mc::math::satur( 0.0, 1.0,  0.5 ), 0.5);
    EXPECT_DOUBLE_EQ(mc::math::satur( 0.0, 1.0,  1.5 ), 1.0);
}

TEST_F(TestMathUtils, CanCalculateSignum)
{
    EXPECT_EQ(mc::math::sign( -10.0 ), -1);
    EXPECT_EQ(mc::math::sign(   0.0 ),  0);
    EXPECT_EQ(mc::math::sign(  10.0 ),  1);
}

TEST_F(TestMathUtils, CanCalculateSineWave)
{
    constexpr double tolerance = 1e-5;
    EXPECT_NEAR(mc::math::sineWave( -1.0 ) , sin(-M_PI)   , tolerance);
    EXPECT_NEAR(mc::math::sineWave( -0.5 ) , sin(-M_PI_2) , tolerance);
    EXPECT_NEAR(mc::math::sineWave(  0.0 ) , sin(0.0)     , tolerance);
    EXPECT_NEAR(mc::math::sineWave(  0.5 ) , sin(M_PI_2)  , tolerance);
    EXPECT_NEAR(mc::math::sineWave(  1.0 ) , sin(M_PI)    , tolerance);
}

TEST_F(TestMathUtils, CanCalculateSmoothstep)
{
    EXPECT_DOUBLE_EQ(mc::math::smoothstep(-1.0, 1.0, -1.5), 0.0);
    EXPECT_DOUBLE_EQ(mc::math::smoothstep(-1.0, 1.0, -1.0), 0.0);
    EXPECT_DOUBLE_EQ(mc::math::smoothstep(-1.0, 1.0,  0.0), 0.5);
    EXPECT_DOUBLE_EQ(mc::math::smoothstep(-1.0, 1.0,  1.0), 1.0);
    EXPECT_DOUBLE_EQ(mc::math::smoothstep(-1.0, 1.0,  1.5), 1.0);
}