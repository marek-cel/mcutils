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

template <typename T1, typename T2>
void VectorN_CanInstantiateFromDifferentType()
{
    mc::VectorN<T1,SIZE> v1;

    v1(0) = T2{1};
    v1(1) = T2{2};
    v1(2) = T2{3};

    mc::VectorN<T2,SIZE> v2(v1);
    
    EXPECT_DOUBLE_EQ(v2(0)(), 1.0);
    EXPECT_DOUBLE_EQ(v2(1)(), 2.0);
    EXPECT_DOUBLE_EQ(v2(2)(), 3.0);
}

TEST_F(TestVectorNWithUnits, CanInstantiateFromDifferentType)
{
    VectorN_CanInstantiateFromDifferentType<
        units::length::meter_t,
        units::length::foot_t
    >();
    VectorN_CanInstantiateFromDifferentType<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t
    >();
    VectorN_CanInstantiateFromDifferentType<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t
    >();
    VectorN_CanInstantiateFromDifferentType<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t
    >();
    VectorN_CanInstantiateFromDifferentType<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t
    >();
    VectorN_CanInstantiateFromDifferentType<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t
    >();
    VectorN_CanInstantiateFromDifferentType<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t
    >();
    VectorN_CanInstantiateFromDifferentType<
        units::force::newton_t,
        units::force::pound_t
    >();
    VectorN_CanInstantiateFromDifferentType<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t
    >();     
}

template <typename T>
void VectorN_CanValidate()
{
    mc::VectorN<T,SIZE> v;

    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

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
    EXPECT_DOUBLE_EQ(v.getLengthSq()(), 14.0);
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
void VectorN_CanGetStdArray()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    std::array<T, SIZE> result;
    result = v.getStdArray();

    EXPECT_NEAR(result[0](), 1.0, TOLERANCE);
    EXPECT_NEAR(result[1](), 2.0, TOLERANCE);
    EXPECT_NEAR(result[2](), 3.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanGetStdArray)
{
    VectorN_CanGetStdArray<units::length::meter_t>();
    VectorN_CanGetStdArray<units::velocity::meters_per_second_t>();
    VectorN_CanGetStdArray<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanGetStdArray<units::angular_velocity::radians_per_second_t>();
    VectorN_CanGetStdArray<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanGetStdArray<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanGetStdArray<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanGetStdArray<units::force::newton_t>();
    VectorN_CanGetStdArray<units::torque::newton_meter_t>();
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
void VectorN_CanSetFromStdArray()
{
    std::array<T, SIZE> x { T{1}, T{2}, T{3} };
    mc::VectorN<T,SIZE> v;
    v.setFromStdArray(x);

    EXPECT_NEAR(v(0)(), 1.0, TOLERANCE);
    EXPECT_NEAR(v(1)(), 2.0, TOLERANCE);
    EXPECT_NEAR(v(2)(), 3.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanSetFromStdArray)
{
    VectorN_CanSetFromStdArray<units::length::meter_t>();
    VectorN_CanSetFromStdArray<units::velocity::meters_per_second_t>();
    VectorN_CanSetFromStdArray<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanSetFromStdArray<units::angular_velocity::radians_per_second_t>();
    VectorN_CanSetFromStdArray<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanSetFromStdArray<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanSetFromStdArray<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanSetFromStdArray<units::force::newton_t>();
    VectorN_CanSetFromStdArray<units::torque::newton_meter_t>();
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
void VectorN_CanCastToDimensionless()
{
    mc::VectorN<T,SIZE> v1;
    v1(0) = T{1};
    v1(1) = T{2};
    v1(2) = T{3};

    mc::VectorN<double,SIZE> v2;
    v2 = static_cast<mc::VectorN<double,SIZE>>(v1);
    EXPECT_NEAR(v2(0), 1.0, TOLERANCE);
    EXPECT_NEAR(v2(1), 2.0, TOLERANCE);
    EXPECT_NEAR(v2(2), 3.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanCastToDimensionless)
{
    VectorN_CanCastToDimensionless<units::length::meter_t>();
    VectorN_CanCastToDimensionless<units::velocity::meters_per_second_t>();
    VectorN_CanCastToDimensionless<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanCastToDimensionless<units::angular_velocity::radians_per_second_t>();
    VectorN_CanCastToDimensionless<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanCastToDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanCastToDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanCastToDimensionless<units::force::newton_t>();
    VectorN_CanCastToDimensionless<units::torque::newton_meter_t>();
}

template <typename T1, typename T2>
void VectorN_CanCastToDifferentUnit()
{
    mc::VectorN<T1,SIZE> v1;
    v1(0) = T2{1};
    v1(1) = T2{2};
    v1(2) = T2{3};

    mc::VectorN<T2,SIZE> v2;
    v2 = static_cast<mc::VectorN<T2,SIZE>>(v1);

    EXPECT_NEAR(v2(0)(), 1.0, TOLERANCE);
    EXPECT_NEAR(v2(1)(), 2.0, TOLERANCE);
    EXPECT_NEAR(v2(2)(), 3.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanCastToDifferentUnit)
{
    VectorN_CanCastToDifferentUnit<
        units::length::meter_t,
        units::length::foot_t
    >();
    VectorN_CanCastToDifferentUnit<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t
    >();
    VectorN_CanCastToDifferentUnit<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t
    >();
    VectorN_CanCastToDifferentUnit<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t
    >();
    VectorN_CanCastToDifferentUnit<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t
    >();
    VectorN_CanCastToDifferentUnit<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t
    >();
    VectorN_CanCastToDifferentUnit<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t
    >();
    VectorN_CanCastToDifferentUnit<
        units::force::newton_t,
        units::force::pound_t
    >();
    VectorN_CanCastToDifferentUnit<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t
    >();  
}

template <typename T>
void VectorN_CanAddSameTypes()
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

TEST_F(TestVectorNWithUnits, CanAddSameTypes)
{
    VectorN_CanAddSameTypes<units::length::meter_t>();
    VectorN_CanAddSameTypes<units::velocity::meters_per_second_t>();
    VectorN_CanAddSameTypes<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanAddSameTypes<units::angular_velocity::radians_per_second_t>();
    VectorN_CanAddSameTypes<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanAddSameTypes<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanAddSameTypes<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanAddSameTypes<units::force::newton_t>();
    VectorN_CanAddSameTypes<units::torque::newton_meter_t>();
}

template <typename T1, typename T2>
void VectorN_CanAddDifferentTypes()
{
    mc::VectorN<T1,SIZE> v1;
    mc::VectorN<T2,SIZE> v2;

    v1(0) = T1{1};
    v1(1) = T1{2};
    v1(2) = T1{3};

    v2(0) = T1{4};
    v2(1) = T1{5};
    v2(2) = T1{6};

    mc::VectorN<T1,SIZE> v12 = v1 + v2;

    EXPECT_NEAR(v12(0)(), 5.0, TOLERANCE);
    EXPECT_NEAR(v12(1)(), 7.0, TOLERANCE);
    EXPECT_NEAR(v12(2)(), 9.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanAddDifferentTypes)
{
    VectorN_CanAddDifferentTypes<
        units::length::meter_t,
        units::length::foot_t
    >();
    VectorN_CanAddDifferentTypes<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t
    >();
    VectorN_CanAddDifferentTypes<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t
    >();
    VectorN_CanAddDifferentTypes<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t
    >();
    VectorN_CanAddDifferentTypes<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t
    >();
    VectorN_CanAddDifferentTypes<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t
    >();
    VectorN_CanAddDifferentTypes<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t
    >();
    VectorN_CanAddDifferentTypes<
        units::force::newton_t,
        units::force::pound_t
    >();
    VectorN_CanAddDifferentTypes<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t
    >();
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
void VectorN_CanSubtractSameTypes()
{
    mc::VectorN<T,SIZE> v1;
    mc::VectorN<T,SIZE> v2;

    v1(0) = T{4};
    v1(1) = T{5};
    v1(2) = T{6};

    v2(0) = T{3};
    v2(1) = T{2};
    v2(2) = T{1};

    mc::VectorN<T,SIZE> v12 = v1 - v2;

    EXPECT_NEAR(v12(0)(), 1.0, TOLERANCE);
    EXPECT_NEAR(v12(1)(), 3.0, TOLERANCE);
    EXPECT_NEAR(v12(2)(), 5.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanSubtractSameTypes)
{
    VectorN_CanSubtractSameTypes<units::length::meter_t>();
    VectorN_CanSubtractSameTypes<units::velocity::meters_per_second_t>();
    VectorN_CanSubtractSameTypes<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanSubtractSameTypes<units::angular_velocity::radians_per_second_t>();
    VectorN_CanSubtractSameTypes<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanSubtractSameTypes<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanSubtractSameTypes<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanSubtractSameTypes<units::force::newton_t>();
    VectorN_CanSubtractSameTypes<units::torque::newton_meter_t>();
}

template <typename T1, typename T2>
void VectorN_CanSubtractDifferentTypes()
{
    mc::VectorN<T1,SIZE> v1;
    mc::VectorN<T2,SIZE> v2;

    v1(0) = T1{4};
    v1(1) = T1{5};
    v1(2) = T1{6};

    v2(0) = T1{3};
    v2(1) = T1{2};
    v2(2) = T1{1};

    mc::VectorN<T1,SIZE> v12 = v1 - v2;

    EXPECT_NEAR(v12(0)(), 1.0, TOLERANCE);
    EXPECT_NEAR(v12(1)(), 3.0, TOLERANCE);
    EXPECT_NEAR(v12(2)(), 5.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanSubtractDifferentTypes)
{
    VectorN_CanSubtractDifferentTypes<
        units::length::meter_t,
        units::length::foot_t
    >();
    VectorN_CanSubtractDifferentTypes<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t
    >();
    VectorN_CanSubtractDifferentTypes<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t
    >();
    VectorN_CanSubtractDifferentTypes<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t
    >();
    VectorN_CanSubtractDifferentTypes<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t
    >();
    VectorN_CanSubtractDifferentTypes<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t
    >();
    VectorN_CanSubtractDifferentTypes<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t
    >();
    VectorN_CanSubtractDifferentTypes<
        units::force::newton_t,
        units::force::pound_t
    >();
    VectorN_CanSubtractDifferentTypes<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t
    >();
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
    VectorN_CanMultiplyByScalar<units::force::newton_t>();
    VectorN_CanMultiplyByScalar<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanMultiplyByTimeScalar()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    units::time::second_t val = 2.0_s;

    mc::VectorN<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::time::second
            >
        >,
        SIZE
    > vr = v * val;

    EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanMultiplyByTimeScalar)
{
    VectorN_CanMultiplyByTimeScalar<units::length::meter_t>();
    VectorN_CanMultiplyByTimeScalar<units::velocity::meters_per_second_t>();
    VectorN_CanMultiplyByTimeScalar<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanMultiplyByTimeScalar<units::angular_velocity::radians_per_second_t>();
    VectorN_CanMultiplyByTimeScalar<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanMultiplyByTimeScalar<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanMultiplyByTimeScalar<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanMultiplyByTimeScalar<units::force::newton_t>();
    VectorN_CanMultiplyByTimeScalar<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanMultiplyByAngularVelScalar()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    units::angular_velocity::degrees_per_second_t val = 2.0_rad_per_s;

    mc::VectorN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_t>::unit_type
            >
        >,
        SIZE
    > vr = v * val;

    EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanMultiplyByAngularVelScalar)
{
    VectorN_CanMultiplyByAngularVelScalar<units::length::meter_t>();
    VectorN_CanMultiplyByAngularVelScalar<units::velocity::meters_per_second_t>();
    VectorN_CanMultiplyByAngularVelScalar<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanMultiplyByAngularVelScalar<units::force::newton_t>();
    VectorN_CanMultiplyByAngularVelScalar<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanMultiplyAngularVelVectorByScalar)
{
    mc::VectorN<units::angular_velocity::radians_per_second_t,SIZE> v;
    v(0) = 1.0_rad_per_s;
    v(1) = 2.0_rad_per_s;
    v(2) = 3.0_rad_per_s;

    units::length::meter_t val = 2.0_m;

    mc::VectorN<units::velocity::meters_per_second_t, SIZE> vr = v * val;

    EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
}

template <typename T>
void VectorN_CanMultiplyByAngularAccScalar()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    units::angular_acceleration::degrees_per_second_squared_t val = 2.0_rad_per_s_sq;

    mc::VectorN<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_squared_t>::unit_type
            >
        >,
        SIZE
    > vr = v * val;

    EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanMultiplyByAngularAccScalar)
{
    VectorN_CanMultiplyByAngularAccScalar<units::length::meter_t>();
    VectorN_CanMultiplyByAngularAccScalar<units::velocity::meters_per_second_t>();
    VectorN_CanMultiplyByAngularAccScalar<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanMultiplyByAngularAccScalar<units::force::newton_t>();
    VectorN_CanMultiplyByAngularAccScalar<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanMultiplyAngularAccVectorByScalar)
{
    mc::VectorN<units::angular_acceleration::radians_per_second_squared_t,SIZE> v;
    v(0) = 1.0_rad_per_s_sq;
    v(1) = 2.0_rad_per_s_sq;
    v(2) = 3.0_rad_per_s_sq;

    units::length::meter_t val = 2.0_m;

    mc::VectorN<units::acceleration::meters_per_second_squared_t, SIZE> vr = v * val;

    EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
}

template <typename T>
void VectorN_CanCalculateDotProduct()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    using ResultType = typename units::unit_t<units::squared<typename units::traits::unit_t_traits<T>::unit_type>>;

    ResultType s = v * v;

    EXPECT_NEAR(s(), 14.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanCalculateDotProduct)
{
    VectorN_CanCalculateDotProduct<units::length::meter_t>();
    VectorN_CanCalculateDotProduct<units::velocity::meters_per_second_t>();
    VectorN_CanCalculateDotProduct<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanCalculateDotProduct<units::force::newton_t>();
    VectorN_CanCalculateDotProduct<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanCalculateVectorDotProductOfAngularVelVector()
{
    mc::VectorN<T,SIZE> v1;
    v1(0) = T{1};
    v1(1) = T{2};
    v1(2) = T{3};

    mc::VectorN<units::angular_velocity::radians_per_second_t,SIZE> v2;
    v2(0) = 4.0_rad_per_s;
    v2(1) = 5.0_rad_per_s;
    v2(2) = 6.0_rad_per_s;

    using ResultType = typename units::unit_t<
        units::compound_unit<
            typename units::traits::unit_t_traits<T>::unit_type,
            typename units::traits::unit_t_traits<units::inverted::per_second_t>::unit_type
        >
    >;

    ResultType s12 = v1 * v2;
    ResultType s21 = v2 * v1;

    // expected values calculated with wxMaxima
    // tests/mcsim/utils/math/python/test_vector3_dot_product.py
    EXPECT_NEAR(s12(), 32.0, TOLERANCE);
    EXPECT_NEAR(s21(), 32.0, TOLERANCE);
}


TEST_F(TestVectorNWithUnits, CanCalculateVectorDotProductOfAngularVelVector)
{
    VectorN_CanCalculateVectorDotProductOfAngularVelVector<units::length::meter_t>();
    VectorN_CanCalculateVectorDotProductOfAngularVelVector<units::velocity::meters_per_second_t>();
    VectorN_CanCalculateVectorDotProductOfAngularVelVector<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanCalculateVectorDotProductOfAngularVelVector<units::force::newton_t>();
    VectorN_CanCalculateVectorDotProductOfAngularVelVector<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanCalculateAngularVelVectorDotProduct)
{
    mc::VectorN<units::angular_velocity::radians_per_second_t,SIZE> v1;
    v1(0) = 1.0_rad_per_s;
    v1(1) = 2.0_rad_per_s;
    v1(2) = 3.0_rad_per_s;

    mc::VectorN<units::angular_velocity::radians_per_second_t,SIZE> v2;
    v2(0) = 4.0_rad_per_s;
    v2(1) = 5.0_rad_per_s;
    v2(2) = 6.0_rad_per_s;

    using ResultType = typename units::unit_t<
        units::compound_unit<
            typename units::traits::unit_t_traits<units::angular_velocity::radians_per_second_t>::unit_type,
            typename units::traits::unit_t_traits<units::angular_velocity::radians_per_second_t>::unit_type
        >
    >;

    ResultType s12 = v1 * v2;
    ResultType s21 = v2 * v1;

    // expected values calculated with wxMaxima
    // tests/mcsim/utils/math/python/test_vector3_dot_product.py
    EXPECT_NEAR(s12(), 32.0, TOLERANCE);
    EXPECT_NEAR(s21(), 32.0, TOLERANCE);
}

template <typename T>
void VectorN_CanCalculateVectorDotProductOfAngularAccVector()
{
    mc::VectorN<T,SIZE> v1;
    v1(0) = T{1};
    v1(1) = T{2};
    v1(2) = T{3};

    mc::VectorN<units::angular_acceleration::radians_per_second_squared_t, SIZE> v2;
    v2(0) = 4.0_rad_per_s_sq;
    v2(1) = 5.0_rad_per_s_sq;
    v2(2) = 6.0_rad_per_s_sq;

    using ResultType = typename units::unit_t<
        units::compound_unit<
            typename units::traits::unit_t_traits<T>::unit_type,
            typename units::traits::unit_t_traits<units::inverted::per_second_squared_t>::unit_type
        >
    >;

    ResultType s12 = v1 * v2;
    ResultType s21 = v2 * v1;

    // expected values calculated with wxMaxima
    // tests/mcsim/utils/math/python/test_vector3_dot_product.py
    EXPECT_NEAR(s12(), 32.0, TOLERANCE);
    EXPECT_NEAR(s21(), 32.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanCalculateVectorDotProductOfAngularAccVector)
{
    VectorN_CanCalculateVectorDotProductOfAngularAccVector<units::length::meter_t>();
    VectorN_CanCalculateVectorDotProductOfAngularAccVector<units::velocity::meters_per_second_t>();
    VectorN_CanCalculateVectorDotProductOfAngularAccVector<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanCalculateVectorDotProductOfAngularAccVector<units::force::newton_t>();
    VectorN_CanCalculateVectorDotProductOfAngularAccVector<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanCalculateAngularAccVectorDotProduct)
{
    mc::VectorN<units::angular_acceleration::radians_per_second_squared_t,SIZE> v1;
    v1(0) = 1.0_rad_per_s_sq;
    v1(1) = 2.0_rad_per_s_sq;
    v1(2) = 3.0_rad_per_s_sq;

    mc::VectorN<units::angular_acceleration::radians_per_second_squared_t,SIZE> v2;
    v2(0) = 4.0_rad_per_s_sq;
    v2(1) = 5.0_rad_per_s_sq;
    v2(2) = 6.0_rad_per_s_sq;

    using ResultType = typename units::unit_t<
        units::compound_unit<
            typename units::traits::unit_t_traits<units::angular_acceleration::radians_per_second_squared_t>::unit_type,
            typename units::traits::unit_t_traits<units::angular_acceleration::radians_per_second_squared_t>::unit_type
        >
    >;

    ResultType s12 = v1 * v2;
    ResultType s21 = v2 * v1;

    // expected values calculated with wxMaxima
    // tests/mcsim/utils/math/python/test_vector3_dot_product.py
    EXPECT_NEAR(s12(), 32.0, TOLERANCE);
    EXPECT_NEAR(s21(), 32.0, TOLERANCE);
}

template <typename T>
void VectorN_CanCalculateDotProductDimensionless()
{
    mc::VectorN<T,SIZE> v1;
    v1(0) = T{1};
    v1(1) = T{2};
    v1(2) = T{3};

    mc::VectorN<double,SIZE> v2;
    v2(0) = 4.0;
    v2(1) = 5.0;
    v2(2) = 6.0;

    T s12 = v1 * v2;
    T s21 = v2 * v1;

    // expected values calculated with wxMaxima
    // tests/mcsim/utils/math/python/test_vector3_dot_product.py
    EXPECT_NEAR(s12(), 32.0, TOLERANCE);
    EXPECT_NEAR(s21(), 32.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanCalculateDotProductDimensionless)
{
    VectorN_CanCalculateDotProductDimensionless<units::length::meter_t>();
    VectorN_CanCalculateDotProductDimensionless<units::velocity::meters_per_second_t>();
    VectorN_CanCalculateDotProductDimensionless<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanCalculateDotProductDimensionless<units::angular_velocity::radians_per_second_t>();
    VectorN_CanCalculateDotProductDimensionless<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanCalculateDotProductDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanCalculateDotProductDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanCalculateDotProductDimensionless<units::force::newton_t>();
    VectorN_CanCalculateDotProductDimensionless<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanDivideByScalar()
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
                units::inverse<units::length::meter>
            >
        >,
        SIZE
    > vr = v / val;

    EXPECT_NEAR(vr(0)(), 0.5, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 1.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 1.5, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanDivideByScalar)
{
    VectorN_CanDivideByScalar<units::length::meter_t>();
    VectorN_CanDivideByScalar<units::velocity::meters_per_second_t>();
    VectorN_CanDivideByScalar<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanDivideByScalar<units::angular_velocity::radians_per_second_t>();
    VectorN_CanDivideByScalar<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanDivideByScalar<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanDivideByScalar<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanDivideByScalar<units::force::newton_t>();
    VectorN_CanDivideByScalar<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanDivideByScalarDimensionlessVector)
{
    mc::VectorN<double,SIZE> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    constexpr units::time::second_t val = 2.0_s;
    mc::VectorN<units::frequency::hertz_t,SIZE> vr = v / val;

    EXPECT_NEAR(vr(0)(), 0.5, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 1.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 1.5, TOLERANCE);
}

template <typename T>
void VectorN_CanDivideByScalarDimensionless()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    double val = 2.0;

    mc::VectorN<T,SIZE> vr = v / val;

    EXPECT_NEAR(vr(0)(), 0.5, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 1.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 1.5, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanDivideByScalarDimensionless)
{
    VectorN_CanDivideByScalarDimensionless<units::length::meter_t>();
    VectorN_CanDivideByScalarDimensionless<units::velocity::meters_per_second_t>();
    VectorN_CanDivideByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanDivideByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
    VectorN_CanDivideByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanDivideByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanDivideByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanDivideByScalarDimensionless<units::force::newton_t>();
    VectorN_CanDivideByScalarDimensionless<units::torque::newton_meter_t>();
}

template <typename T1, typename T2>
void VectorN_CanAssignDifferentType()
{
    mc::VectorN<T1,SIZE> v1;
    mc::VectorN<T2,SIZE> v2;

    v1(0) = T1{1};
    v1(1) = T1{2};
    v1(2) = T1{3};

    v2(0) = T1{4};
    v2(1) = T1{5};
    v2(2) = T1{6};

    v1 = v2;

    EXPECT_NEAR(v1(0)(), 4.0, TOLERANCE);
    EXPECT_NEAR(v1(1)(), 5.0, TOLERANCE);
    EXPECT_NEAR(v1(2)(), 6.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanAssignDifferentType)
{
    VectorN_CanAssignDifferentType<
        units::length::meter_t,
        units::length::foot_t
    >();
    VectorN_CanAssignDifferentType<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t
    >();
    VectorN_CanAssignDifferentType<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t
    >();
    VectorN_CanAssignDifferentType<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t
    >();
    VectorN_CanAssignDifferentType<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t
    >();
    VectorN_CanAssignDifferentType<
        units::force::newton_t,
        units::force::pound_t
    >();
    VectorN_CanAssignDifferentType<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t
    >();
}

template <typename T>
void VectorN_CanUnaryAdd()
{
    mc::VectorN<T,SIZE> v0;
    v0(0) = T{1};
    v0(1) = T{2};
    v0(2) = T{3};

    mc::VectorN<T,SIZE> v1;
    v1(0) = T{2};
    v1(1) = T{3};
    v1(2) = T{4};

    v0 += v1;

    EXPECT_NEAR(v0(0)(), 3.0, TOLERANCE);
    EXPECT_NEAR(v0(1)(), 5.0, TOLERANCE);
    EXPECT_NEAR(v0(2)(), 7.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanUnaryAdd)
{
    VectorN_CanUnaryAdd<units::length::meter_t>();
    VectorN_CanUnaryAdd<units::velocity::meters_per_second_t>();
    VectorN_CanUnaryAdd<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanUnaryAdd<units::angular_velocity::radians_per_second_t>();
    VectorN_CanUnaryAdd<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanUnaryAdd<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanUnaryAdd<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanUnaryAdd<units::force::newton_t>();
    VectorN_CanUnaryAdd<units::torque::newton_meter_t>();
}

template <typename T1, typename T2>
void VectorN_CanUnaryAddDifferentType()
{
    mc::VectorN<T1,SIZE> v0;
    v0(0) = T1{1};
    v0(1) = T1{2};
    v0(2) = T1{3};

    mc::VectorN<T2,SIZE> v1;
    v1(0) = T1{2};
    v1(1) = T1{3};
    v1(2) = T1{4};

    v0 += v1;

    EXPECT_NEAR(v0(0)(), 3.0, TOLERANCE);
    EXPECT_NEAR(v0(1)(), 5.0, TOLERANCE);
    EXPECT_NEAR(v0(2)(), 7.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanUnaryAddDifferentType)
{
    VectorN_CanUnaryAddDifferentType<
        units::length::meter_t,
        units::length::foot_t
    >();

    VectorN_CanUnaryAddDifferentType<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t
    >();

    VectorN_CanUnaryAddDifferentType<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t
    >();

    VectorN_CanUnaryAddDifferentType<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t
    >();

    VectorN_CanUnaryAddDifferentType<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t
    >();

    VectorN_CanUnaryAddDifferentType<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t
    >();

    VectorN_CanUnaryAddDifferentType<
        units::force::newton_t,
        units::force::pound_t
    >();

    VectorN_CanUnaryAddDifferentType<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t
    >();
}

template <typename T>
void VectorN_CanUnarySubtract()
{
    mc::VectorN<T,SIZE> v0;
    v0(0) = T{3};
    v0(1) = T{5};
    v0(2) = T{7};

    mc::VectorN<T,SIZE> v1;
    v1(0) = T{2};
    v1(1) = T{3};
    v1(2) = T{4};

    v0 -= v1;

    EXPECT_NEAR(v0(0)(), 1.0, TOLERANCE);
    EXPECT_NEAR(v0(1)(), 2.0, TOLERANCE);
    EXPECT_NEAR(v0(2)(), 3.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanUnarySubtract)
{
    VectorN_CanUnarySubtract<units::length::meter_t>();
    VectorN_CanUnarySubtract<units::velocity::meters_per_second_t>();
    VectorN_CanUnarySubtract<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanUnarySubtract<units::angular_velocity::radians_per_second_t>();
    VectorN_CanUnarySubtract<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanUnarySubtract<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanUnarySubtract<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanUnarySubtract<units::force::newton_t>();
    VectorN_CanUnarySubtract<units::torque::newton_meter_t>();
}

template <typename T1, typename T2>
void VectorN_CanUnarySubtractDifferentTypes()
{
    mc::VectorN<T1,SIZE> v0;
    v0(0) = T1{3};
    v0(1) = T1{5};
    v0(2) = T1{7};

    mc::VectorN<T2,SIZE> v1;
    v1(0) = T1{2};
    v1(1) = T1{3};
    v1(2) = T1{4};

    v0 -= v1;

    EXPECT_NEAR(v0(0)(), 1.0, TOLERANCE);
    EXPECT_NEAR(v0(1)(), 2.0, TOLERANCE);
    EXPECT_NEAR(v0(2)(), 3.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanUnarySubtractDifferentTypes)
{
    VectorN_CanUnarySubtractDifferentTypes<
        units::length::meter_t,
        units::length::foot_t
    >();

    VectorN_CanUnarySubtractDifferentTypes<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t
    >();

    VectorN_CanUnarySubtractDifferentTypes<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t
    >();

    VectorN_CanUnarySubtractDifferentTypes<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t
    >();

    VectorN_CanUnarySubtractDifferentTypes<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t
    >();

    VectorN_CanUnarySubtractDifferentTypes<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t
    >();

    VectorN_CanUnarySubtractDifferentTypes<
        units::force::newton_t,
        units::force::pound_t
    >();

    VectorN_CanUnarySubtractDifferentTypes<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t
    >();
}

template <typename T>
void VectorN_CanUnaryMultiplyByScalarDimensionless()
{
    mc::VectorN<T,SIZE> v0;
    v0(0) = T{2};
    v0(1) = T{4};
    v0(2) = T{6};

    v0 *= 0.5;

    EXPECT_NEAR(v0(0)(), 1.0, TOLERANCE);
    EXPECT_NEAR(v0(1)(), 2.0, TOLERANCE);
    EXPECT_NEAR(v0(2)(), 3.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanUnaryMultiplyByScalarDimensionless)
{
    VectorN_CanUnaryMultiplyByScalarDimensionless<units::length::meter_t>();
    VectorN_CanUnaryMultiplyByScalarDimensionless<units::velocity::meters_per_second_t>();
    VectorN_CanUnaryMultiplyByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanUnaryMultiplyByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
    VectorN_CanUnaryMultiplyByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanUnaryMultiplyByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanUnaryMultiplyByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanUnaryMultiplyByScalarDimensionless<units::force::newton_t>();
    VectorN_CanUnaryMultiplyByScalarDimensionless<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanUnaryDivideByScalarDimensionless()
{
    mc::VectorN<T,SIZE> v0;
    v0(0) = T{2};
    v0(1) = T{4};
    v0(2) = T{6};

    v0 /= 2.0;

    EXPECT_NEAR(v0(0)(), 1.0, TOLERANCE);
    EXPECT_NEAR(v0(1)(), 2.0, TOLERANCE);
    EXPECT_NEAR(v0(2)(), 3.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanUnaryDivideByScalarDimensionless)
{
    VectorN_CanUnaryDivideByScalarDimensionless<units::length::meter_t>();
    VectorN_CanUnaryDivideByScalarDimensionless<units::velocity::meters_per_second_t>();
    VectorN_CanUnaryDivideByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanUnaryDivideByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
    VectorN_CanUnaryDivideByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanUnaryDivideByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanUnaryDivideByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanUnaryDivideByScalarDimensionless<units::force::newton_t>();
    VectorN_CanUnaryDivideByScalarDimensionless<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanCompare()
{
    mc::VectorN<T,SIZE> v1;
    mc::VectorN<T,SIZE> v2;
    v1(0) = v2(0) = T{1};
    v1(1) = v2(1) = T{2};
    v1(2) = v2(2) = T{3};

    mc::VectorN<T,SIZE> v3;
    v3(0) = T{4};
    v3(1) = T{5};
    v3(2) = T{6};

    EXPECT_TRUE(v1 == v2);
    EXPECT_TRUE(v1 != v3);
    EXPECT_FALSE(v1 == v3);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(TestVectorNWithUnits, CanCompare)
{
    VectorN_CanCompare<units::length::meter_t>();
    VectorN_CanCompare<units::velocity::meters_per_second_t>();
    VectorN_CanCompare<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanCompare<units::angular_velocity::radians_per_second_t>();
    VectorN_CanCompare<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanCompare<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanCompare<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanCompare<units::force::newton_t>();
    VectorN_CanCompare<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanMultiplyScalarByVector()
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
    > vr = val * v;

    EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanMultiplyScalarByVector)
{
    VectorN_CanMultiplyScalarByVector<units::length::meter_t>();
    VectorN_CanMultiplyScalarByVector<units::velocity::meters_per_second_t>();
    VectorN_CanMultiplyScalarByVector<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanMultiplyScalarByVector<units::force::newton_t>();
    VectorN_CanMultiplyScalarByVector<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanMultiplyTimeScalarByVector()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    units::time::second_t val = 2.0_s;

    mc::VectorN<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::time::second
            >
        >,
        SIZE
    > vr = val * v;

    EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanMultiplyTimeScalarByVector)
{
    VectorN_CanMultiplyTimeScalarByVector<units::length::meter_t>();
    VectorN_CanMultiplyTimeScalarByVector<units::velocity::meters_per_second_t>();
    VectorN_CanMultiplyTimeScalarByVector<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanMultiplyTimeScalarByVector<units::angular_velocity::radians_per_second_t>();
    VectorN_CanMultiplyTimeScalarByVector<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanMultiplyTimeScalarByVector<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanMultiplyTimeScalarByVector<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanMultiplyTimeScalarByVector<units::force::newton_t>();
    VectorN_CanMultiplyTimeScalarByVector<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanMultiplyAngularVelScalarByVector()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    units::angular_velocity::degrees_per_second_t val = 2.0_rad_per_s;

    mc::VectorN<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_t>::unit_type
            >
        >,
        SIZE
    > vr = val * v;

    EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanMultiplyAngularVelScalarByVector)
{
    VectorN_CanMultiplyAngularVelScalarByVector<units::length::meter_t>();
    VectorN_CanMultiplyAngularVelScalarByVector<units::velocity::meters_per_second_t>();
    VectorN_CanMultiplyAngularVelScalarByVector<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanMultiplyAngularVelScalarByVector<units::force::newton_t>();
    VectorN_CanMultiplyAngularVelScalarByVector<units::torque::newton_meter_t>();
}

template <typename T>
void VectorN_CanMultiplyAngularAccScalarByVector()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    units::angular_acceleration::degrees_per_second_squared_t val = 2.0_rad_per_s_sq;

    mc::VectorN<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_squared_t>::unit_type
            >
        >,
        SIZE
    > vr = val * v;

    EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanMultiplyAngularAccScalarByVector)
{
    VectorN_CanMultiplyAngularAccScalarByVector<units::length::meter_t>();
    VectorN_CanMultiplyAngularAccScalarByVector<units::velocity::meters_per_second_t>();
    VectorN_CanMultiplyAngularAccScalarByVector<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanMultiplyAngularAccScalarByVector<units::force::newton_t>();
    VectorN_CanMultiplyAngularAccScalarByVector<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanMultiplyScalarByDimensionlessVector)
{
    mc::VectorN<double,SIZE> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<units::length::meter_t,SIZE> vr = 2.0_m * v;

    EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
}

template <typename T>
void VectorN_CanMultiplyDimensionlessScalarByVector()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    mc::VectorN<T,SIZE> vr = 2.0 * v;

    EXPECT_NEAR(vr(0)(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr(1)(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr(2)(), 6.0, TOLERANCE);
}

TEST_F(TestVectorNWithUnits, CanMultiplyDimensionlessScalarByVector)
{
    VectorN_CanMultiplyDimensionlessScalarByVector<units::length::meter_t>();
    VectorN_CanMultiplyDimensionlessScalarByVector<units::velocity::meters_per_second_t>();
    VectorN_CanMultiplyDimensionlessScalarByVector<units::acceleration::meters_per_second_squared_t>();
    VectorN_CanMultiplyDimensionlessScalarByVector<units::angular_velocity::radians_per_second_t>();
    VectorN_CanMultiplyDimensionlessScalarByVector<units::angular_velocity::degrees_per_second_t>();
    VectorN_CanMultiplyDimensionlessScalarByVector<units::angular_acceleration::radians_per_second_squared_t>();
    VectorN_CanMultiplyDimensionlessScalarByVector<units::angular_acceleration::degrees_per_second_squared_t>();
    VectorN_CanMultiplyDimensionlessScalarByVector<units::force::newton_t>();
    VectorN_CanMultiplyDimensionlessScalarByVector<units::torque::newton_meter_t>();
}