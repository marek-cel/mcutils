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

namespace test {

template <typename T>
void CanInstantiate()
{
    mc::VectorN<T,SIZE> v1;

    EXPECT_NEAR(v1(0)(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1(1)(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1(2)(), 0.0, TOLERANCE);
}

template <typename T1, typename T2>
void CanInstantiateFromDifferentTypes()
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

template <typename T>
void CanValidate()
{
    mc::VectorN<T,SIZE> v;

    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    EXPECT_TRUE(v.isValid());

    v(0) = T{std::numeric_limits<double>::quiet_NaN()};
    EXPECT_FALSE(v.isValid());
}

template <typename T>
void CanGetLengthSquared()
{
    mc::VectorN<T,SIZE> v;

    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    // 1^2 + 2^2 + 3^2 = 1 + 4 + 9 = 14
    EXPECT_DOUBLE_EQ(v.getLengthSq()(), 14.0);
}

template <typename T>
void CanGetLength()
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

template <typename T>
void CanGetNormalized()
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

template <typename T>
void CanGetStdArray()
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

template <typename T>
void CanGetStdVector()
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

template <typename T>
void CanSetFromStdArray()
{
    std::array<T, SIZE> x { T{1}, T{2}, T{3} };
    mc::VectorN<T,SIZE> v;
    v.setFromStdArray(x);

    EXPECT_NEAR(v(0)(), 1.0, TOLERANCE);
    EXPECT_NEAR(v(1)(), 2.0, TOLERANCE);
    EXPECT_NEAR(v(2)(), 3.0, TOLERANCE);
}

template <typename T>
void CanSetFromStdVector()
{
    std::vector<T> x { T{1}, T{2}, T{3} };
    mc::VectorN<T,SIZE> v;
    v.setFromStdVector(x);

    EXPECT_NEAR(v(0)(), 1.0, TOLERANCE);
    EXPECT_NEAR(v(1)(), 2.0, TOLERANCE);
    EXPECT_NEAR(v(2)(), 3.0, TOLERANCE);
}

template <typename T>
void CanSetFromString()
{
    char str[] = { " 1.0  2.0  3.0 " };
    mc::VectorN<T,SIZE> v;
    v.setFromString(str);

    EXPECT_DOUBLE_EQ(v(0)(), 1.0);
    EXPECT_DOUBLE_EQ(v(1)(), 2.0);
    EXPECT_DOUBLE_EQ(v(2)(), 3.0);
}

template <typename T>
void CanSetFromInvalidString()
{
    char str[] = { "lorem ipsum" };
    mc::VectorN<T,SIZE> v;
    v.setFromString(str);
    EXPECT_FALSE(v.isValid());
}

template <typename T>
void CanSwapRows()
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

template <typename T>
void CanConvertToString()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    std::stringstream ss;
    ss << T{1} << "\t" << T{2} << "\t" << T{3};

    EXPECT_STREQ(v.toString().c_str(), ss.str().c_str());
}

template <typename T>
void CanZeroize()
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

template <typename T>
void CanCastToDimensionless()
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

template <typename T1, typename T2>
void CanCastToDifferentUnit()
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

template <typename T>
void CanAddSameTypes()
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

template <typename T1, typename T2>
void CanAddDifferentTypes()
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

template <typename T>
void CanNegate()
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

template <typename T>
void CanSubtractSameTypes()
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

template <typename T1, typename T2>
void CanSubtractDifferentTypes()
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

template <typename T>
void CanMultiplyByDouble()
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

template <typename T>
void CanMultiplyDimensionlessVectorByScalar()
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

template <typename T>
void CanMultiplyByScalar()
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

template <typename T>
void CanMultiplyByTimeScalar()
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

template <typename T>
void CanCalculateDotProduct()
{
    mc::VectorN<T,SIZE> v;
    v(0) = T{1};
    v(1) = T{2};
    v(2) = T{3};

    using ResultType = typename units::unit_t<units::squared<typename units::traits::unit_t_traits<T>::unit_type>>;

    ResultType s = v * v;

    EXPECT_NEAR(s(), 14.0, TOLERANCE);
}

template <typename T>
void CanCalculateDotProductDimensionless()
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

template <typename T>
void CanDivideByScalar()
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

template <typename T>
void CanDivideByScalarDimensionless()
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

template <typename T1, typename T2>
void CanAssignDifferentTypes()
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

template <typename T>
void CanUnaryAdd()
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

template <typename T1, typename T2>
void CanUnaryAddDifferentTypes()
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

template <typename T>
void CanUnarySubtract()
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

template <typename T1, typename T2>
void CanUnarySubtractDifferentTypes()
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

template <typename T>
void CanUnaryMultiplyByScalarDimensionless()
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

template <typename T>
void CanCompare()
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

template <typename T>
void CanUnaryDivideByScalarDimensionless()
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

template <typename T>
void CanMultiplyScalarByVector()
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

template <typename T>
void CanMultiplyTimeScalarByVector()
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

template <typename T>
void CanMultiplyDimensionlessScalarByVector()
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

} // namespace test

TEST_F(TestVectorNWithUnits, CanInstantiate)
{
    test::CanInstantiate<units::length::meter_t>();
    test::CanInstantiate<units::velocity::meters_per_second_t>();
    test::CanInstantiate<units::acceleration::meters_per_second_squared_t>();
    test::CanInstantiate<units::angular_velocity::radians_per_second_t>();
    test::CanInstantiate<units::angular_velocity::degrees_per_second_t>();
    test::CanInstantiate<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanInstantiate<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanInstantiate<units::force::newton_t>();
    test::CanInstantiate<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanInstantiateFromDifferentTypes)
{
    test::CanInstantiateFromDifferentTypes<
        units::length::meter_t,
        units::length::foot_t
    >();
    test::CanInstantiateFromDifferentTypes<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t
    >();
    test::CanInstantiateFromDifferentTypes<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t
    >();
    test::CanInstantiateFromDifferentTypes<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t
    >();
    test::CanInstantiateFromDifferentTypes<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t
    >();
    test::CanInstantiateFromDifferentTypes<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t
    >();
    test::CanInstantiateFromDifferentTypes<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t
    >();
    test::CanInstantiateFromDifferentTypes<
        units::force::newton_t,
        units::force::pound_t
    >();
    test::CanInstantiateFromDifferentTypes<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t
    >();     
}

TEST_F(TestVectorNWithUnits, CanValidate)
{
    test::CanValidate<units::length::meter_t>();
    test::CanValidate<units::velocity::meters_per_second_t>();
    test::CanValidate<units::acceleration::meters_per_second_squared_t>();
    test::CanValidate<units::angular_velocity::radians_per_second_t>();
    test::CanValidate<units::angular_velocity::degrees_per_second_t>();
    test::CanValidate<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanValidate<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanValidate<units::force::newton_t>();
    test::CanValidate<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanGetLengthSquared)
{
    test::CanGetLengthSquared<units::length::meter_t>();
    test::CanGetLengthSquared<units::velocity::meters_per_second_t>();
    test::CanGetLengthSquared<units::acceleration::meters_per_second_squared_t>();
    test::CanGetLengthSquared<units::angular_velocity::radians_per_second_t>();
    test::CanGetLengthSquared<units::angular_velocity::degrees_per_second_t>();
    test::CanGetLengthSquared<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanGetLengthSquared<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanGetLengthSquared<units::force::newton_t>();
    test::CanGetLengthSquared<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanGetLength)
{
    test::CanGetLength<units::length::meter_t>();
    test::CanGetLength<units::velocity::meters_per_second_t>();
    test::CanGetLength<units::acceleration::meters_per_second_squared_t>();
    test::CanGetLength<units::angular_velocity::radians_per_second_t>();
    test::CanGetLength<units::angular_velocity::degrees_per_second_t>();
    test::CanGetLength<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanGetLength<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanGetLength<units::force::newton_t>();
    test::CanGetLength<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanGetNormalized)
{
    test::CanGetNormalized<units::length::meter_t>();
    test::CanGetNormalized<units::velocity::meters_per_second_t>();
    test::CanGetNormalized<units::acceleration::meters_per_second_squared_t>();
    test::CanGetNormalized<units::angular_velocity::radians_per_second_t>();
    test::CanGetNormalized<units::angular_velocity::degrees_per_second_t>();
    test::CanGetNormalized<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanGetNormalized<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanGetNormalized<units::force::newton_t>();
    test::CanGetNormalized<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanGetStdArray)
{
    test::CanGetStdArray<units::length::meter_t>();
    test::CanGetStdArray<units::velocity::meters_per_second_t>();
    test::CanGetStdArray<units::acceleration::meters_per_second_squared_t>();
    test::CanGetStdArray<units::angular_velocity::radians_per_second_t>();
    test::CanGetStdArray<units::angular_velocity::degrees_per_second_t>();
    test::CanGetStdArray<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanGetStdArray<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanGetStdArray<units::force::newton_t>();
    test::CanGetStdArray<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanGetStdVector)
{
    test::CanGetStdVector<units::length::meter_t>();
    test::CanGetStdVector<units::velocity::meters_per_second_t>();
    test::CanGetStdVector<units::acceleration::meters_per_second_squared_t>();
    test::CanGetStdVector<units::angular_velocity::radians_per_second_t>();
    test::CanGetStdVector<units::angular_velocity::degrees_per_second_t>();
    test::CanGetStdVector<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanGetStdVector<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanGetStdVector<units::force::newton_t>();
    test::CanGetStdVector<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanSetFromStdArray)
{
    test::CanSetFromStdArray<units::length::meter_t>();
    test::CanSetFromStdArray<units::velocity::meters_per_second_t>();
    test::CanSetFromStdArray<units::acceleration::meters_per_second_squared_t>();
    test::CanSetFromStdArray<units::angular_velocity::radians_per_second_t>();
    test::CanSetFromStdArray<units::angular_velocity::degrees_per_second_t>();
    test::CanSetFromStdArray<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanSetFromStdArray<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanSetFromStdArray<units::force::newton_t>();
    test::CanSetFromStdArray<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanSetFromStdVector)
{
    test::CanSetFromStdVector<units::length::meter_t>();
    test::CanSetFromStdVector<units::velocity::meters_per_second_t>();
    test::CanSetFromStdVector<units::acceleration::meters_per_second_squared_t>();
    test::CanSetFromStdVector<units::angular_velocity::radians_per_second_t>();
    test::CanSetFromStdVector<units::angular_velocity::degrees_per_second_t>();
    test::CanSetFromStdVector<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanSetFromStdVector<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanSetFromStdVector<units::force::newton_t>();
    test::CanSetFromStdVector<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanSetFromString)
{
    test::CanSetFromString<units::length::meter_t>();
    test::CanSetFromString<units::velocity::meters_per_second_t>();
    test::CanSetFromString<units::acceleration::meters_per_second_squared_t>();
    test::CanSetFromString<units::angular_velocity::radians_per_second_t>();
    test::CanSetFromString<units::angular_velocity::degrees_per_second_t>();
    test::CanSetFromString<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanSetFromString<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanSetFromString<units::force::newton_t>();
    test::CanSetFromString<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanSetFromInvalidString)
{
    test::CanSetFromInvalidString<units::length::meter_t>();
    test::CanSetFromInvalidString<units::velocity::meters_per_second_t>();
    test::CanSetFromInvalidString<units::acceleration::meters_per_second_squared_t>();
    test::CanSetFromInvalidString<units::angular_velocity::radians_per_second_t>();
    test::CanSetFromInvalidString<units::angular_velocity::degrees_per_second_t>();
    test::CanSetFromInvalidString<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanSetFromInvalidString<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanSetFromInvalidString<units::force::newton_t>();
    test::CanSetFromInvalidString<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanSwapRows)
{
    test::CanSwapRows<units::length::meter_t>();
    test::CanSwapRows<units::velocity::meters_per_second_t>();
    test::CanSwapRows<units::acceleration::meters_per_second_squared_t>();
    test::CanSwapRows<units::angular_velocity::radians_per_second_t>();
    test::CanSwapRows<units::angular_velocity::degrees_per_second_t>();
    test::CanSwapRows<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanSwapRows<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanSwapRows<units::force::newton_t>();
    test::CanSwapRows<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanConvertToString)
{
    test::CanConvertToString<units::length::meter_t>();
    test::CanConvertToString<units::velocity::meters_per_second_t>();
    test::CanConvertToString<units::acceleration::meters_per_second_squared_t>();
    test::CanConvertToString<units::angular_velocity::radians_per_second_t>();
    test::CanConvertToString<units::angular_velocity::degrees_per_second_t>();
    test::CanConvertToString<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanConvertToString<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanConvertToString<units::force::newton_t>();
    test::CanConvertToString<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanZeroize)
{
    test::CanZeroize<units::length::meter_t>();
    test::CanZeroize<units::velocity::meters_per_second_t>();
    test::CanZeroize<units::acceleration::meters_per_second_squared_t>();
    test::CanZeroize<units::angular_velocity::radians_per_second_t>();
    test::CanZeroize<units::angular_velocity::degrees_per_second_t>();
    test::CanZeroize<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanZeroize<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanZeroize<units::force::newton_t>();
    test::CanZeroize<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanGetStripped)
{
    mc::VectorN<units::angular_velocity::radians_per_second_t,SIZE> omega;
    mc::VectorN<units::inverted::per_second_t,SIZE> omega_stripped = omega.getStripped();

    mc::VectorN<units::angular_acceleration::radians_per_second_squared_t,SIZE> epsilon;
    mc::VectorN<units::inverted::per_second_squared_t,SIZE> epsilon_stripped = epsilon.getStripped();
}

TEST_F(TestVectorNWithUnits, CanCastToDimensionless)
{
    test::CanCastToDimensionless<units::length::meter_t>();
    test::CanCastToDimensionless<units::velocity::meters_per_second_t>();
    test::CanCastToDimensionless<units::acceleration::meters_per_second_squared_t>();
    test::CanCastToDimensionless<units::angular_velocity::radians_per_second_t>();
    test::CanCastToDimensionless<units::angular_velocity::degrees_per_second_t>();
    test::CanCastToDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanCastToDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanCastToDimensionless<units::force::newton_t>();
    test::CanCastToDimensionless<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanCastToDifferentUnit)
{
    test::CanCastToDifferentUnit<
        units::length::meter_t,
        units::length::foot_t
    >();
    test::CanCastToDifferentUnit<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t
    >();
    test::CanCastToDifferentUnit<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t
    >();
    test::CanCastToDifferentUnit<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t
    >();
    test::CanCastToDifferentUnit<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t
    >();
    test::CanCastToDifferentUnit<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t
    >();
    test::CanCastToDifferentUnit<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t
    >();
    test::CanCastToDifferentUnit<
        units::force::newton_t,
        units::force::pound_t
    >();
    test::CanCastToDifferentUnit<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t
    >();  
}

TEST_F(TestVectorNWithUnits, CanAddSameTypes)
{
    test::CanAddSameTypes<units::length::meter_t>();
    test::CanAddSameTypes<units::velocity::meters_per_second_t>();
    test::CanAddSameTypes<units::acceleration::meters_per_second_squared_t>();
    test::CanAddSameTypes<units::angular_velocity::radians_per_second_t>();
    test::CanAddSameTypes<units::angular_velocity::degrees_per_second_t>();
    test::CanAddSameTypes<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanAddSameTypes<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanAddSameTypes<units::force::newton_t>();
    test::CanAddSameTypes<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanAddDifferentTypes)
{
    test::CanAddDifferentTypes<
        units::length::meter_t,
        units::length::foot_t
    >();
    test::CanAddDifferentTypes<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t
    >();
    test::CanAddDifferentTypes<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t
    >();
    test::CanAddDifferentTypes<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t
    >();
    test::CanAddDifferentTypes<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t
    >();
    test::CanAddDifferentTypes<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t
    >();
    test::CanAddDifferentTypes<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t
    >();
    test::CanAddDifferentTypes<
        units::force::newton_t,
        units::force::pound_t
    >();
    test::CanAddDifferentTypes<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t
    >();
}

TEST_F(TestVectorNWithUnits, CanNegate)
{
    test::CanNegate<units::length::meter_t>();
    test::CanNegate<units::velocity::meters_per_second_t>();
    test::CanNegate<units::acceleration::meters_per_second_squared_t>();
    test::CanNegate<units::angular_velocity::radians_per_second_t>();
    test::CanNegate<units::angular_velocity::degrees_per_second_t>();
    test::CanNegate<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanNegate<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanNegate<units::force::newton_t>();
    test::CanNegate<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanSubtractSameTypes)
{
    test::CanSubtractSameTypes<units::length::meter_t>();
    test::CanSubtractSameTypes<units::velocity::meters_per_second_t>();
    test::CanSubtractSameTypes<units::acceleration::meters_per_second_squared_t>();
    test::CanSubtractSameTypes<units::angular_velocity::radians_per_second_t>();
    test::CanSubtractSameTypes<units::angular_velocity::degrees_per_second_t>();
    test::CanSubtractSameTypes<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanSubtractSameTypes<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanSubtractSameTypes<units::force::newton_t>();
    test::CanSubtractSameTypes<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanSubtractDifferentTypes)
{
    test::CanSubtractDifferentTypes<
        units::length::meter_t,
        units::length::foot_t
    >();
    test::CanSubtractDifferentTypes<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t
    >();
    test::CanSubtractDifferentTypes<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t
    >();
    test::CanSubtractDifferentTypes<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t
    >();
    test::CanSubtractDifferentTypes<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t
    >();
    test::CanSubtractDifferentTypes<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t
    >();
    test::CanSubtractDifferentTypes<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t
    >();
    test::CanSubtractDifferentTypes<
        units::force::newton_t,
        units::force::pound_t
    >();
    test::CanSubtractDifferentTypes<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t
    >();
}

TEST_F(TestVectorNWithUnits, CanMultiplyByDouble)
{
    test::CanMultiplyByDouble<units::length::meter_t>();
    test::CanMultiplyByDouble<units::velocity::meters_per_second_t>();
    test::CanMultiplyByDouble<units::acceleration::meters_per_second_squared_t>();
    test::CanMultiplyByDouble<units::angular_velocity::radians_per_second_t>();
    test::CanMultiplyByDouble<units::angular_velocity::degrees_per_second_t>();
    test::CanMultiplyByDouble<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanMultiplyByDouble<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanMultiplyByDouble<units::force::newton_t>();
    test::CanMultiplyByDouble<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanMultiplyDimensionlessVectorByScalar)
{
    test::CanMultiplyDimensionlessVectorByScalar<units::length::meter_t>();
    test::CanMultiplyDimensionlessVectorByScalar<units::velocity::meters_per_second_t>();
    test::CanMultiplyDimensionlessVectorByScalar<units::acceleration::meters_per_second_squared_t>();
    test::CanMultiplyDimensionlessVectorByScalar<units::angular_velocity::radians_per_second_t>();
    test::CanMultiplyDimensionlessVectorByScalar<units::angular_velocity::degrees_per_second_t>();
    test::CanMultiplyDimensionlessVectorByScalar<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanMultiplyDimensionlessVectorByScalar<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanMultiplyDimensionlessVectorByScalar<units::force::newton_t>();
    test::CanMultiplyDimensionlessVectorByScalar<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanMultiplyByScalar)
{
    test::CanMultiplyByScalar<units::length::meter_t>();
    test::CanMultiplyByScalar<units::velocity::meters_per_second_t>();
    test::CanMultiplyByScalar<units::acceleration::meters_per_second_squared_t>();
    test::CanMultiplyByScalar<units::force::newton_t>();
    test::CanMultiplyByScalar<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanMultiplyByTimeScalar)
{
    test::CanMultiplyByTimeScalar<units::length::meter_t>();
    test::CanMultiplyByTimeScalar<units::velocity::meters_per_second_t>();
    test::CanMultiplyByTimeScalar<units::acceleration::meters_per_second_squared_t>();
    test::CanMultiplyByTimeScalar<units::angular_velocity::radians_per_second_t>();
    test::CanMultiplyByTimeScalar<units::angular_velocity::degrees_per_second_t>();
    test::CanMultiplyByTimeScalar<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanMultiplyByTimeScalar<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanMultiplyByTimeScalar<units::force::newton_t>();
    test::CanMultiplyByTimeScalar<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanCalculateDotProduct)
{
    test::CanCalculateDotProduct<units::length::meter_t>();
    test::CanCalculateDotProduct<units::velocity::meters_per_second_t>();
    test::CanCalculateDotProduct<units::acceleration::meters_per_second_squared_t>();
    test::CanCalculateDotProduct<units::force::newton_t>();
    test::CanCalculateDotProduct<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanCalculateDotProductDimensionless)
{
    test::CanCalculateDotProductDimensionless<units::length::meter_t>();
    test::CanCalculateDotProductDimensionless<units::velocity::meters_per_second_t>();
    test::CanCalculateDotProductDimensionless<units::acceleration::meters_per_second_squared_t>();
    test::CanCalculateDotProductDimensionless<units::angular_velocity::radians_per_second_t>();
    test::CanCalculateDotProductDimensionless<units::angular_velocity::degrees_per_second_t>();
    test::CanCalculateDotProductDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanCalculateDotProductDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanCalculateDotProductDimensionless<units::force::newton_t>();
    test::CanCalculateDotProductDimensionless<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanDivideByScalar)
{
    test::CanDivideByScalar<units::length::meter_t>();
    test::CanDivideByScalar<units::velocity::meters_per_second_t>();
    test::CanDivideByScalar<units::acceleration::meters_per_second_squared_t>();
    test::CanDivideByScalar<units::angular_velocity::radians_per_second_t>();
    test::CanDivideByScalar<units::angular_velocity::degrees_per_second_t>();
    test::CanDivideByScalar<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanDivideByScalar<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanDivideByScalar<units::force::newton_t>();
    test::CanDivideByScalar<units::torque::newton_meter_t>();
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

TEST_F(TestVectorNWithUnits, CanDivideByScalarDimensionless)
{
    test::CanDivideByScalarDimensionless<units::length::meter_t>();
    test::CanDivideByScalarDimensionless<units::velocity::meters_per_second_t>();
    test::CanDivideByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
    test::CanDivideByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
    test::CanDivideByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
    test::CanDivideByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanDivideByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanDivideByScalarDimensionless<units::force::newton_t>();
    test::CanDivideByScalarDimensionless<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanAssignDifferentTypes)
{
    test::CanAssignDifferentTypes<
        units::length::meter_t,
        units::length::foot_t
    >();
    test::CanAssignDifferentTypes<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t
    >();
    test::CanAssignDifferentTypes<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t
    >();
    test::CanAssignDifferentTypes<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t
    >();
    test::CanAssignDifferentTypes<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t
    >();
    test::CanAssignDifferentTypes<
        units::force::newton_t,
        units::force::pound_t
    >();
    test::CanAssignDifferentTypes<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t
    >();
}

TEST_F(TestVectorNWithUnits, CanUnaryAdd)
{
    test::CanUnaryAdd<units::length::meter_t>();
    test::CanUnaryAdd<units::velocity::meters_per_second_t>();
    test::CanUnaryAdd<units::acceleration::meters_per_second_squared_t>();
    test::CanUnaryAdd<units::angular_velocity::radians_per_second_t>();
    test::CanUnaryAdd<units::angular_velocity::degrees_per_second_t>();
    test::CanUnaryAdd<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanUnaryAdd<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanUnaryAdd<units::force::newton_t>();
    test::CanUnaryAdd<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanUnaryAddDifferentTypes)
{
    test::CanUnaryAddDifferentTypes<
        units::length::meter_t,
        units::length::foot_t
    >();

    test::CanUnaryAddDifferentTypes<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t
    >();

    test::CanUnaryAddDifferentTypes<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t
    >();

    test::CanUnaryAddDifferentTypes<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t
    >();

    test::CanUnaryAddDifferentTypes<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t
    >();

    test::CanUnaryAddDifferentTypes<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t
    >();

    test::CanUnaryAddDifferentTypes<
        units::force::newton_t,
        units::force::pound_t
    >();

    test::CanUnaryAddDifferentTypes<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t
    >();
}

TEST_F(TestVectorNWithUnits, CanUnarySubtract)
{
    test::CanUnarySubtract<units::length::meter_t>();
    test::CanUnarySubtract<units::velocity::meters_per_second_t>();
    test::CanUnarySubtract<units::acceleration::meters_per_second_squared_t>();
    test::CanUnarySubtract<units::angular_velocity::radians_per_second_t>();
    test::CanUnarySubtract<units::angular_velocity::degrees_per_second_t>();
    test::CanUnarySubtract<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanUnarySubtract<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanUnarySubtract<units::force::newton_t>();
    test::CanUnarySubtract<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanUnarySubtractDifferentTypes)
{
    test::CanUnarySubtractDifferentTypes<
        units::length::meter_t,
        units::length::foot_t
    >();

    test::CanUnarySubtractDifferentTypes<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t
    >();

    test::CanUnarySubtractDifferentTypes<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t
    >();

    test::CanUnarySubtractDifferentTypes<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t
    >();

    test::CanUnarySubtractDifferentTypes<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t
    >();

    test::CanUnarySubtractDifferentTypes<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t
    >();

    test::CanUnarySubtractDifferentTypes<
        units::force::newton_t,
        units::force::pound_t
    >();

    test::CanUnarySubtractDifferentTypes<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t
    >();
}

TEST_F(TestVectorNWithUnits, CanUnaryMultiplyByScalarDimensionless)
{
    test::CanUnaryMultiplyByScalarDimensionless<units::length::meter_t>();
    test::CanUnaryMultiplyByScalarDimensionless<units::velocity::meters_per_second_t>();
    test::CanUnaryMultiplyByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
    test::CanUnaryMultiplyByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
    test::CanUnaryMultiplyByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
    test::CanUnaryMultiplyByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanUnaryMultiplyByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanUnaryMultiplyByScalarDimensionless<units::force::newton_t>();
    test::CanUnaryMultiplyByScalarDimensionless<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanUnaryDivideByScalarDimensionless)
{
    test::CanUnaryDivideByScalarDimensionless<units::length::meter_t>();
    test::CanUnaryDivideByScalarDimensionless<units::velocity::meters_per_second_t>();
    test::CanUnaryDivideByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
    test::CanUnaryDivideByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
    test::CanUnaryDivideByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
    test::CanUnaryDivideByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanUnaryDivideByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanUnaryDivideByScalarDimensionless<units::force::newton_t>();
    test::CanUnaryDivideByScalarDimensionless<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanCompare)
{
    test::CanCompare<units::length::meter_t>();
    test::CanCompare<units::velocity::meters_per_second_t>();
    test::CanCompare<units::acceleration::meters_per_second_squared_t>();
    test::CanCompare<units::angular_velocity::radians_per_second_t>();
    test::CanCompare<units::angular_velocity::degrees_per_second_t>();
    test::CanCompare<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanCompare<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanCompare<units::force::newton_t>();
    test::CanCompare<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanMultiplyScalarByVector)
{
    test::CanMultiplyScalarByVector<units::length::meter_t>();
    test::CanMultiplyScalarByVector<units::velocity::meters_per_second_t>();
    test::CanMultiplyScalarByVector<units::acceleration::meters_per_second_squared_t>();
    test::CanMultiplyScalarByVector<units::force::newton_t>();
    test::CanMultiplyScalarByVector<units::torque::newton_meter_t>();
}

TEST_F(TestVectorNWithUnits, CanMultiplyTimeScalarByVector)
{
    test::CanMultiplyTimeScalarByVector<units::length::meter_t>();
    test::CanMultiplyTimeScalarByVector<units::velocity::meters_per_second_t>();
    test::CanMultiplyTimeScalarByVector<units::acceleration::meters_per_second_squared_t>();
    test::CanMultiplyTimeScalarByVector<units::angular_velocity::radians_per_second_t>();
    test::CanMultiplyTimeScalarByVector<units::angular_velocity::degrees_per_second_t>();
    test::CanMultiplyTimeScalarByVector<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanMultiplyTimeScalarByVector<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanMultiplyTimeScalarByVector<units::force::newton_t>();
    test::CanMultiplyTimeScalarByVector<units::torque::newton_meter_t>();
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

TEST_F(TestVectorNWithUnits, CanMultiplyDimensionlessScalarByVector)
{
    test::CanMultiplyDimensionlessScalarByVector<units::length::meter_t>();
    test::CanMultiplyDimensionlessScalarByVector<units::velocity::meters_per_second_t>();
    test::CanMultiplyDimensionlessScalarByVector<units::acceleration::meters_per_second_squared_t>();
    test::CanMultiplyDimensionlessScalarByVector<units::angular_velocity::radians_per_second_t>();
    test::CanMultiplyDimensionlessScalarByVector<units::angular_velocity::degrees_per_second_t>();
    test::CanMultiplyDimensionlessScalarByVector<units::angular_acceleration::radians_per_second_squared_t>();
    test::CanMultiplyDimensionlessScalarByVector<units::angular_acceleration::degrees_per_second_squared_t>();
    test::CanMultiplyDimensionlessScalarByVector<units::force::newton_t>();
    test::CanMultiplyDimensionlessScalarByVector<units::torque::newton_meter_t>();
}