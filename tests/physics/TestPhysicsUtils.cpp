#include <gtest/gtest.h>

#include <mcutils/physics/PhysicsUtils.h>

#include <XcosBinFileReader.h>

class TestPhysicsUtils : public ::testing::Test
{
protected:

    static constexpr double TIME_STEP     { 0.1 };
    static constexpr double TIME_CONSTANT { 2.0 };

    TestPhysicsUtils() {}
    virtual ~TestPhysicsUtils() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestPhysicsUtils, CanComputeFirstOrderInertia)
{
    std::vector<double> vals;

    // expected values calculated with Scilab Xcos
    // tests/physics/xcos/test_inertia.xcos
    XcosBinFileReader::ReadData("../tests/physics/data/test_inertia.bin", &vals);

    EXPECT_GT(vals.size(), 0) << "No input data.";

    double t = 0.0;
    double y = 0.0;

    double u_prev = 0.0;
    double y_prev = 0.0;

    for ( unsigned int i = 0; i < vals.size(); ++i )
    {
        double u = ( t < 0.99 ) ? 0.0 : 1.0;

        int steps = 10;
        for ( int j = 0; j < steps; ++j )
        {
            double dt = TIME_STEP / static_cast<double>(steps);
            y = mc::physics::firstOrderInertia(u, y, dt, TIME_CONSTANT);

            if ( 0 )
            {
                double c1 = 1.0 / TIME_CONSTANT;
                double denom = 2.0 + dt * c1;
                double ca = dt * c1 / denom;
                double cb = (2.0 - dt * c1) / denom;

                y = (u + u_prev) * ca + y_prev * cb;

                u_prev = u;
                y_prev = y;
            }
        }

        EXPECT_NEAR(y, vals.at(i), 1.0e-3);

        t += TIME_STEP;
    }
}

TEST_F(TestPhysicsUtils, CanComputeInertiaTimeConst0)
{
    double y = 0.0;

    for ( unsigned int i = 0; i < 100; ++i )
    {
        double u = ( i < 10 ) ? 0.0 : 1.0;
        y = mc::physics::firstOrderInertia(u, y, 0.01, 0.0);
        EXPECT_NEAR(y, u, 1.0e-3);
    }
}
