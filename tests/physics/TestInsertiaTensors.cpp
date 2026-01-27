#include <gtest/gtest.h>

#include <mcutils/physics/InertiaTensors.h>

class TestInsertiaTensors : public ::testing::Test
{
protected:

    TestInsertiaTensors() {}
    virtual ~TestInsertiaTensors() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestInsertiaTensors, CanCalculateInertiaTensorOfSolidSphere)
{
    // expected values calculated with Python trimesh
    // tests/physics/python/test_inertia_tensors.py
    // [[ 1.63296006e+00 -1.46409247e-07 -1.49779016e-10]
    // [-1.46409247e-07  1.63296001e+00 -2.26705792e-10]
    // [-1.49779016e-10 -2.26705792e-10  1.62773793e+00]]

    constexpr units::mass::kilogram_t mass = 1.0_kg;
    constexpr units::length::meter_t radius = 1.0_m;

    mc::Matrix3x3_kg_m_sq i = mc::physics::calculateInrtiaTensorOfSolidSphere(mass, radius);

    constexpr double tolerance = 1.0e-6;

    EXPECT_NEAR(i.xx().to<double>(), 1.63296006, tolerance);
    EXPECT_NEAR(i.yy().to<double>(), 1.63296001, tolerance);
    EXPECT_NEAR(i.zz().to<double>(), 1.62773793, tolerance);
    EXPECT_NEAR(i.xy().to<double>(), -1.46409247e-07, tolerance);
    EXPECT_NEAR(i.xz().to<double>(), -1.49779016e-10, tolerance);
    EXPECT_NEAR(i.yz().to<double>(), -2.26705792e-10, tolerance);
    EXPECT_NEAR(i.yx().to<double>(), -1.46409247e-07, tolerance);
    EXPECT_NEAR(i.zx().to<double>(), -1.49779016e-10, tolerance);
    EXPECT_NEAR(i.zy().to<double>(), -2.26705792e-10, tolerance);

}
