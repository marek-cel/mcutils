#include <gtest/gtest.h>

#include <mcutils/math/GaussJordan.h>

class TestGaussJordan : public ::testing::Test
{
protected:
    TestGaussJordan() {}
    virtual ~TestGaussJordan() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestGaussJordan, CanSolve)
{
    // x = 1
    // y = 1
    // z = 2
    //  x +  y + z = 4
    // 2x +  y + z = 5
    // 2x + 2y + z = 6

    mc::MatrixNxN<double, 3> m;
    m(0,0) = 1.0;
    m(0,1) = 1.0;
    m(0,2) = 1.0;

    m(1,0) = 2.0;
    m(1,1) = 1.0;
    m(1,2) = 1.0;

    m(2,0) = 2.0;
    m(2,1) = 2.0;
    m(2,2) = 1.0;

    mc::VectorN<double, 3> rhs;
    rhs(0) = 4.0;
    rhs(1) = 5.0;
    rhs(2) = 6.0;

    mc::VectorN<double, 3> x;
    mc::math::solveGaussJordan(m, rhs, &x);

    EXPECT_NEAR(x(0), 1.0, 1.0e-9);
    EXPECT_NEAR(x(1), 1.0, 1.0e-9);
    EXPECT_NEAR(x(2), 2.0, 1.0e-9);
}

TEST_F(TestGaussJordan, CanSolveNotInOrder)
{
    // x = 1
    // y = 1
    // z = 2
    // 2x + 2y + z = 6
    //  x +  y + z = 4
    // 2x +  y + z = 5

    mc::MatrixNxN<double, 3> m;
    m(0,0) = 2.0;
    m(0,1) = 2.0;
    m(0,2) = 1.0;

    m(1,0) = 2.0;
    m(1,1) = 1.0;
    m(1,2) = 1.0;

    m(2,0) = 1.0;
    m(2,1) = 1.0;
    m(2,2) = 1.0;

    mc::VectorN<double, 3> rhs;
    rhs(0) = 6.0;
    rhs(1) = 5.0;
    rhs(2) = 4.0;

    mc::VectorN<double, 3> x;
    mc::math::solveGaussJordan(m, rhs, &x);

    EXPECT_NEAR(x(0), 1.0, 1.0e-9);
    EXPECT_NEAR(x(1), 1.0, 1.0e-9);
    EXPECT_NEAR(x(2), 2.0, 1.0e-9);
}

TEST_F(TestGaussJordan, CanSolveWithZerosAtDiagonal)
{
    // x = 1
    // y = 1
    // z = 2
    //      y + z = 3
    //  x     + z = 3
    //  x + y     = 2

    mc::MatrixNxN<double, 3> m;
    m(0,0) = 0.0;
    m(0,1) = 1.0;
    m(0,2) = 1.0;

    m(1,0) = 1.0;
    m(1,1) = 0.0;
    m(1,2) = 1.0;

    m(2,0) = 1.0;
    m(2,1) = 1.0;
    m(2,2) = 0.0;

    mc::VectorN<double, 3> rhs;
    rhs(0) = 3.0;
    rhs(1) = 3.0;
    rhs(2) = 2.0;

    mc::VectorN<double, 3> x;
    mc::math::solveGaussJordan(m, rhs, &x);

    EXPECT_NEAR(x(0), 1.0, 1.0e-9);
    EXPECT_NEAR(x(1), 1.0, 1.0e-9);
    EXPECT_NEAR(x(2), 2.0, 1.0e-9);
}
