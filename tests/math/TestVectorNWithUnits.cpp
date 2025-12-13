#include <gtest/gtest.h>

#include <mcutils/math/Vector.h>

#define SIZE 3
#define TOLERANCE 1.0e-12

using namespace units::literals;

class TestVectorNWithUnits : public ::testing::Test
{
protected:
    TestVectorNWithUnits() {}
    virtual ~TestVectorNWithUnits() {}
    void SetUp() override {}
    void TearDown() override {}
};

template <typename T>
void VectorN_CanInstantiate()
{
    mc::VectorN<T,SIZE> v1;

    EXPECT_NEAR(v1(0)(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1(1)(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1(2)(), 0.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanInstantiate)
{
    VectorN_CanInstantiate<units::length::meter_t>();
    VectorN_CanInstantiate<units::velocity::meters_per_second_t>();
    VectorN_CanInstantiate<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanInstantiate<units::angular_velocity::radians_per_second_t>();
    VectorN_CanInstantiate<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanInstantiate<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanInstantiate<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanInstantiate<units::force::newton_t>();
    VectorN_CanInstantiate<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanValidate()
{
    std::vector<T> x { T{1}, T{2}, T{3} };
    mc::VectorN<T,SIZE> v;
    v.setFromStdVector(x);
    EXPECT_TRUE(v.isValid());
    v(0) = T{std::numeric_limits<double>::quiet_NaN()};
    EXPECT_FALSE(v.isValid());
}

TEST_F(TestVectorNWithUnits, CanValidate)
{
    VectorN_CanValidate<units::length::meter_t>();
    VectorN_CanValidate<units::velocity::meters_per_second_t>();
    VectorN_CanValidate<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanValidate<units::angular_velocity::radians_per_second_t>();
    VectorN_CanValidate<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanValidate<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanValidate<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanValidate<units::force::newton_t>();
    VectorN_CanValidate<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanGetLengthSquared()
{
    mc::VectorN<T,SIZE> v;

    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    // 1^2 + 2^2 + 3^2 = 1 + 4 + 9 = 14
    EXPECT_DOUBLE_EQ(v.getLength2()(), 14.0);
}

TEST_F(TestVectorNWithUnits, CanGetLengthSquared)
{
    VectorN_CanGetLengthSquared<units::length::meter_t>();
    VectorN_CanGetLengthSquared<units::velocity::meters_per_second_t>();
    VectorN_CanGetLengthSquared<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanGetLengthSquared<units::angular_velocity::radians_per_second_t>();
    VectorN_CanGetLengthSquared<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanGetLengthSquared<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanGetLengthSquared<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanGetLengthSquared<units::force::newton_t>();
    VectorN_CanGetLengthSquared<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanGetLength()
{
    mc::VectorN<T,SIZE> v;

    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    // expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_vector.m
    // sqrt( 1^2 + 2^2 + 3^2 ) = sqrt( 1 + 4 + 9 ) = sqrt( 14 )
    EXPECT_NEAR(v.getLength()(), 3.741657, 1.0e-5);
}

TEST_F(TestVectorNWithUnits, CanGetLength)
{
    VectorN_CanGetLength<units::length::meter_t>();
    VectorN_CanGetLength<units::velocity::meters_per_second_t>();
    VectorN_CanGetLength<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanGetLength<units::angular_velocity::radians_per_second_t>();
    VectorN_CanGetLength<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanGetLength<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanGetLength<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanGetLength<units::force::newton_t>();
    VectorN_CanGetLength<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanGetNormalized()
{
    mc::VectorN<T,SIZE> v1;
    v1(0) = T{1};
    v1(1) = T{2};
    v1(2) = T{3};

    // expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_vector3.m

    mc::VectorN<double,SIZE> v1_n = v1.getNormalized();

    EXPECT_NEAR(v1_n(0), 0.267261, 1.0e-5);
    EXPECT_NEAR(v1_n(1), 0.534522, 1.0e-5);
    EXPECT_NEAR(v1_n(2), 0.801784, 1.0e-5);

    EXPECT_NEAR(v1_n.getLength(), 1.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanGetNormalized)
{
    VectorN_CanGetNormalized<units::length::meter_t>();
    VectorN_CanGetNormalized<units::velocity::meters_per_second_t>();
    VectorN_CanGetNormalized<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanGetNormalized<units::angular_velocity::radians_per_second_t>();
    VectorN_CanGetNormalized<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanGetNormalized<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanGetNormalized<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanGetNormalized<units::force::newton_t>();
    VectorN_CanGetNormalized<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanGetStdVector()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    std::vector<T> result;
    result = v.getStdVector();

    EXPECT_NEAR(result[0](), 1.0, TOLERANCE);
    EXPECT_NEAR(result[1](), 2.0, TOLERANCE);
    EXPECT_NEAR(result[2](), 3.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanGetStdVector)
{
    VectorN_CanGetStdVector<units::length::meter_t>();
    VectorN_CanGetStdVector<units::velocity::meters_per_second_t>();
    VectorN_CanGetStdVector<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanGetStdVector<units::angular_velocity::radians_per_second_t>();
    VectorN_CanGetStdVector<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanGetStdVector<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanGetStdVector<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanGetStdVector<units::force::newton_t>();
    VectorN_CanGetStdVector<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanSetFromStdVector()
{
    std::vector<T> x { T{1}, T{2}, T{3} };
    mc::VectorN<T,SIZE> v;
    v.setFromStdVector(x);

    EXPECT_NEAR(v(0)(), 1.0, TOLERANCE);
    EXPECT_NEAR(v(1)(), 2.0, TOLERANCE);
    EXPECT_NEAR(v(2)(), 3.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanSetFromStdVector)
{
    VectorN_CanSetFromStdVector<units::length::meter_t>();
    VectorN_CanSetFromStdVector<units::velocity::meters_per_second_t>();
    VectorN_CanSetFromStdVector<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanSetFromStdVector<units::angular_velocity::radians_per_second_t>();
    VectorN_CanSetFromStdVector<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanSetFromStdVector<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanSetFromStdVector<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanSetFromStdVector<units::force::newton_t>();
    VectorN_CanSetFromStdVector<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanSetFromString()
{
    char str[] = { " 1.0  2.0  3.0 " };
    mc::VectorN<T,SIZE> v;
    v.setFromString(str);

    EXPECT_DOUBLE_EQ(v(0)(), 1.0);
    EXPECT_DOUBLE_EQ(v(1)(), 2.0);
    EXPECT_DOUBLE_EQ(v(2)(), 3.0);
}

TEST_F(TestVectorNWithUnits, CanSetFromString)
{
    VectorN_CanSetFromString<units::length::meter_t>();
    VectorN_CanSetFromString<units::velocity::meters_per_second_t>();
    VectorN_CanSetFromString<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanSetFromString<units::angular_velocity::radians_per_second_t>();
    VectorN_CanSetFromString<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanSetFromString<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanSetFromString<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanSetFromString<units::force::newton_t>();
    VectorN_CanSetFromString<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanSetFromInvalidString()
{
    char str[] = { "lorem ipsum" };
    mc::VectorN<T,SIZE> v;
    v.setFromString(str);
    EXPECT_FALSE(v.isValid());
}

TEST_F(TestVectorNWithUnits, CanSetFromInvalidString)
{
    VectorN_CanSetFromInvalidString<units::length::meter_t>();
    VectorN_CanSetFromInvalidString<units::velocity::meters_per_second_t>();
    VectorN_CanSetFromInvalidString<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanSetFromInvalidString<units::angular_velocity::radians_per_second_t>();
    VectorN_CanSetFromInvalidString<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanSetFromInvalidString<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanSetFromInvalidString<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanSetFromInvalidString<units::force::newton_t>();
    VectorN_CanSetFromInvalidString<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanSwapRows()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    v.swapRows(0, 1);
    EXPECT_DOUBLE_EQ(v(0)(), 2.0);
    EXPECT_DOUBLE_EQ(v(1)(), 1.0);
    EXPECT_DOUBLE_EQ(v(2)(), 3.0);
}

TEST_F(TestVectorNWithUnits, CanSwapRows)
{
    VectorN_CanSwapRows<units::length::meter_t>();
    VectorN_CanSwapRows<units::velocity::meters_per_second_t>();
    VectorN_CanSwapRows<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanSwapRows<units::angular_velocity::radians_per_second_t>();
    VectorN_CanSwapRows<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanSwapRows<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanSwapRows<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanSwapRows<units::force::newton_t>();
    VectorN_CanSwapRows<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanConvertToString()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    std::stringstream ss;
    ss << T{1} << "\t" << T{2} << "\t" << T{3};

    EXPECT_STREQ(v.toString().c_str(), ss.str().c_str());
}

TEST_F(TestVectorNWithUnits, CanConvertToString)
{
    VectorN_CanConvertToString<units::length::meter_t>();
    VectorN_CanConvertToString<units::velocity::meters_per_second_t>();
    VectorN_CanConvertToString<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanConvertToString<units::angular_velocity::radians_per_second_t>();
    VectorN_CanConvertToString<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanConvertToString<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanConvertToString<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanConvertToString<units::force::newton_t>();
    VectorN_CanConvertToString<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanZeroize()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    v.zeroize();
    EXPECT_DOUBLE_EQ(v(0)(), 0.0);
    EXPECT_DOUBLE_EQ(v(1)(), 0.0);
    EXPECT_DOUBLE_EQ(v(2)(), 0.0);
}

TEST_F(TestVectorNWithUnits, CanZeroize)
{
    VectorN_CanZeroize<units::length::meter_t>();
    VectorN_CanZeroize<units::velocity::meters_per_second_t>();
    VectorN_CanZeroize<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanZeroize<units::angular_velocity::radians_per_second_t>();
    VectorN_CanZeroize<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanZeroize<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanZeroize<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanZeroize<units::force::newton_t>();
    VectorN_CanZeroize<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanGetDimensionless()
{
    mc::VectorN<T,SIZE> v1;
    v1(0) = T{1};
    v1(1) = T{2};
    v1(2) = T{3};

    mc::VectorN<double,SIZE> v2;
    v2 = v1.getDimensionless();
    EXPECT_NEAR(v2(0), 1.0, TOLERANCE);
    EXPECT_NEAR(v2(1), 2.0, TOLERANCE);
    EXPECT_NEAR(v2(2), 3.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanGetDimensionless)
{
    VectorN_CanGetDimensionless<units::length::meter_t>();
    VectorN_CanGetDimensionless<units::velocity::meters_per_second_t>();
    VectorN_CanGetDimensionless<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanGetDimensionless<units::angular_velocity::radians_per_second_t>();
    VectorN_CanGetDimensionless<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanGetDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanGetDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanGetDimensionless<units::force::newton_t>();
    VectorN_CanGetDimensionless<units::torque::newton_meter_t>();
}

template <typename T1, typename T2>
void VectorN_CanCastToOtherVectorType()
{
    mc::VectorN<T1,SIZE> v1;
    v1(0) = T2{1}; // sic!
    v1(1) = T2{2}; // sic!
    v1(2) = T2{3}; // sic!
    mc::VectorN<T2,SIZE> v2;
    v2 = v1;
    EXPECT_NEAR(v2(0)(), 1.0, TOLERANCE);
    EXPECT_NEAR(v2(1)(), 2.0, TOLERANCE);
    EXPECT_NEAR(v2(2)(), 3.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanCastToOtherVectorType)
{
    VectorN_CanCastToOtherVectorType<
        units::length::meter_t,
        units::length::foot_t>();
    VectorN_CanCastToOtherVectorType<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t>();
    VectorN_CanCastToOtherVectorType<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t>();
    VectorN_CanCastToOtherVectorType<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t>();
    VectorN_CanCastToOtherVectorType<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t>();
    VectorN_CanCastToOtherVectorType<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanCastToOtherVectorType<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanCastToOtherVectorType<
        units::force::newton_t,
        units::force::pound_t>();
    VectorN_CanCastToOtherVectorType<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t>();
}

template <typename T>
void VectorN_CanAdd()
{
    mc::VectorN<T,SIZE> v1;
    mc::VectorN<T,SIZE> v2;

    v1(0) = T{1};
    v1(1) = T{2};
    v1(2) = T{3};

    v2(0) = T{4};
    v2(1) = T{5};
    v2(2) = T{6};

    mc::VectorN<T,SIZE> v12 = v1 + v2;

    EXPECT_NEAR(v12(0)(), 5.0, TOLERANCE);
    EXPECT_NEAR(v12(1)(), 7.0, TOLERANCE);
    EXPECT_NEAR(v12(2)(), 9.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanAdd)
{
    VectorN_CanAdd<units::length::meter_t>();
    VectorN_CanAdd<units::velocity::meters_per_second_t>();
    VectorN_CanAdd<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanAdd<units::angular_velocity::radians_per_second_t>();
    VectorN_CanAdd<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanAdd<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanAdd<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanAdd<units::force::newton_t>();
    VectorN_CanAdd<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanNegate()
{
    mc::VectorN<T,SIZE> v1;
    v1(0) = T{1};
    v1(1) = T{2};
    v1(2) = T{3};

    mc::VectorN<T,SIZE> v1_n = -v1;

    EXPECT_NEAR(v1_n(0)(), -1.0, TOLERANCE);
    EXPECT_NEAR(v1_n(1)(), -2.0, TOLERANCE);
    EXPECT_NEAR(v1_n(2)(), -3.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanNegate)
{
    VectorN_CanNegate<units::length::meter_t>();
    VectorN_CanNegate<units::velocity::meters_per_second_t>();
    VectorN_CanNegate<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanNegate<units::angular_velocity::radians_per_second_t>();
    VectorN_CanNegate<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanNegate<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanNegate<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanNegate<units::force::newton_t>();
    VectorN_CanNegate<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanSubtract()
{
    std::vector<T> x1 { T{4}, T{5}, T{6} };
    std::vector<T> x2 { T{3}, T{2}, T{1} };
    mc::VectorN<T,SIZE> v1;
    mc::VectorN<T,SIZE> v2;
    v1.setFromStdVector(x1);
    v2.setFromStdVector(x2);

    mc::VectorN<T,SIZE> v12 = v1 - v2;

    EXPECT_NEAR(v12(0)(), 1.0, TOLERANCE);
    EXPECT_NEAR(v12(1)(), 3.0, TOLERANCE);
    EXPECT_NEAR(v12(2)(), 5.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanSubtract)
{
    VectorN_CanSubtract<units::length::meter_t>();
    VectorN_CanSubtract<units::velocity::meters_per_second_t>();
    VectorN_CanSubtract<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanSubtract<units::angular_velocity::radians_per_second_t>();
    VectorN_CanSubtract<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanSubtract<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanSubtract<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanSubtract<units::force::newton_t>();
    VectorN_CanSubtract<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanMultiplyByDouble()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    double val = 2.0;

    mc::VectorN<T, SIZE> vr = v * val;

    EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanMultiplyByDouble)
{
    VectorN_CanMultiplyByDouble<units::length::meter_t>();
    VectorN_CanMultiplyByDouble<units::velocity::meters_per_second_t>();
    VectorN_CanMultiplyByDouble<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanMultiplyByDouble<units::angular_velocity::radians_per_second_t>();
    VectorN_CanMultiplyByDouble<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanMultiplyByDouble<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanMultiplyByDouble<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanMultiplyByDouble<units::force::newton_t>();
    VectorN_CanMultiplyByDouble<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanMultiplyDimensionlessVectorByScalar()
{
    mc::VectorN<double,SIZE> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    T val = T{2.0};

    mc::VectorN<T, SIZE> vr = v * val;

    EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanMultiplyDimensionlessVectorByScalar)
{
    VectorN_CanMultiplyDimensionlessVectorByScalar<units::length::meter_t>();
    VectorN_CanMultiplyDimensionlessVectorByScalar<units::velocity::meters_per_second_t>();
    VectorN_CanMultiplyDimensionlessVectorByScalar<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanMultiplyDimensionlessVectorByScalar<units::angular_velocity::radians_per_second_t>();
    VectorN_CanMultiplyDimensionlessVectorByScalar<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanMultiplyDimensionlessVectorByScalar<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanMultiplyDimensionlessVectorByScalar<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanMultiplyDimensionlessVectorByScalar<units::force::newton_t>();
    VectorN_CanMultiplyDimensionlessVectorByScalar<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanMultiplyByScalar()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    units::length::meter_t val = 2.0_m;

    mc::VectorN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::length::meter
            >
        >,
        SIZE
    > vr = v * val;

    EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanMultiplyByScalar)
{
    VectorN_CanMultiplyByScalar<units::length::meter_t>();
    VectorN_CanMultiplyByScalar<units::velocity::meters_per_second_t>();
    VectorN_CanMultiplyByScalar<units::acceleration::meters_per_second_squared_t>();

    // angular velocity and angular acceleration excluded from this test
    // because they are treated in a special way

    VectorN_CanMultiplyByScalar<units::force::newton_t>();
    VectorN_CanMultiplyByScalar<units::torque::newton_meter_t>();
}

// template <typename T>
// void VectorN_CanMultiplyByScalarTime()
// {
//     mc::VectorN<T,SIZE> v;
//     v(0) = T{1};
//     v(1) = T{2};
//     v(2) = T{3};

//     units::time::second_t val = 2.0_s;

//     mc::VectorN<
//         units::unit_t<
//         units::compound_unit<
//                 typename units::traits::unit_t_traits<T>::unit_type,
//                 units::time::second
//             >
//         >,
//         SIZE
//     > vr = v * val;

//     EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
//     EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
//     EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanMultiplyByScalarTime)
// {
//     VectorN_CanMultiplyByScalarTime<units::length::meter_t>();
//     VectorN_CanMultiplyByScalarTime<units::velocity::meters_per_second_t>();
//     VectorN_CanMultiplyByScalarTime<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanMultiplyByScalarTime<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanMultiplyByScalarTime<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanMultiplyByScalarTime<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanMultiplyByScalarTime<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanMultiplyByScalarTime<units::force::newton_t>();
//     VectorN_CanMultiplyByScalarTime<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanMultiplyByScalarAngularVel()
// {
//     mc::VectorN<T,SIZE> v;
//     v(0) = T{1};
//     v(1) = T{2};
//     v(2) = T{3};

//     units::angular_velocity::degrees_per_second_t val = 2.0_rad_per_s;

//     mc::VectorN<
//         units::unit_t<
//             units::compound_unit<
//                 typename units::traits::unit_t_traits<T>::unit_type,
//                 typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
//             >
//         >,
//         SIZE
//     > vr = v * val;

//     EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
//     EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
//     EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanMultiplyByScalarAngularVel)
// {
//     VectorN_CanMultiplyByScalarAngularVel<units::length::meter_t>();
//     VectorN_CanMultiplyByScalarAngularVel<units::velocity::meters_per_second_t>();
//     VectorN_CanMultiplyByScalarAngularVel<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanMultiplyByScalarAngularVel<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanMultiplyByScalarAngularVel<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanMultiplyByScalarAngularVel<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanMultiplyByScalarAngularVel<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanMultiplyByScalarAngularVel<units::force::newton_t>();
//     VectorN_CanMultiplyByScalarAngularVel<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanMultiplyByScalarAngularAcc()
// {
//     mc::VectorN<T,SIZE> v;
//     v(0) = T{1};
//     v(1) = T{2};
//     v(2) = T{3};

//     units::angular_acceleration::degrees_per_second_squared_t val = 2.0_rad_per_s_sq;

//     mc::VectorN<
//         units::unit_t<
//         units::compound_unit<
//                 typename units::traits::unit_t_traits<T>::unit_type,
//                 typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
//             >
//         >,
//         SIZE
//     > vr = v * val;

//     EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
//     EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
//     EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanMultiplyByScalarAngularAcc)
// {
//     VectorN_CanMultiplyByScalarAngularAcc<units::length::meter_t>();
//     VectorN_CanMultiplyByScalarAngularAcc<units::velocity::meters_per_second_t>();
//     VectorN_CanMultiplyByScalarAngularAcc<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanMultiplyByScalarAngularAcc<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanMultiplyByScalarAngularAcc<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanMultiplyByScalarAngularAcc<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanMultiplyByScalarAngularAcc<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanMultiplyByScalarAngularAcc<units::force::newton_t>();
//     VectorN_CanMultiplyByScalarAngularAcc<units::torque::newton_meter_t>();
// }

// TEST_F(TestVectorNWithUnits, CanMultiplyByScalarDimensionlessVector)
// {
//     mc::VectorN<double,SIZE> v;
//     v(0) = 1.0;
//     v(1) = 2.0;
//     v(2) = 3.0;

//     mc::VectorN<units::length::meter_t,SIZE> vr = v * 2.0_m;

//     EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
//     EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
//     EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
// }

// template <typename T>
// void VectorN_CanMultiplyByScalarDimensionless()
// {
//     mc::VectorN<T,SIZE> v;
//     v(0) = T{1};
//     v(1) = T{2};
//     v(2) = T{3};

//     mc::VectorN<T,SIZE> vr = v * 2.0;

//     EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
//     EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
//     EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanMultiplyByScalarDimensionless)
// {
//     VectorN_CanMultiplyByScalarDimensionless<units::length::meter_t>();
//     VectorN_CanMultiplyByScalarDimensionless<units::velocity::meters_per_second_t>();
//     VectorN_CanMultiplyByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanMultiplyByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanMultiplyByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanMultiplyByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanMultiplyByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanMultiplyByScalarDimensionless<units::force::newton_t>();
//     VectorN_CanMultiplyByScalarDimensionless<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanCalculateDotProduct()
// {
//     mc::VectorN<T,SIZE> v;
//     v(0) = T{1};
//     v(1) = T{2};
//     v(2) = T{3};

//     using ResultType = typename units::unit_t<units::squared<typename units::traits::unit_t_traits<T>::unit_type>>;

//     ResultType s = v * v;

//     EXPECT_NEAR(s(), 14.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanCalculateDotProduct)
// {
//     VectorN_CanCalculateDotProduct<units::length::meter_t>();
//     VectorN_CanCalculateDotProduct<units::velocity::meters_per_second_t>();
//     VectorN_CanCalculateDotProduct<units::acceleration::meters_per_second_squared_t>();

//     // angular velocity and angular acceleration excluded from this test
//     // because they are treated in a special way

//     VectorN_CanCalculateDotProduct<units::force::newton_t>();
//     VectorN_CanCalculateDotProduct<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanCalculateVectorDotProductAngularVel()
// {
//     mc::VectorN<T,SIZE> v1;
//     v1(0) = T{1};
//     v1(1) = T{2};
//     v1(2) = T{3};

//     mc::VectorN<units::angular_velocity::radians_per_second_t,SIZE> v2;
//     v2(0) = 4.0_rad_per_s;
//     v2(1) = 5.0_rad_per_s;
//     v2(2) = 6.0_rad_per_s;

//     using ResultType = typename units::unit_t<
//         units::compound_unit<
//             typename units::traits::unit_t_traits<T>::unit_type,
//             typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
//         >
//     >;

//     ResultType s12 = v1 * v2;
//     ResultType s21 = v2 * v1;

//     // expected values calculated with wxMaxima
//     // tests/mcsim/utils/math/python/test_vector3_dot_product.py
//     EXPECT_NEAR(s12(), 32.0, TOLERANCE);
//     EXPECT_NEAR(s21(), 32.0, TOLERANCE);
// }


// TEST_F(TestVectorNWithUnits, CanCalculateVectorDotProductAngularVel)
// {
//     VectorN_CanCalculateVectorDotProductAngularVel<units::length::meter_t>();
//     VectorN_CanCalculateVectorDotProductAngularVel<units::velocity::meters_per_second_t>();
//     VectorN_CanCalculateVectorDotProductAngularVel<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanCalculateVectorDotProductAngularVel<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanCalculateVectorDotProductAngularVel<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanCalculateVectorDotProductAngularVel<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanCalculateVectorDotProductAngularVel<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanCalculateVectorDotProductAngularVel<units::force::newton_t>();
//     VectorN_CanCalculateVectorDotProductAngularVel<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanCalculateVectorDotProductAngularAcc()
// {
//     mc::VectorN<T,SIZE> v1;
//     v1(0) = T{1};
//     v1(1) = T{2};
//     v1(2) = T{3};

//     mc::VectorN<units::angular_acceleration::radians_per_second_squared_t, SIZE> v2;
//     v2(0) = 4.0_rad_per_s_sq;
//     v2(1) = 5.0_rad_per_s_sq;
//     v2(2) = 6.0_rad_per_s_sq;

//     using ResultType = typename units::unit_t<
//         units::compound_unit<
//             typename units::traits::unit_t_traits<T>::unit_type,
//             typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
//         >
//     >;

//     ResultType s12 = v1 * v2;
//     ResultType s21 = v2 * v1;

//     // expected values calculated with wxMaxima
//     // tests/mcsim/utils/math/python/test_vector3_dot_product.py
//     EXPECT_NEAR(s12(), 32.0, TOLERANCE);
//     EXPECT_NEAR(s21(), 32.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanCalculateVectorDotProductAngularAcc)
// {
//     VectorN_CanCalculateVectorDotProductAngularAcc<units::length::meter_t>();
//     VectorN_CanCalculateVectorDotProductAngularAcc<units::velocity::meters_per_second_t>();
//     VectorN_CanCalculateVectorDotProductAngularAcc<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanCalculateVectorDotProductAngularAcc<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanCalculateVectorDotProductAngularAcc<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanCalculateVectorDotProductAngularAcc<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanCalculateVectorDotProductAngularAcc<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanCalculateVectorDotProductAngularAcc<units::force::newton_t>();
//     VectorN_CanCalculateVectorDotProductAngularAcc<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanCalculateDotProductDimensionless()
// {
//     mc::VectorN<T,SIZE> v1;
//     v1(0) = T{1};
//     v1(1) = T{2};
//     v1(2) = T{3};

//     mc::VectorN<double,SIZE> v2;
//     v2(0) = 4.0;
//     v2(1) = 5.0;
//     v2(2) = 6.0;

//     T s12 = v1 * v2;
//     T s21 = v2 * v1;

//     // expected values calculated with wxMaxima
//     // tests/mcsim/utils/math/python/test_vector3_dot_product.py
//     EXPECT_NEAR(s12(), 32.0, TOLERANCE);
//     EXPECT_NEAR(s21(), 32.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanCalculateDotProductDimensionless)
// {
//     VectorN_CanCalculateDotProductDimensionless<units::length::meter_t>();
//     VectorN_CanCalculateDotProductDimensionless<units::velocity::meters_per_second_t>();
//     VectorN_CanCalculateDotProductDimensionless<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanCalculateDotProductDimensionless<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanCalculateDotProductDimensionless<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanCalculateDotProductDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanCalculateDotProductDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanCalculateDotProductDimensionless<units::force::newton_t>();
//     VectorN_CanCalculateDotProductDimensionless<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanDivideByScalar()
// {
//     mc::VectorN<T,SIZE> v;
//     v(0) = T{1};
//     v(1) = T{2};
//     v(2) = T{3};

//     units::length::meter_t val = 2.0_m;

//     mc::VectorN<
//         units::unit_t<
//         units::compound_unit<
//                 typename units::traits::unit_t_traits<T>::unit_type,
//                 units::inverse<units::length::meter>
//             >
//         >,
//         SIZE
//     > vr = v / val;

//     EXPECT_NEAR(vr(0)(), 0.5, TOLERANCE);
//     EXPECT_NEAR(vr(1)(), 1.0, TOLERANCE);
//     EXPECT_NEAR(vr(2)(), 1.5, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanDivideByScalar)
// {
//     VectorN_CanDivideByScalar<units::length::meter_t>();
//     VectorN_CanDivideByScalar<units::velocity::meters_per_second_t>();
//     VectorN_CanDivideByScalar<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanDivideByScalar<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanDivideByScalar<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanDivideByScalar<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanDivideByScalar<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanDivideByScalar<units::force::newton_t>();
//     VectorN_CanDivideByScalar<units::torque::newton_meter_t>();
// }

// TEST_F(TestVectorNWithUnits, CanDivideByScalarDimensionlessVector)
// {
//     mc::VectorN<double,SIZE> v;
//     v(0) = 1.0;
//     v(1) = 2.0;
//     v(2) = 3.0;

//     constexpr units::time::second_t val = 2.0_s;
//     mc::VectorN<units::frequency::hertz_t,SIZE> vr = v / val;

//     EXPECT_NEAR(vr(0)(), 0.5, TOLERANCE);
//     EXPECT_NEAR(vr(1)(), 1.0, TOLERANCE);
//     EXPECT_NEAR(vr(2)(), 1.5, TOLERANCE);
// }

// template <typename T>
// void VectorN_CanDivideByScalarDimensionless()
// {
//     mc::VectorN<T,SIZE> v;
//     v(0) = T{1};
//     v(1) = T{2};
//     v(2) = T{3};

//     double val = 2.0;

//     mc::VectorN<T,SIZE> vr = v / val;

//     EXPECT_NEAR(vr(0)(), 0.5, TOLERANCE);
//     EXPECT_NEAR(vr(1)(), 1.0, TOLERANCE);
//     EXPECT_NEAR(vr(2)(), 1.5, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanDivideByScalarDimensionless)
// {
//     VectorN_CanDivideByScalarDimensionless<units::length::meter_t>();
//     VectorN_CanDivideByScalarDimensionless<units::velocity::meters_per_second_t>();
//     VectorN_CanDivideByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanDivideByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanDivideByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanDivideByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanDivideByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanDivideByScalarDimensionless<units::force::newton_t>();
//     VectorN_CanDivideByScalarDimensionless<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanUnaryAdd()
// {
//     mc::VectorN<T,SIZE> v0;
//     v0(0) = T{1};
//     v0(1) = T{2};
//     v0(2) = T{3};

//     mc::VectorN<T,SIZE> v1;
//     v1(0) = T{2};
//     v1(1) = T{3};
//     v1(2) = T{4};

//     v0 += v1;

//     EXPECT_NEAR(v0(0)(), 3.0, TOLERANCE);
//     EXPECT_NEAR(v0(1)(), 5.0, TOLERANCE);
//     EXPECT_NEAR(v0(2)(), 7.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanUnaryAdd)
// {
//     VectorN_CanUnaryAdd<units::length::meter_t>();
//     VectorN_CanUnaryAdd<units::velocity::meters_per_second_t>();
//     VectorN_CanUnaryAdd<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanUnaryAdd<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanUnaryAdd<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanUnaryAdd<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanUnaryAdd<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanUnaryAdd<units::force::newton_t>();
//     VectorN_CanUnaryAdd<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanUnarySubtract()
// {
//     mc::VectorN<T,SIZE> v0;
//     v0(0) = T{3};
//     v0(1) = T{5};
//     v0(2) = T{7};

//     mc::VectorN<T,SIZE> v1;
//     v1(0) = T{2};
//     v1(1) = T{3};
//     v1(2) = T{4};

//     v0 -= v1;

//     EXPECT_NEAR(v0(0)(), 1.0, TOLERANCE);
//     EXPECT_NEAR(v0(1)(), 2.0, TOLERANCE);
//     EXPECT_NEAR(v0(2)(), 3.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanUnarySubtract)
// {
//     VectorN_CanUnarySubtract<units::length::meter_t>();
//     VectorN_CanUnarySubtract<units::velocity::meters_per_second_t>();
//     VectorN_CanUnarySubtract<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanUnarySubtract<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanUnarySubtract<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanUnarySubtract<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanUnarySubtract<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanUnarySubtract<units::force::newton_t>();
//     VectorN_CanUnarySubtract<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanUnaryMultiplyByScalarDimensionless()
// {
//     mc::VectorN<T,SIZE> v0;
//     v0(0) = T{2};
//     v0(1) = T{4};
//     v0(2) = T{6};

//     v0 *= 0.5;

//     EXPECT_NEAR(v0(0)(), 1.0, TOLERANCE);
//     EXPECT_NEAR(v0(1)(), 2.0, TOLERANCE);
//     EXPECT_NEAR(v0(2)(), 3.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanUnaryMultiplyByScalarDimensionless)
// {
//     VectorN_CanUnaryMultiplyByScalarDimensionless<units::length::meter_t>();
//     VectorN_CanUnaryMultiplyByScalarDimensionless<units::velocity::meters_per_second_t>();
//     VectorN_CanUnaryMultiplyByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanUnaryMultiplyByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanUnaryMultiplyByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanUnaryMultiplyByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanUnaryMultiplyByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanUnaryMultiplyByScalarDimensionless<units::force::newton_t>();
//     VectorN_CanUnaryMultiplyByScalarDimensionless<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanUnaryDivideByScalarDimensionless()
// {
//     mc::VectorN<T,SIZE> v0;
//     v0(0) = T{2};
//     v0(1) = T{4};
//     v0(2) = T{6};

//     v0 /= 2.0;

//     EXPECT_NEAR(v0(0)(), 1.0, TOLERANCE);
//     EXPECT_NEAR(v0(1)(), 2.0, TOLERANCE);
//     EXPECT_NEAR(v0(2)(), 3.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanUnaryDivideByScalarDimensionless)
// {
//     VectorN_CanUnaryDivideByScalarDimensionless<units::length::meter_t>();
//     VectorN_CanUnaryDivideByScalarDimensionless<units::velocity::meters_per_second_t>();
//     VectorN_CanUnaryDivideByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanUnaryDivideByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanUnaryDivideByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanUnaryDivideByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanUnaryDivideByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanUnaryDivideByScalarDimensionless<units::force::newton_t>();
//     VectorN_CanUnaryDivideByScalarDimensionless<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanCompare()
// {
//     mc::VectorN<T,SIZE> v1;
//     mc::VectorN<T,SIZE> v2;
//     v1(0) = v2(0) = T{1};
//     v1(1) = v2(1) = T{2};
//     v1(2) = v2(2) = T{3};

//     mc::VectorN<T,SIZE> v3;
//     v3(0) = T{4};
//     v3(1) = T{5};
//     v3(2) = T{6};

//     EXPECT_TRUE(v1 == v2);
//     EXPECT_TRUE(v1 != v3);
//     EXPECT_FALSE(v1 == v3);
//     EXPECT_FALSE(v1 != v2);
// }

// TEST_F(TestVectorNWithUnits, CanCompare)
// {
//     VectorN_CanCompare<units::length::meter_t>();
//     VectorN_CanCompare<units::velocity::meters_per_second_t>();
//     VectorN_CanCompare<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanCompare<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanCompare<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanCompare<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanCompare<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanCompare<units::force::newton_t>();
//     VectorN_CanCompare<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanMultiplyScalarByVector()
// {
//     mc::VectorN<T,SIZE> v;
//     v(0) = T{1};
//     v(1) = T{2};
//     v(2) = T{3};

//     units::length::meter_t val = 2.0_m;

//     mc::VectorN<
//         units::unit_t<
//         units::compound_unit<
//                 typename units::traits::unit_t_traits<T>::unit_type,
//                 units::length::meter
//             >
//         >,
//         SIZE
//     > vr = val * v;

//     EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
//     EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
//     EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanMultiplyScalarByVector)
// {
//     VectorN_CanMultiplyScalarByVector<units::length::meter_t>();
//     VectorN_CanMultiplyScalarByVector<units::velocity::meters_per_second_t>();
//     VectorN_CanMultiplyScalarByVector<units::acceleration::meters_per_second_squared_t>();

//     // angular velocity and angular acceleration excluded from this test
//     // because they are treated in a special way

//     VectorN_CanMultiplyScalarByVector<units::force::newton_t>();
//     VectorN_CanMultiplyScalarByVector<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanMultiplyScalarByVectorTime()
// {
//     mc::VectorN<T,SIZE> v;
//     v(0) = T{1};
//     v(1) = T{2};
//     v(2) = T{3};

//     units::time::second_t val = 2.0_s;

//     mc::VectorN<
//         units::unit_t<
//         units::compound_unit<
//                 typename units::traits::unit_t_traits<T>::unit_type,
//                 units::time::second
//             >
//         >,
//         SIZE
//     > vr = val * v;

//     EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
//     EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
//     EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanMultiplyScalarByVectorTime)
// {
//     VectorN_CanMultiplyScalarByVectorTime<units::length::meter_t>();
//     VectorN_CanMultiplyScalarByVectorTime<units::velocity::meters_per_second_t>();
//     VectorN_CanMultiplyScalarByVectorTime<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanMultiplyScalarByVectorTime<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanMultiplyScalarByVectorTime<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanMultiplyScalarByVectorTime<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanMultiplyScalarByVectorTime<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanMultiplyScalarByVectorTime<units::force::newton_t>();
//     VectorN_CanMultiplyScalarByVectorTime<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanMultiplyScalarByVectorAngularVel()
// {
//     mc::VectorN<T,SIZE> v;
//     v(0) = T{1};
//     v(1) = T{2};
//     v(2) = T{3};

//     units::angular_velocity::degrees_per_second_t val = 2.0_rad_per_s;

//     mc::VectorN<
//         units::unit_t<
//         units::compound_unit<
//                 typename units::traits::unit_t_traits<T>::unit_type,
//                 typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
//             >
//         >,
//         SIZE
//     > vr = val * v;

//     EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
//     EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
//     EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanMultiplyScalarByVectorAngularVel)
// {
//     VectorN_CanMultiplyScalarByVectorAngularVel<units::length::meter_t>();
//     VectorN_CanMultiplyScalarByVectorAngularVel<units::velocity::meters_per_second_t>();
//     VectorN_CanMultiplyScalarByVectorAngularVel<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanMultiplyScalarByVectorAngularVel<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanMultiplyScalarByVectorAngularVel<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanMultiplyScalarByVectorAngularVel<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanMultiplyScalarByVectorAngularVel<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanMultiplyScalarByVectorAngularVel<units::force::newton_t>();
//     VectorN_CanMultiplyScalarByVectorAngularVel<units::torque::newton_meter_t>();
// }

// template <typename T>
// void VectorN_CanMultiplyScalarByVectorAngularAcc()
// {
//     mc::VectorN<T,SIZE> v;
//     v(0) = T{1};
//     v(1) = T{2};
//     v(2) = T{3};

//     units::angular_acceleration::degrees_per_second_squared_t val = 2.0_rad_per_s_sq;

//     mc::VectorN<
//         units::unit_t<
//         units::compound_unit<
//                 typename units::traits::unit_t_traits<T>::unit_type,
//                 typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
//             >
//         >,
//         SIZE
//     > vr = val * v;

//     EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
//     EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
//     EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanMultiplyScalarByVectorAngularAcc)
// {
//     VectorN_CanMultiplyScalarByVectorAngularAcc<units::length::meter_t>();
//     VectorN_CanMultiplyScalarByVectorAngularAcc<units::velocity::meters_per_second_t>();
//     VectorN_CanMultiplyScalarByVectorAngularAcc<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanMultiplyScalarByVectorAngularAcc<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanMultiplyScalarByVectorAngularAcc<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanMultiplyScalarByVectorAngularAcc<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanMultiplyScalarByVectorAngularAcc<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanMultiplyScalarByVectorAngularAcc<units::force::newton_t>();
//     VectorN_CanMultiplyScalarByVectorAngularAcc<units::torque::newton_meter_t>();
// }

// TEST_F(TestVectorNWithUnits, CanMultiplyScalarByVectorDimensionlessVector)
// {
//     mc::VectorN<double,SIZE> v;
//     v(0) = 1.0;
//     v(1) = 2.0;
//     v(2) = 3.0;

//     mc::VectorN<units::length::meter_t,SIZE> vr = 2.0_m * v;

//     EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
//     EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
//     EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
// }

// template <typename T>
// void VectorN_CanMultiplyScalarByVectorDimensionless()
// {
//     mc::VectorN<T,SIZE> v;
//     v(0) = T{1};
//     v(1) = T{2};
//     v(2) = T{3};

//     mc::VectorN<T,SIZE> vr = 2.0 * v;

//     EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
//     EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
//     EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
// }

// TEST_F(TestVectorNWithUnits, CanMultiplyScalarByVectorDimensionless)
// {
//     VectorN_CanMultiplyScalarByVectorDimensionless<units::length::meter_t>();
//     VectorN_CanMultiplyScalarByVectorDimensionless<units::velocity::meters_per_second_t>();
//     VectorN_CanMultiplyScalarByVectorDimensionless<units::acceleration::meters_per_second_squared_t>();
//     VectorN_CanMultiplyScalarByVectorDimensionless<units::angular_velocity::radians_per_second_t>();
//     VectorN_CanMultiplyScalarByVectorDimensionless<units::angular_velocity::degrees_per_second_t>();
//     VectorN_CanMultiplyScalarByVectorDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
//     VectorN_CanMultiplyScalarByVectorDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
//     VectorN_CanMultiplyScalarByVectorDimensionless<units::force::newton_t>();
//     VectorN_CanMultiplyScalarByVectorDimensionless<units::torque::newton_meter_t>();
// }