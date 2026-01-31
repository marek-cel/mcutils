#include <gtest/gtest.h>

#include <mcutils/math/Vector.h>

// To cover all classes generated from the template class in the SDK, tests are
// defined using template functions and used with different types.

using namespace units::literals;

#define TOLERANCE 1.0e-12

class TestVector3WithUnits : public ::testing::Test
{
protected:
    TestVector3WithUnits() {}
    virtual ~TestVector3WithUnits() {}
    void SetUp() override {}
    void TearDown() override {}
};

namespace test {
namespace Vector3 {

template <typename T>
void CanCreateI()
{
    mc::Vector3<T> v1 = mc::Vector3<T>::i();

    EXPECT_NEAR(v1.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 0.0, TOLERANCE);
}

template <typename T>
void CanCreateJ()
{
    mc::Vector3<T> v1 = mc::Vector3<T>::j();

    EXPECT_NEAR(v1.x()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 0.0, TOLERANCE);
}

template <typename T>
void CanCreateK()
{
    mc::Vector3<T> v1 = mc::Vector3<T>::k();

    EXPECT_NEAR(v1.x()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 1.0, TOLERANCE);
}

template <typename T>
void CanCreateEx()
{
    mc::Vector3<T> v1 = mc::Vector3<T>::ex();

    EXPECT_NEAR(v1.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 0.0, TOLERANCE);
}

template <typename T>
void CanCreateEy()
{
    mc::Vector3<T> v1 = mc::Vector3<T>::ey();

    EXPECT_NEAR(v1.x()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 0.0, TOLERANCE);
}

template <typename T>
void CanCreateEz()
{
    mc::Vector3<T> v1 = mc::Vector3<T>::ez();

    EXPECT_NEAR(v1.x()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 1.0, TOLERANCE);
}

template <typename T>
void CanInstantiate()
{
    mc::Vector3<T> v1;

    EXPECT_NEAR(v1.x()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 0.0, TOLERANCE);
}

template <typename T>
void CanInstantiateAndSetData()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});

    EXPECT_NEAR(v1.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 2.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 3.0, TOLERANCE);
}

template <typename T>
void CanGetLengthXY()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});
    // 1^2 + 2^2 = 1 + 4 = 5
    EXPECT_NEAR(v1.getLengthXY()(), sqrt(5.0), TOLERANCE);
}

template <typename T>
void CanGetLengthXZ()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});
    // 1^2 + 3^2 = 1 + 9 = 10
    EXPECT_NEAR(v1.getLengthXZ()(), sqrt(10.0), TOLERANCE);
}

template <typename T>
void CanGetLengthYZ()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});
    // 2^2 + 3^2 = 4 + 9 = 13
    EXPECT_NEAR(v1.getLengthYZ()(), sqrt(13.0), TOLERANCE);
}

template <typename T>
void CanGetNormalized()
{
    // expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_vector3.m

    mc::Vector3<T> v1(T{1}, T{2}, T{3});
    mc::Vector3d v1_n = v1.getNormalized();

    EXPECT_NEAR(v1_n.x(), 0.267261, 1.0e-5);
    EXPECT_NEAR(v1_n.y(), 0.534522, 1.0e-5);
    EXPECT_NEAR(v1_n.z(), 0.801784, 1.0e-5);

    EXPECT_NEAR(v1_n.getLength(), 1.0, TOLERANCE);
}

template <typename T>
void CanAccessElementsViaFunctionsXYZ()
{
    mc::Vector3<T> v;

    v.x() = T{1};
    v.y() = T{2};
    v.z() = T{3};

    const mc::Vector3<T>& vv = v;

    EXPECT_NEAR(vv.x()() , 1.0, TOLERANCE);
    EXPECT_NEAR(vv.y()() , 2.0, TOLERANCE);
    EXPECT_NEAR(vv.z()() , 3.0, TOLERANCE);
    EXPECT_NEAR(vv(0)()  , 1.0, TOLERANCE);
    EXPECT_NEAR(vv(1)()  , 2.0, TOLERANCE);
    EXPECT_NEAR(vv(2)()  , 3.0, TOLERANCE);
}

template <typename T>
void CanAccessElementsViaFunctionsPQR()
{
    mc::Vector3<T> v;

    v.p() = T{1};
    v.q() = T{2};
    v.r() = T{3};

    const mc::Vector3<T>& vv = v;

    EXPECT_NEAR(vv.p()() , 1.0, TOLERANCE);
    EXPECT_NEAR(vv.q()() , 2.0, TOLERANCE);
    EXPECT_NEAR(vv.r()() , 3.0, TOLERANCE);
    EXPECT_NEAR(vv(0)()  , 1.0, TOLERANCE);
    EXPECT_NEAR(vv(1)()  , 2.0, TOLERANCE);
    EXPECT_NEAR(vv(2)()  , 3.0, TOLERANCE);
}

template <typename T>
void CanAccessElementsViaFunctionsUVW()
{
    mc::Vector3<T> v;

    v.u() = T{1};
    v.v() = T{2};
    v.w() = T{3};

    const mc::Vector3<T>& vv = v;

    EXPECT_NEAR(vv.u()() , 1.0, TOLERANCE);
    EXPECT_NEAR(vv.v()() , 2.0, TOLERANCE);
    EXPECT_NEAR(vv.w()() , 3.0, TOLERANCE);
    EXPECT_NEAR(vv(0)()  , 1.0, TOLERANCE);
    EXPECT_NEAR(vv(1)()  , 2.0, TOLERANCE);
    EXPECT_NEAR(vv(2)()  , 3.0, TOLERANCE);
}

template <typename T1, typename T2>
void CanCastToOtherVectorType()
{
    mc::Vector3<T1> v1(T2{1}, T2{2}, T2{3}); // sic!
    mc::Vector3<T2> v2;
    v2 = v1;
    EXPECT_NEAR(v2.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v2.y()(), 2.0, TOLERANCE);
    EXPECT_NEAR(v2.z()(), 3.0, TOLERANCE);
}

template <typename T>
void CanAdd()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});
    mc::Vector3<T> v2(T{4}, T{5}, T{6});

    mc::Vector3<T> v12 = v1 + v2;

    EXPECT_NEAR(v12.x()(), 5.0, TOLERANCE);
    EXPECT_NEAR(v12.y()(), 7.0, TOLERANCE);
    EXPECT_NEAR(v12.z()(), 9.0, TOLERANCE);
}

template <typename T>
void CanNegate()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});

    mc::Vector3<T> v1_n = -v1;

    EXPECT_NEAR(v1_n.x()(), -1.0, TOLERANCE);
    EXPECT_NEAR(v1_n.y()(), -2.0, TOLERANCE);
    EXPECT_NEAR(v1_n.z()(), -3.0, TOLERANCE);
}

template <typename T>
void CanSubtract()
{
    mc::Vector3<T> v1(T{4}, T{5}, T{6});
    mc::Vector3<T> v2(T{3}, T{2}, T{1});

    mc::Vector3<T> v12 = v1 - v2;

    EXPECT_NEAR(v12.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v12.y()(), 3.0, TOLERANCE);
    EXPECT_NEAR(v12.z()(), 5.0, TOLERANCE);
}

template <typename T>
void CanMultiplyByScalar()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});

    units::length::meter_t val = 2.0_m;

    mc::Vector3<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::length::meter
            >
        >
    > vr = v * val;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

template <typename T>
void CanMultiplyByTimeScalar()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});

    units::time::second_t val = 2.0_s;

    mc::Vector3<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::time::second
            >
        >
    > vr = v * val;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

template <typename T>
void CanMultiplyByDimensionlessScalar()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});
    mc::Vector3<T> vr = v * 2.0;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

template <typename T>
void CanCalculateDotProduct()
{
    mc::Vector3<T> v1(T{1}, T{0}, T{0});
    mc::Vector3<T> v2(T{0}, T{1}, T{0});
    mc::Vector3<T> v3(T{0}, T{0}, T{1});
    mc::Vector3<T> v4(T{1}, T{2}, T{3});

    using ResultType = typename units::unit_t<units::squared<typename units::traits::unit_t_traits<T>::unit_type>>;

    ResultType s1 = v4 * v1;
    ResultType s2 = v4 * v2;
    ResultType s3 = v4 * v3;
    ResultType s4 = v4 * v4;

    EXPECT_NEAR(s1(),  1.0, TOLERANCE);
    EXPECT_NEAR(s2(),  2.0, TOLERANCE);
    EXPECT_NEAR(s3(),  3.0, TOLERANCE);
    EXPECT_NEAR(s4(), 14.0, TOLERANCE);
}

template <typename T>
void CanCalculateDotProductOfDimensionlessVector()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});
    mc::Vector3d v2(4.0, 5.0, 6.0);

    T s12 = v1 * v2;
    T s21 = v2 * v1;

    // expected values calculated with wxMaxima
    // tests/mcsim/utils/math/python/test_test::Vector3::dot_product.py
    EXPECT_NEAR(s12(), 32.0, TOLERANCE);
    EXPECT_NEAR(s21(), 32.0, TOLERANCE);
}

template <typename T>
void CanDivideByScalar()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});

    units::length::meter_t val = 2.0_m;

    mc::Vector3<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::inverse<units::length::meter>
            >
        >
    > vr = v / val;

    EXPECT_NEAR(vr.x()(), 0.5, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 1.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 1.5, TOLERANCE);
}

template <typename T>
void CanDivideByDimensionlessScalar()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});

    double val = 2.0;

    mc::Vector3<T> vr = v / val;

    EXPECT_NEAR(vr.x()(), 0.5, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 1.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 1.5, TOLERANCE);
}

template <typename T>
void CanCalculateVectorCrossProduct()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});
    mc::Vector3<units::length::meter_t> v2(4.0_m, 5.0_m, 6.0_m);

    mc::Vector3<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::length::meter
            >
        >
    > vr = v1 % v2;

    // expected values calculated with wxMaxima
    // tests/mcsim/utils/math/octave/test_test::Vector3::cross_product.m
    EXPECT_NEAR(vr.x()(), -3.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(),  6.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), -3.0, TOLERANCE);
}

template <typename T>
void CanCalculateVectorCrossProductOfDimensionlessVector()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});

    mc::Vector3d vd(4.0, 5.0, 6.0);

    mc::Vector3<T>v1 = v % vd;
    mc::Vector3<T>v2 = vd % v;

    // expected values calculated with wxMaxima
    // tests/mcsim/utils/math/octave/test_test::Vector3::cross_product.m
    EXPECT_NEAR(v1.x()(), -3.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(),  6.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), -3.0, TOLERANCE);

    EXPECT_NEAR(v2.x()(),  3.0, TOLERANCE);
    EXPECT_NEAR(v2.y()(), -6.0, TOLERANCE);
    EXPECT_NEAR(v2.z()(),  3.0, TOLERANCE);
}

template <typename T>
void CanUnaryAdd()
{
    mc::Vector3<T> v0(T{1}, T{2}, T{3});
    mc::Vector3<T> v1(T{2}, T{3}, T{4});

    v0 += v1;

    EXPECT_NEAR(v0.x()(), 3.0, TOLERANCE);
    EXPECT_NEAR(v0.y()(), 5.0, TOLERANCE);
    EXPECT_NEAR(v0.z()(), 7.0, TOLERANCE);
}

template <typename T>
void CanUnarySubtract()
{
    mc::Vector3<T> v0(T{3}, T{5}, T{7});
    mc::Vector3<T> v1(T{2}, T{3}, T{4});

    v0 -= v1;

    EXPECT_NEAR(v0.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v0.y()(), 2.0, TOLERANCE);
    EXPECT_NEAR(v0.z()(), 3.0, TOLERANCE);
}

template <typename T>
void CanUnaryMultiplyByScalarDimensionless()
{
    mc::Vector3<T> v0(T{2}, T{4}, T{6});

    v0 *= 0.5;

    EXPECT_NEAR(v0.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v0.y()(), 2.0, TOLERANCE);
    EXPECT_NEAR(v0.z()(), 3.0, TOLERANCE);
}

template <typename T>
void CanUnaryDivideByScalarDimensionless()
{
    mc::Vector3<T> v0(T{2}, T{4}, T{6});

    v0 /= 2.0;

    EXPECT_NEAR(v0.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v0.y()(), 2.0, TOLERANCE);
    EXPECT_NEAR(v0.z()(), 3.0, TOLERANCE);
}

template <typename T>
void CanMultiplyScalarByVector()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});

    units::length::meter_t val = 2.0_m;

    mc::Vector3<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::length::meter
            >
        >
    > vr = val * v;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

template <typename T>
void CanMultiplyScalarByVectorDimensionless()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});
    mc::Vector3<T> vr = 2.0 * v;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

} // namespace Vector3
} // namespace test

TEST_F(TestVector3WithUnits, CanCreateI)
{
    test::Vector3::CanCreateI<units::length::meter_t>();
    test::Vector3::CanCreateI<units::velocity::meters_per_second_t>();
    test::Vector3::CanCreateI<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanCreateI<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanCreateI<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanCreateI<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanCreateI<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanCreateI<units::force::newton_t>();
    test::Vector3::CanCreateI<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanCreateJ)
{
    test::Vector3::CanCreateJ<units::length::meter_t>();
    test::Vector3::CanCreateJ<units::velocity::meters_per_second_t>();
    test::Vector3::CanCreateJ<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanCreateJ<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanCreateJ<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanCreateJ<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanCreateJ<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanCreateJ<units::force::newton_t>();
    test::Vector3::CanCreateJ<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanCreateK)
{
    test::Vector3::CanCreateK<units::length::meter_t>();
    test::Vector3::CanCreateK<units::velocity::meters_per_second_t>();
    test::Vector3::CanCreateK<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanCreateK<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanCreateK<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanCreateK<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanCreateK<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanCreateK<units::force::newton_t>();
    test::Vector3::CanCreateK<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanCreateEx)
{
    test::Vector3::CanCreateEx<units::length::meter_t>();
    test::Vector3::CanCreateEx<units::velocity::meters_per_second_t>();
    test::Vector3::CanCreateEx<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanCreateEx<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanCreateEx<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanCreateEx<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanCreateEx<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanCreateEx<units::force::newton_t>();
    test::Vector3::CanCreateEx<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanCreateEy)
{
    test::Vector3::CanCreateEy<units::length::meter_t>();
    test::Vector3::CanCreateEy<units::velocity::meters_per_second_t>();
    test::Vector3::CanCreateEy<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanCreateEy<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanCreateEy<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanCreateEy<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanCreateEy<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanCreateEy<units::force::newton_t>();
    test::Vector3::CanCreateEy<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanCreateEz)
{
    test::Vector3::CanCreateEz<units::length::meter_t>();
    test::Vector3::CanCreateEz<units::velocity::meters_per_second_t>();
    test::Vector3::CanCreateEz<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanCreateEz<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanCreateEz<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanCreateEz<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanCreateEz<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanCreateEz<units::force::newton_t>();
    test::Vector3::CanCreateEz<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanInstantiate)
{
    test::Vector3::CanInstantiate<units::length::meter_t>();
    test::Vector3::CanInstantiate<units::velocity::meters_per_second_t>();
    test::Vector3::CanInstantiate<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanInstantiate<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanInstantiate<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanInstantiate<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanInstantiate<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanInstantiate<units::force::newton_t>();
    test::Vector3::CanInstantiate<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanInstantiateAndSetData)
{
    test::Vector3::CanInstantiateAndSetData<units::length::meter_t>();
    test::Vector3::CanInstantiateAndSetData<units::velocity::meters_per_second_t>();
    test::Vector3::CanInstantiateAndSetData<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanInstantiateAndSetData<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanInstantiateAndSetData<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanInstantiateAndSetData<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanInstantiateAndSetData<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanInstantiateAndSetData<units::force::newton_t>();
    test::Vector3::CanInstantiateAndSetData<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanGetLengthXY)
{
    test::Vector3::CanGetLengthXY<units::length::meter_t>();
    test::Vector3::CanGetLengthXY<units::velocity::meters_per_second_t>();
    test::Vector3::CanGetLengthXY<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanGetLengthXY<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanGetLengthXY<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanGetLengthXY<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanGetLengthXY<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanGetLengthXY<units::force::newton_t>();
    test::Vector3::CanGetLengthXY<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanGetLengthXZ)
{
    test::Vector3::CanGetLengthXZ<units::length::meter_t>();
    test::Vector3::CanGetLengthXZ<units::velocity::meters_per_second_t>();
    test::Vector3::CanGetLengthXZ<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanGetLengthXZ<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanGetLengthXZ<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanGetLengthXZ<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanGetLengthXZ<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanGetLengthXZ<units::force::newton_t>();
    test::Vector3::CanGetLengthXZ<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanGetLengthYZ)
{
    test::Vector3::CanGetLengthYZ<units::length::meter_t>();
    test::Vector3::CanGetLengthYZ<units::velocity::meters_per_second_t>();
    test::Vector3::CanGetLengthYZ<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanGetLengthYZ<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanGetLengthYZ<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanGetLengthYZ<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanGetLengthYZ<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanGetLengthYZ<units::force::newton_t>();
    test::Vector3::CanGetLengthYZ<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanAccessElementsViaFunctionsXYZ)
{
    test::Vector3::CanAccessElementsViaFunctionsXYZ<units::length::meter_t>();
    test::Vector3::CanAccessElementsViaFunctionsXYZ<units::velocity::meters_per_second_t>();
    test::Vector3::CanAccessElementsViaFunctionsXYZ<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanAccessElementsViaFunctionsXYZ<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanAccessElementsViaFunctionsXYZ<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanAccessElementsViaFunctionsXYZ<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanAccessElementsViaFunctionsXYZ<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanAccessElementsViaFunctionsXYZ<units::force::newton_t>();
    test::Vector3::CanAccessElementsViaFunctionsXYZ<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanAccessElementsViaFunctionsPQR)
{
    test::Vector3::CanAccessElementsViaFunctionsPQR<units::length::meter_t>();
    test::Vector3::CanAccessElementsViaFunctionsPQR<units::velocity::meters_per_second_t>();
    test::Vector3::CanAccessElementsViaFunctionsPQR<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanAccessElementsViaFunctionsPQR<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanAccessElementsViaFunctionsPQR<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanAccessElementsViaFunctionsPQR<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanAccessElementsViaFunctionsPQR<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanAccessElementsViaFunctionsPQR<units::force::newton_t>();
    test::Vector3::CanAccessElementsViaFunctionsPQR<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanAccessElementsViaFunctionsUVW)
{
    test::Vector3::CanAccessElementsViaFunctionsUVW<units::length::meter_t>();
    test::Vector3::CanAccessElementsViaFunctionsUVW<units::velocity::meters_per_second_t>();
    test::Vector3::CanAccessElementsViaFunctionsUVW<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanAccessElementsViaFunctionsUVW<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanAccessElementsViaFunctionsUVW<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanAccessElementsViaFunctionsUVW<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanAccessElementsViaFunctionsUVW<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanAccessElementsViaFunctionsUVW<units::force::newton_t>();
    test::Vector3::CanAccessElementsViaFunctionsUVW<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanCastToOtherVectorType)
{
    test::Vector3::CanCastToOtherVectorType<
        units::length::meter_t,
        units::length::foot_t>();
    test::Vector3::CanCastToOtherVectorType<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t>();
    test::Vector3::CanCastToOtherVectorType<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t>();
    test::Vector3::CanCastToOtherVectorType<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanCastToOtherVectorType<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanCastToOtherVectorType<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanCastToOtherVectorType<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanCastToOtherVectorType<
        units::force::newton_t,
        units::force::pound_t>();
    test::Vector3::CanCastToOtherVectorType<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t>();
}

TEST_F(TestVector3WithUnits, CanAdd)
{
    test::Vector3::CanAdd<units::length::meter_t>();
    test::Vector3::CanAdd<units::velocity::meters_per_second_t>();
    test::Vector3::CanAdd<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanAdd<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanAdd<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanAdd<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanAdd<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanAdd<units::force::newton_t>();
    test::Vector3::CanAdd<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanNegate)
{
    test::Vector3::CanNegate<units::length::meter_t>();
    test::Vector3::CanNegate<units::velocity::meters_per_second_t>();
    test::Vector3::CanNegate<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanNegate<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanNegate<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanNegate<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanNegate<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanNegate<units::force::newton_t>();
    test::Vector3::CanNegate<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanSubtract)
{
    test::Vector3::CanSubtract<units::length::meter_t>();
    test::Vector3::CanSubtract<units::velocity::meters_per_second_t>();
    test::Vector3::CanSubtract<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanSubtract<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanSubtract<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanSubtract<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanSubtract<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanSubtract<units::force::newton_t>();
    test::Vector3::CanSubtract<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanMultiplyByScalar)
{
    test::Vector3::CanMultiplyByScalar<units::length::meter_t>();
    test::Vector3::CanMultiplyByScalar<units::velocity::meters_per_second_t>();
    test::Vector3::CanMultiplyByScalar<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanMultiplyByScalar<units::force::newton_t>();
    test::Vector3::CanMultiplyByScalar<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanMultiplyByTimeScalar)
{
    test::Vector3::CanMultiplyByTimeScalar<units::length::meter_t>();
    test::Vector3::CanMultiplyByTimeScalar<units::velocity::meters_per_second_t>();
    test::Vector3::CanMultiplyByTimeScalar<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanMultiplyByTimeScalar<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanMultiplyByTimeScalar<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanMultiplyByTimeScalar<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanMultiplyByTimeScalar<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanMultiplyByTimeScalar<units::force::newton_t>();
    test::Vector3::CanMultiplyByTimeScalar<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanMultiplyDimensionlessVectorByScalar)
{
    mc::Vector3d v(1.0, 2.0, 3.0);
    mc::Vector3<units::length::meter_t> vr = v * 2.0_m;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanMultiplyDimensionlessScalar)
{
    test::Vector3::CanMultiplyByDimensionlessScalar<units::length::meter_t>();
    test::Vector3::CanMultiplyByDimensionlessScalar<units::velocity::meters_per_second_t>();
    test::Vector3::CanMultiplyByDimensionlessScalar<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanMultiplyByDimensionlessScalar<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanMultiplyByDimensionlessScalar<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanMultiplyByDimensionlessScalar<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanMultiplyByDimensionlessScalar<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanMultiplyByDimensionlessScalar<units::force::newton_t>();
    test::Vector3::CanMultiplyByDimensionlessScalar<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanCalculateDotProduct)
{
    test::Vector3::CanCalculateDotProduct<units::length::meter_t>();
    test::Vector3::CanCalculateDotProduct<units::velocity::meters_per_second_t>();
    test::Vector3::CanCalculateDotProduct<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanCalculateDotProduct<units::force::newton_t>();
    test::Vector3::CanCalculateDotProduct<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanCalculateDotProductOfDimensionlessVector)
{
    test::Vector3::CanCalculateDotProductOfDimensionlessVector<units::length::meter_t>();
    test::Vector3::CanCalculateDotProductOfDimensionlessVector<units::velocity::meters_per_second_t>();
    test::Vector3::CanCalculateDotProductOfDimensionlessVector<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanCalculateDotProductOfDimensionlessVector<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanCalculateDotProductOfDimensionlessVector<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanCalculateDotProductOfDimensionlessVector<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanCalculateDotProductOfDimensionlessVector<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanCalculateDotProductOfDimensionlessVector<units::force::newton_t>();
    test::Vector3::CanCalculateDotProductOfDimensionlessVector<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanDivideByScalar)
{
    test::Vector3::CanDivideByScalar<units::length::meter_t>();
    test::Vector3::CanDivideByScalar<units::velocity::meters_per_second_t>();
    test::Vector3::CanDivideByScalar<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanDivideByScalar<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanDivideByScalar<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanDivideByScalar<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanDivideByScalar<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanDivideByScalar<units::force::newton_t>();
    test::Vector3::CanDivideByScalar<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanDivideDimensionlessVectorByScalar)
{
    mc::Vector3<double> v(1.0, 2.0, 3.0);

    constexpr units::time::second_t val = 2.0_s;
    mc::Vector3<units::frequency::hertz_t> vr = v / val;

    EXPECT_NEAR(vr.x()(), 0.5, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 1.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 1.5, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanDivideByDimensionlessScalar)
{
    test::Vector3::CanDivideByDimensionlessScalar<units::length::meter_t>();
    test::Vector3::CanDivideByDimensionlessScalar<units::velocity::meters_per_second_t>();
    test::Vector3::CanDivideByDimensionlessScalar<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanDivideByDimensionlessScalar<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanDivideByDimensionlessScalar<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanDivideByDimensionlessScalar<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanDivideByDimensionlessScalar<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanDivideByDimensionlessScalar<units::force::newton_t>();
    test::Vector3::CanDivideByDimensionlessScalar<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanCalculateVectorCrossProduct)
{
    test::Vector3::CanCalculateVectorCrossProduct<units::length::meter_t>();
    test::Vector3::CanCalculateVectorCrossProduct<units::velocity::meters_per_second_t>();
    test::Vector3::CanCalculateVectorCrossProduct<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanCalculateVectorCrossProduct<units::force::newton_t>();
    test::Vector3::CanCalculateVectorCrossProduct<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanCalculateVectorCrossProductOfDimensionlessVector)
{
    test::Vector3::CanCalculateVectorCrossProductOfDimensionlessVector<units::length::meter_t>();
    test::Vector3::CanCalculateVectorCrossProductOfDimensionlessVector<units::velocity::meters_per_second_t>();
    test::Vector3::CanCalculateVectorCrossProductOfDimensionlessVector<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanCalculateVectorCrossProductOfDimensionlessVector<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanCalculateVectorCrossProductOfDimensionlessVector<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanCalculateVectorCrossProductOfDimensionlessVector<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanCalculateVectorCrossProductOfDimensionlessVector<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanCalculateVectorCrossProductOfDimensionlessVector<units::force::newton_t>();
    test::Vector3::CanCalculateVectorCrossProductOfDimensionlessVector<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanUnaryAdd)
{
    test::Vector3::CanUnaryAdd<units::length::meter_t>();
    test::Vector3::CanUnaryAdd<units::velocity::meters_per_second_t>();
    test::Vector3::CanUnaryAdd<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanUnaryAdd<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanUnaryAdd<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanUnaryAdd<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanUnaryAdd<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanUnaryAdd<units::force::newton_t>();
    test::Vector3::CanUnaryAdd<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanUnarySubtract)
{
    test::Vector3::CanUnarySubtract<units::length::meter_t>();
    test::Vector3::CanUnarySubtract<units::velocity::meters_per_second_t>();
    test::Vector3::CanUnarySubtract<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanUnarySubtract<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanUnarySubtract<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanUnarySubtract<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanUnarySubtract<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanUnarySubtract<units::force::newton_t>();
    test::Vector3::CanUnarySubtract<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanUnaryMultiplyByScalarDimensionless)
{
    test::Vector3::CanUnaryMultiplyByScalarDimensionless<units::length::meter_t>();
    test::Vector3::CanUnaryMultiplyByScalarDimensionless<units::velocity::meters_per_second_t>();
    test::Vector3::CanUnaryMultiplyByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanUnaryMultiplyByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanUnaryMultiplyByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanUnaryMultiplyByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanUnaryMultiplyByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanUnaryMultiplyByScalarDimensionless<units::force::newton_t>();
    test::Vector3::CanUnaryMultiplyByScalarDimensionless<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanUnaryDivideByScalarDimensionless)
{
    test::Vector3::CanUnaryDivideByScalarDimensionless<units::length::meter_t>();
    test::Vector3::CanUnaryDivideByScalarDimensionless<units::velocity::meters_per_second_t>();
    test::Vector3::CanUnaryDivideByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanUnaryDivideByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanUnaryDivideByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanUnaryDivideByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanUnaryDivideByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanUnaryDivideByScalarDimensionless<units::force::newton_t>();
    test::Vector3::CanUnaryDivideByScalarDimensionless<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanMultiplyScalarByVector)
{
    test::Vector3::CanMultiplyScalarByVector<units::length::meter_t>();
    test::Vector3::CanMultiplyScalarByVector<units::velocity::meters_per_second_t>();
    test::Vector3::CanMultiplyScalarByVector<units::acceleration::meters_per_second_squared_t>();

    // angular velocity and angular acceleration excluded from this test
    // because they are treated in a special way

    test::Vector3::CanMultiplyScalarByVector<units::force::newton_t>();
    test::Vector3::CanMultiplyScalarByVector<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanMultiplyScalarByVectorDimensionlessVector)
{
    mc::Vector3d v(1.0, 2.0, 3.0);
    mc::Vector3<units::length::meter_t> vr = 2.0_m * v;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanMultiplyScalarByVectorDimensionless)
{
    test::Vector3::CanMultiplyScalarByVectorDimensionless<units::length::meter_t>();
    test::Vector3::CanMultiplyScalarByVectorDimensionless<units::velocity::meters_per_second_t>();
    test::Vector3::CanMultiplyScalarByVectorDimensionless<units::acceleration::meters_per_second_squared_t>();
    test::Vector3::CanMultiplyScalarByVectorDimensionless<units::angular_velocity::radians_per_second_t>();
    test::Vector3::CanMultiplyScalarByVectorDimensionless<units::angular_velocity::degrees_per_second_t>();
    test::Vector3::CanMultiplyScalarByVectorDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    test::Vector3::CanMultiplyScalarByVectorDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    test::Vector3::CanMultiplyScalarByVectorDimensionless<units::force::newton_t>();
    test::Vector3::CanMultiplyScalarByVectorDimensionless<units::torque::newton_meter_t>();
}