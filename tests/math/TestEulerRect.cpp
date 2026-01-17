#include <gtest/gtest.h>

#include <functional>

#include <mcutils/math/EulerRect.h>

#include <DiffEquationSolver.h>

class TestEulerRect : public ::testing::Test
{
protected:
    TestEulerRect() {}
    virtual ~TestEulerRect() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestEulerRect, CanInstantiate)
{
    mc::EulerRect<double,double> er;
    EXPECT_FALSE(static_cast<bool>(er.fun()));
}

TEST_F(TestEulerRect, CanSolve)
{
    mc::EulerRect<mc::Vector3d, double> er1;
    DiffEquationSolver<mc::EulerRect<mc::Vector3d, double>> des1(1.0, 1.0, 3.0, &er1);
    EXPECT_TRUE(des1.Solve(0.0, 1.0));

    mc::EulerRect<mc::Vector3d, double> er2;
    DiffEquationSolver<mc::EulerRect<mc::Vector3d, double>> des2(1.0, 1.0, 3.0, &er2);
    EXPECT_TRUE(des2.Solve(1.0, 0.0));

    mc::EulerRect<mc::Vector3d, double> er3;
    DiffEquationSolver<mc::EulerRect<mc::Vector3d, double>> des3(1.0, 1.0, 3.0, &er3);
    EXPECT_TRUE(des3.Solve(1.0, 1.0));

    mc::EulerRect<mc::Vector3d, double> er4;
    DiffEquationSolver<mc::EulerRect<mc::Vector3d, double>> des4(1.0, 1.0, 1.0, &er4);
    EXPECT_TRUE(des4.Solve(0.0, 1.0));

    mc::EulerRect<mc::Vector3d, double> er5;
    DiffEquationSolver<mc::EulerRect<mc::Vector3d, double>> des5(1.0, 1.0, 1.0, &er5);
    EXPECT_TRUE(des5.Solve(1.0, 0.0));

    mc::EulerRect<mc::Vector3d, double> er6;
    DiffEquationSolver<mc::EulerRect<mc::Vector3d, double>> des6(1.0, 1.0, 1.0, &er6);
    EXPECT_TRUE(des6.Solve(1.0, 1.0));
}

TEST_F(TestEulerRect, CanSetDerivFun)
{
    mc::EulerRect<double,double> er;
    EXPECT_NO_THROW(er.setFun([](const double&)
    {
        return 1.0;
    } ));
    EXPECT_TRUE(static_cast<bool>(er.fun()));
}
