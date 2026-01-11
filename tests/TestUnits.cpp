#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/units.h>

using namespace units::literals;

class TestUnits : public ::testing::Test
{
protected:
    TestUnits() {}
    virtual ~TestUnits() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestUnits, CanInstantiateInvertedUnits)
{
    units::inverted::per_meter_t inv_m1 = 2.0_per_m;
    EXPECT_DOUBLE_EQ(inv_m1(), 2.0);

    units::inverted::per_centimeter_t inv_cm1 = 5.0_per_cm;
    EXPECT_DOUBLE_EQ(inv_cm1(), 5.0);

    units::inverted::per_foot_t inv_ft1 = 3.0_per_ft;
    EXPECT_DOUBLE_EQ(inv_ft1(), 3.0);

    units::inverted::per_inch_t inv_in1 = 10.0_per_in;
    EXPECT_DOUBLE_EQ(inv_in1(), 10.0);

    units::inverted::per_second_t inv_s1 = 4.0_per_s;
    EXPECT_DOUBLE_EQ(inv_s1(), 4.0);

    units::inverted::per_second_squared_t inv_s_sq1 = 6.0_per_s_sq;
    EXPECT_DOUBLE_EQ(inv_s_sq1(), 6.0);

    units::inverted::per_radian_t inv_rad1 = 1.5_per_rad;
    EXPECT_DOUBLE_EQ(inv_rad1(), 1.5);

    units::inverted::per_degree_t inv_deg1 = 0.5_per_deg;
    EXPECT_DOUBLE_EQ(inv_deg1(), 0.5);
}

TEST_F(TestUnits, CanInstantiateInertiaUnits)
{
    units::moment_of_inertia::kilograms_meters_squared_t I1 = 10.0_kg_m_sq;
    EXPECT_DOUBLE_EQ(I1(), 10.0);

    units::moment_of_inertia::slugs_feet_squared_t I2 = 20.0_slugs_ft_sq;
    EXPECT_DOUBLE_EQ(I2(), 20.0);
}

TEST_F(TestUnits, CanInstantiateFirstMomentOfMassUnits)
{
    units::first_moment_of_mass::kilogram_meter_t fm1 = 15.0_kg_m;
    EXPECT_DOUBLE_EQ(fm1(), 15.0);

    units::first_moment_of_mass::slug_feet_t fm2 = 25.0_slug_ft;
    EXPECT_DOUBLE_EQ(fm2(), 25.0);
}

TEST_F(TestUnits, CanInstantiateVelocityUnits)
{
    units::velocity::feet_per_minute_t v1 = 30.0_fpm;
    EXPECT_DOUBLE_EQ(v1(), 30.0);
}

TEST_F(TestUnits, CanInstantiateAngularAccelerationUnits)
{
    units::angular_acceleration::radians_per_second_squared_t aa1 = 9.81_rad_per_s_sq;
    EXPECT_DOUBLE_EQ(aa1(), 9.81);

    units::angular_acceleration::degrees_per_second_squared_t aa2 = 45.0_deg_per_s_sq;
    EXPECT_DOUBLE_EQ(aa2(), 45.0);
}

TEST_F(TestUnits, CanInstantiatePressureUnits)
{
    units::pressure::pounds_per_square_inch_t p1 = 100.0_psi;
    EXPECT_DOUBLE_EQ(p1(), 100.0);
}

TEST_F(TestUnits, CanInstantiateStiffnessUnits)
{
    units::stiffness::newtons_per_meter_t k1 = 500.0_N_per_m;
    EXPECT_DOUBLE_EQ(k1(), 500.0);

    units::stiffness::pounds_per_foot_t k2 = 600.0_lbf_per_ft;
    EXPECT_DOUBLE_EQ(k2(), 600.0);
}

TEST_F(TestUnits, CanInstantiateViscousDampingUnits)
{
    units::viscous_damping::newtons_per_meters_per_second_t c1 = 50.0_N_per_mps;
    EXPECT_DOUBLE_EQ(c1(), 50.0);

    units::viscous_damping::pounds_per_feet_per_second_t c2 = 75.0_lbf_per_fps;
    EXPECT_DOUBLE_EQ(c2(), 75.0);
}

TEST_F(TestUnits, CanInstantiateAerodynamicDerivativeUnits)
{
    // TODO
}

TEST_F(TestUnits, CanInstantiateTemperatureGradientUnits)
{
    units::temperature_gradient::kelvins_per_meter_t tg1 = 0.02_K_per_m;
    EXPECT_DOUBLE_EQ(tg1(), 0.02);

    units::temperature_gradient::kelvins_per_kilometer_t tg2 = 15.0_K_per_km;
    EXPECT_DOUBLE_EQ(tg2(), 15.0);
}

TEST_F(TestUnits, CanInstantiateMolarMassUnits)
{
    units::molar_mass::kilograms_per_mole_t mm1 = 0.018_kg_per_mol;
    EXPECT_DOUBLE_EQ(mm1(), 0.018);
}

TEST_F(TestUnits, CanInstantiateDynamicViscosityUnits)
{
    units::dynamic_viscosity::pascal_second_t dv1 = 0.89_Pa_s;
    EXPECT_DOUBLE_EQ(dv1(), 0.89);
}

TEST_F(TestUnits, CanInstantiateKinematicViscosityUnits)
{
    units::kinematic_viscosity::meters_squared_per_second_t kv1 = 1.5_m_sq_per_s;
    EXPECT_DOUBLE_EQ(kv1(), 1.5);
}

TEST_F(TestUnits, CanInstantiateGasConstantUnits)
{
    units::gas_constant::joules_per_kelvin_per_mole_t R1 = 8.314_J_per_K_per_mol;
    EXPECT_DOUBLE_EQ(R1(), 8.314);
}

TEST_F(TestUnits, CanCheckForAngularDimension)
{
    using namespace units::traits;

    constexpr bool has_angle_1 = has_angle_dimension_t<units::angle::radian_t>::value;
    EXPECT_TRUE(has_angle_1);

    constexpr bool has_angle_2 = has_angle_dimension_t<units::angle::degree_t>::value;
    EXPECT_TRUE(has_angle_2);

    constexpr bool has_angle_3 = has_angle_dimension_t<units::length::meter_t>::value;
    EXPECT_FALSE(has_angle_3);

    constexpr bool has_angle_4 = has_angle_dimension_t<units::inverted::per_radian_t>::value;
    EXPECT_TRUE(has_angle_4);

    constexpr bool has_angle_5 = has_angle_dimension_t<units::angular_velocity::radians_per_second_t>::value;
    EXPECT_TRUE(has_angle_5);

    constexpr bool has_angle_6 = has_angle_dimension_t<units::velocity::meters_per_second_t>::value;
    EXPECT_FALSE(has_angle_6);

    constexpr bool has_angle_7 = 
        has_angle_dimension_t<units::angular_acceleration::radians_per_second_squared_t>::value;
    EXPECT_TRUE(has_angle_7);

    constexpr bool has_angle_8 = has_angle_dimension_t<units::acceleration::meters_per_second_squared_t>::value;
    EXPECT_FALSE(has_angle_8);
}

TEST_F(TestUnits, CanStripAngularDimension)
{
    units::angle::radian_t angle_rad = 3.14159_rad;
    double stripped_angle = units::detail::strip_angle_dimension<units::angle::radian_t>::strip(angle_rad);
    EXPECT_DOUBLE_EQ(stripped_angle, 3.14159);

    units::angle::degree_t angle_deg = 180.0_deg;
    double stripped_deg = units::detail::strip_angle_dimension<units::angle::degree_t>::strip(angle_deg);
    EXPECT_DOUBLE_EQ(stripped_deg, M_PI);

    units::angular_velocity::radians_per_second_t ang_vel = 6.28318_rad_per_s;
    units::inverted::per_second_t stripped_ang_vel = 
        units::detail::strip_angle_dimension<units::angular_velocity::radians_per_second_t>::strip(ang_vel);
    EXPECT_DOUBLE_EQ(stripped_ang_vel(), 6.28318);
}

TEST_F(TestUnits, CanCheckIfAngleStrippingIsNeeded)
{
    constexpr bool need_strip_1 = units::traits::need_angle_stripping<
        units::angular_velocity::radians_per_second_t,
        units::velocity::meters_per_second_t
    >::value;
    EXPECT_TRUE(need_strip_1);

    constexpr bool need_strip_2 = units::traits::need_angle_stripping<
        units::velocity::meters_per_second_t,
        units::angular_velocity::radians_per_second_t
    >::value;
    EXPECT_TRUE(need_strip_2);

    constexpr bool need_strip_3 = units::traits::need_angle_stripping<
        units::velocity::meters_per_second_t,
        units::length::meter_t
    >::value;
    EXPECT_FALSE(need_strip_3);

    constexpr bool need_strip_4 = units::traits::need_angle_stripping<
        units::angular_acceleration::radians_per_second_squared_t,
        units::acceleration::meters_per_second_squared_t
    >::value;
    EXPECT_TRUE(need_strip_4);

    constexpr bool need_strip_5 = units::traits::need_angle_stripping<
        units::acceleration::meters_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t
    >::value;
    EXPECT_TRUE(need_strip_5);
}