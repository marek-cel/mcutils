#include <gtest/gtest.h>

#include <mcutils/math/RungeKutta4.h>

// #include <DiffEquationSolver.h>

class TestRungeKutta4 : public ::testing::Test
{
protected:
    TestRungeKutta4() {}
    virtual ~TestRungeKutta4() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestRungeKutta4, CanInstantiate)
{
    mc::RungeKutta4<double> rk;
    EXPECT_FALSE(static_cast<bool>(rk.fun()));
}

// TEST_F(TestRungeKutta4, CanSolve)
// {
//     mc::RungeKutta4<mc::Vector3d> rk1;
//     DiffEquationSolver<mc::RungeKutta4<mc::Vector3d>> des1(1.0, 1.0, 3.0, &rk1);
//     EXPECT_TRUE(des1.Solve(0.0, 1.0));

//     mc::RungeKutta4<mc::Vector3d> rk2;
//     DiffEquationSolver<mc::RungeKutta4<mc::Vector3d>> des2(1.0, 1.0, 3.0, &rk2);
//     EXPECT_TRUE(des2.Solve(1.0, 0.0));

//     mc::RungeKutta4<mc::Vector3d> rk3;
//     DiffEquationSolver<mc::RungeKutta4<mc::Vector3d>> des3(1.0, 1.0, 3.0, &rk3);
//     EXPECT_TRUE(des3.Solve(1.0, 1.0));

//     mc::RungeKutta4<mc::Vector3d> rk4;
//     DiffEquationSolver<mc::RungeKutta4<mc::Vector3d>> des4(1.0, 1.0, 1.0, &rk4);
//     EXPECT_TRUE(des4.Solve(0.0, 1.0));

//     mc::RungeKutta4<mc::Vector3d> rk5;
//     DiffEquationSolver<mc::RungeKutta4<mc::Vector3d>> des5(1.0, 1.0, 1.0, &rk5);
//     EXPECT_TRUE(des5.Solve(1.0, 0.0));

//     mc::RungeKutta4<mc::Vector3d> rk6;
//     DiffEquationSolver<mc::RungeKutta4<mc::Vector3d>> des6(1.0, 1.0, 1.0, &rk6);
//     EXPECT_TRUE(des6.Solve(1.0, 1.0));
// }

TEST_F(TestRungeKutta4, CanSetDerivFun)
{
    mc::RungeKutta4<double> rk;
    EXPECT_NO_THROW(rk.setFun([](const double&)
    {
        return 1.0;
    } ));
    EXPECT_TRUE(static_cast<bool>(rk.fun()));
}
