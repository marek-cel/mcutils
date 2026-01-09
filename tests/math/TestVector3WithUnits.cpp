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

template <typename T>
void Vector3_CanCreateI()
{
    mc::Vector3<T> v1 = mc::Vector3<T>::i();

    EXPECT_NEAR(v1.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 0.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanCreateI)
{
    Vector3_CanCreateI<units::length::meter_t>();
    Vector3_CanCreateI<units::velocity::meters_per_second_t>();
    Vector3_CanCreateI<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanCreateI<units::angular_velocity::radians_per_second_t>();
    Vector3_CanCreateI<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanCreateI<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanCreateI<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanCreateI<units::force::newton_t>();
    Vector3_CanCreateI<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanCreateJ()
{
    mc::Vector3<T> v1 = mc::Vector3<T>::j();

    EXPECT_NEAR(v1.x()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 0.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanCreateJ)
{
    Vector3_CanCreateJ<units::length::meter_t>();
    Vector3_CanCreateJ<units::velocity::meters_per_second_t>();
    Vector3_CanCreateJ<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanCreateJ<units::angular_velocity::radians_per_second_t>();
    Vector3_CanCreateJ<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanCreateJ<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanCreateJ<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanCreateJ<units::force::newton_t>();
    Vector3_CanCreateJ<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanCreateK()
{
    mc::Vector3<T> v1 = mc::Vector3<T>::k();

    EXPECT_NEAR(v1.x()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 1.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanCreateK)
{
    Vector3_CanCreateK<units::length::meter_t>();
    Vector3_CanCreateK<units::velocity::meters_per_second_t>();
    Vector3_CanCreateK<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanCreateK<units::angular_velocity::radians_per_second_t>();
    Vector3_CanCreateK<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanCreateK<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanCreateK<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanCreateK<units::force::newton_t>();
    Vector3_CanCreateK<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanCreateEx()
{
    mc::Vector3<T> v1 = mc::Vector3<T>::ex();

    EXPECT_NEAR(v1.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 0.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanCreateEx)
{
    Vector3_CanCreateEx<units::length::meter_t>();
    Vector3_CanCreateEx<units::velocity::meters_per_second_t>();
    Vector3_CanCreateEx<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanCreateEx<units::angular_velocity::radians_per_second_t>();
    Vector3_CanCreateEx<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanCreateEx<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanCreateEx<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanCreateEx<units::force::newton_t>();
    Vector3_CanCreateEx<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanCreateEy()
{
    mc::Vector3<T> v1 = mc::Vector3<T>::ey();

    EXPECT_NEAR(v1.x()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 0.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanCreateEy)
{
    Vector3_CanCreateEy<units::length::meter_t>();
    Vector3_CanCreateEy<units::velocity::meters_per_second_t>();
    Vector3_CanCreateEy<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanCreateEy<units::angular_velocity::radians_per_second_t>();
    Vector3_CanCreateEy<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanCreateEy<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanCreateEy<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanCreateEy<units::force::newton_t>();
    Vector3_CanCreateEy<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanCreateEz()
{
    mc::Vector3<T> v1 = mc::Vector3<T>::ez();

    EXPECT_NEAR(v1.x()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 1.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanCreateEz)
{
    Vector3_CanCreateEz<units::length::meter_t>();
    Vector3_CanCreateEz<units::velocity::meters_per_second_t>();
    Vector3_CanCreateEz<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanCreateEz<units::angular_velocity::radians_per_second_t>();
    Vector3_CanCreateEz<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanCreateEz<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanCreateEz<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanCreateEz<units::force::newton_t>();
    Vector3_CanCreateEz<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanInstantiate()
{
    mc::Vector3<T> v1;

    EXPECT_NEAR(v1.x()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 0.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 0.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanInstantiate)
{
    Vector3_CanInstantiate<units::length::meter_t>();
    Vector3_CanInstantiate<units::velocity::meters_per_second_t>();
    Vector3_CanInstantiate<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanInstantiate<units::angular_velocity::radians_per_second_t>();
    Vector3_CanInstantiate<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanInstantiate<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanInstantiate<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanInstantiate<units::force::newton_t>();
    Vector3_CanInstantiate<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanInstantiateAndSetData()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});

    EXPECT_NEAR(v1.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(), 2.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), 3.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanInstantiateAndSetData)
{
    Vector3_CanInstantiateAndSetData<units::length::meter_t>();
    Vector3_CanInstantiateAndSetData<units::velocity::meters_per_second_t>();
    Vector3_CanInstantiateAndSetData<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanInstantiateAndSetData<units::angular_velocity::radians_per_second_t>();
    Vector3_CanInstantiateAndSetData<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanInstantiateAndSetData<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanInstantiateAndSetData<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanInstantiateAndSetData<units::force::newton_t>();
    Vector3_CanInstantiateAndSetData<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanGetLengthXY()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});
    // 1^2 + 2^2 = 1 + 4 = 5
    EXPECT_NEAR(v1.getLengthXY()(), sqrt(5.0), TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanGetLengthXY)
{
    Vector3_CanGetLengthXY<units::length::meter_t>();
    Vector3_CanGetLengthXY<units::velocity::meters_per_second_t>();
    Vector3_CanGetLengthXY<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanGetLengthXY<units::angular_velocity::radians_per_second_t>();
    Vector3_CanGetLengthXY<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanGetLengthXY<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanGetLengthXY<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanGetLengthXY<units::force::newton_t>();
    Vector3_CanGetLengthXY<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanGetLengthXZ()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});
    // 1^2 + 3^2 = 1 + 9 = 10
    EXPECT_NEAR(v1.getLengthXZ()(), sqrt(10.0), TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanGetLengthXZ)
{
    Vector3_CanGetLengthXZ<units::length::meter_t>();
    Vector3_CanGetLengthXZ<units::velocity::meters_per_second_t>();
    Vector3_CanGetLengthXZ<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanGetLengthXZ<units::angular_velocity::radians_per_second_t>();
    Vector3_CanGetLengthXZ<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanGetLengthXZ<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanGetLengthXZ<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanGetLengthXZ<units::force::newton_t>();
    Vector3_CanGetLengthXZ<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanGetLengthYZ()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});
    // 2^2 + 3^2 = 4 + 9 = 13
    EXPECT_NEAR(v1.getLengthYZ()(), sqrt(13.0), TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanGetLengthYZ)
{
    Vector3_CanGetLengthYZ<units::length::meter_t>();
    Vector3_CanGetLengthYZ<units::velocity::meters_per_second_t>();
    Vector3_CanGetLengthYZ<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanGetLengthYZ<units::angular_velocity::radians_per_second_t>();
    Vector3_CanGetLengthYZ<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanGetLengthYZ<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanGetLengthYZ<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanGetLengthYZ<units::force::newton_t>();
    Vector3_CanGetLengthYZ<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanGetNormalized()
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

TEST_F(TestVector3WithUnits, CanGetNormalized)
{
    Vector3_CanGetNormalized<units::length::meter_t>();
    Vector3_CanGetNormalized<units::velocity::meters_per_second_t>();
    Vector3_CanGetNormalized<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanGetNormalized<units::angular_velocity::radians_per_second_t>();
    Vector3_CanGetNormalized<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanGetNormalized<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanGetNormalized<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanGetNormalized<units::force::newton_t>();
    Vector3_CanGetNormalized<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanSetData()
{
    mc::Vector3<T> v;
    v.set(T{1}, T{2}, T{3});

    EXPECT_NEAR(v.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v.y()(), 2.0, TOLERANCE);
    EXPECT_NEAR(v.z()(), 3.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanSetData)
{
    Vector3_CanSetData<units::length::meter_t>();
    Vector3_CanSetData<units::velocity::meters_per_second_t>();
    Vector3_CanSetData<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanSetData<units::angular_velocity::radians_per_second_t>();
    Vector3_CanSetData<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanSetData<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanSetData<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanSetData<units::force::newton_t>();
    Vector3_CanSetData<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanAccessElementsViaFunctionsXYZ()
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

TEST_F(TestVector3WithUnits, CanAccessElementsViaFunctionsXYZ)
{
    Vector3_CanAccessElementsViaFunctionsXYZ<units::length::meter_t>();
    Vector3_CanAccessElementsViaFunctionsXYZ<units::velocity::meters_per_second_t>();
    Vector3_CanAccessElementsViaFunctionsXYZ<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanAccessElementsViaFunctionsXYZ<units::angular_velocity::radians_per_second_t>();
    Vector3_CanAccessElementsViaFunctionsXYZ<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanAccessElementsViaFunctionsXYZ<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanAccessElementsViaFunctionsXYZ<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanAccessElementsViaFunctionsXYZ<units::force::newton_t>();
    Vector3_CanAccessElementsViaFunctionsXYZ<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanAccessElementsViaFunctionsPQR()
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

TEST_F(TestVector3WithUnits, CanAccessElementsViaFunctionsPQR)
{
    Vector3_CanAccessElementsViaFunctionsPQR<units::length::meter_t>();
    Vector3_CanAccessElementsViaFunctionsPQR<units::velocity::meters_per_second_t>();
    Vector3_CanAccessElementsViaFunctionsPQR<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanAccessElementsViaFunctionsPQR<units::angular_velocity::radians_per_second_t>();
    Vector3_CanAccessElementsViaFunctionsPQR<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanAccessElementsViaFunctionsPQR<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanAccessElementsViaFunctionsPQR<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanAccessElementsViaFunctionsPQR<units::force::newton_t>();
    Vector3_CanAccessElementsViaFunctionsPQR<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanAccessElementsViaFunctionsUVW()
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

TEST_F(TestVector3WithUnits, CanAccessElementsViaFunctionsUVW)
{
    Vector3_CanAccessElementsViaFunctionsUVW<units::length::meter_t>();
    Vector3_CanAccessElementsViaFunctionsUVW<units::velocity::meters_per_second_t>();
    Vector3_CanAccessElementsViaFunctionsUVW<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanAccessElementsViaFunctionsUVW<units::angular_velocity::radians_per_second_t>();
    Vector3_CanAccessElementsViaFunctionsUVW<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanAccessElementsViaFunctionsUVW<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanAccessElementsViaFunctionsUVW<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanAccessElementsViaFunctionsUVW<units::force::newton_t>();
    Vector3_CanAccessElementsViaFunctionsUVW<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanGetDimensionless()
{
    mc::Vector3<T> v1;
    v1(0) = T{1};
    v1(1) = T{2};
    v1(2) = T{3};

    mc::Vector3<double> v2;
    v2 = v1.getDimensionless();
    EXPECT_NEAR(v2(0), 1.0, TOLERANCE);
    EXPECT_NEAR(v2(1), 2.0, TOLERANCE);
    EXPECT_NEAR(v2(2), 3.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanGetDimensionless)
{
    Vector3_CanGetDimensionless<units::length::meter_t>();
    Vector3_CanGetDimensionless<units::velocity::meters_per_second_t>();
    Vector3_CanGetDimensionless<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanGetDimensionless<units::angular_velocity::radians_per_second_t>();
    Vector3_CanGetDimensionless<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanGetDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanGetDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanGetDimensionless<units::force::newton_t>();
    Vector3_CanGetDimensionless<units::torque::newton_meter_t>();
}

template <typename T1, typename T2>
void Vector3_CanCastToOtherVectorType()
{
    mc::Vector3<T1> v1(T2{1}, T2{2}, T2{3}); // sic!
    mc::Vector3<T2> v2;
    v2 = v1;
    EXPECT_NEAR(v2.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v2.y()(), 2.0, TOLERANCE);
    EXPECT_NEAR(v2.z()(), 3.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanCastToOtherVectorType)
{
    Vector3_CanCastToOtherVectorType<
        units::length::meter_t,
        units::length::foot_t>();
    Vector3_CanCastToOtherVectorType<
        units::velocity::meters_per_second_t,
        units::velocity::feet_per_minute_t>();
    Vector3_CanCastToOtherVectorType<
        units::acceleration::meters_per_second_squared_t,
        units::acceleration::feet_per_second_squared_t>();
    Vector3_CanCastToOtherVectorType<
        units::angular_velocity::radians_per_second_t,
        units::angular_velocity::degrees_per_second_t>();
    Vector3_CanCastToOtherVectorType<
        units::angular_velocity::degrees_per_second_t,
        units::angular_velocity::radians_per_second_t>();
    Vector3_CanCastToOtherVectorType<
        units::angular_acceleration::radians_per_second_squared_t,
        units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanCastToOtherVectorType<
        units::angular_acceleration::degrees_per_second_squared_t,
        units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanCastToOtherVectorType<
        units::force::newton_t,
        units::force::pound_t>();
    Vector3_CanCastToOtherVectorType<
        units::torque::newton_meter_t,
        units::torque::foot_pound_t>();
}

template <typename T>
void Vector3_CanAdd()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});
    mc::Vector3<T> v2(T{4}, T{5}, T{6});

    mc::Vector3<T> v12 = v1 + v2;

    EXPECT_NEAR(v12.x()(), 5.0, TOLERANCE);
    EXPECT_NEAR(v12.y()(), 7.0, TOLERANCE);
    EXPECT_NEAR(v12.z()(), 9.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanAdd)
{
    Vector3_CanAdd<units::length::meter_t>();
    Vector3_CanAdd<units::velocity::meters_per_second_t>();
    Vector3_CanAdd<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanAdd<units::angular_velocity::radians_per_second_t>();
    Vector3_CanAdd<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanAdd<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanAdd<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanAdd<units::force::newton_t>();
    Vector3_CanAdd<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanNegate()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});

    mc::Vector3<T> v1_n = -v1;

    EXPECT_NEAR(v1_n.x()(), -1.0, TOLERANCE);
    EXPECT_NEAR(v1_n.y()(), -2.0, TOLERANCE);
    EXPECT_NEAR(v1_n.z()(), -3.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanNegate)
{
    Vector3_CanNegate<units::length::meter_t>();
    Vector3_CanNegate<units::velocity::meters_per_second_t>();
    Vector3_CanNegate<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanNegate<units::angular_velocity::radians_per_second_t>();
    Vector3_CanNegate<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanNegate<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanNegate<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanNegate<units::force::newton_t>();
    Vector3_CanNegate<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanSubtract()
{
    mc::Vector3<T> v1(T{4}, T{5}, T{6});
    mc::Vector3<T> v2(T{3}, T{2}, T{1});

    mc::Vector3<T> v12 = v1 - v2;

    EXPECT_NEAR(v12.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v12.y()(), 3.0, TOLERANCE);
    EXPECT_NEAR(v12.z()(), 5.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanSubtract)
{
    Vector3_CanSubtract<units::length::meter_t>();
    Vector3_CanSubtract<units::velocity::meters_per_second_t>();
    Vector3_CanSubtract<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanSubtract<units::angular_velocity::radians_per_second_t>();
    Vector3_CanSubtract<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanSubtract<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanSubtract<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanSubtract<units::force::newton_t>();
    Vector3_CanSubtract<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanMultiplyByScalar()
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

TEST_F(TestVector3WithUnits, CanMultiplyByScalar)
{
    Vector3_CanMultiplyByScalar<units::length::meter_t>();
    Vector3_CanMultiplyByScalar<units::velocity::meters_per_second_t>();
    Vector3_CanMultiplyByScalar<units::acceleration::meters_per_second_squared_t>();

    // angular velocity and angular acceleration excluded from this test
    // because they are treated in a special way

    Vector3_CanMultiplyByScalar<units::force::newton_t>();
    Vector3_CanMultiplyByScalar<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanMultiplyByScalarTime()
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

TEST_F(TestVector3WithUnits, CanMultiplyByScalarTime)
{
    Vector3_CanMultiplyByScalarTime<units::length::meter_t>();
    Vector3_CanMultiplyByScalarTime<units::velocity::meters_per_second_t>();
    Vector3_CanMultiplyByScalarTime<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanMultiplyByScalarTime<units::angular_velocity::radians_per_second_t>();
    Vector3_CanMultiplyByScalarTime<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanMultiplyByScalarTime<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanMultiplyByScalarTime<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanMultiplyByScalarTime<units::force::newton_t>();
    Vector3_CanMultiplyByScalarTime<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanMultiplyByScalarAngularVel()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});

    units::angular_velocity::degrees_per_second_t val = 2.0_rad_per_s;

    mc::Vector3<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_t>::unit_type
            >
        >
    > vr = v * val;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanMultiplyByScalarAngularVel)
{
    Vector3_CanMultiplyByScalarAngularVel<units::length::meter_t>();
    Vector3_CanMultiplyByScalarAngularVel<units::velocity::meters_per_second_t>();
    Vector3_CanMultiplyByScalarAngularVel<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanMultiplyByScalarAngularVel<units::angular_velocity::radians_per_second_t>();
    Vector3_CanMultiplyByScalarAngularVel<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanMultiplyByScalarAngularVel<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanMultiplyByScalarAngularVel<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanMultiplyByScalarAngularVel<units::force::newton_t>();
    Vector3_CanMultiplyByScalarAngularVel<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanMultiplyByScalarAngularAcc()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});

    units::angular_acceleration::degrees_per_second_squared_t val = 2.0_rad_per_s_sq;

    mc::Vector3<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_squared_t>::unit_type
            >
        >
    > vr = v * val;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanMultiplyByScalarAngularAcc)
{
    Vector3_CanMultiplyByScalarAngularAcc<units::length::meter_t>();
    Vector3_CanMultiplyByScalarAngularAcc<units::velocity::meters_per_second_t>();
    Vector3_CanMultiplyByScalarAngularAcc<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanMultiplyByScalarAngularAcc<units::angular_velocity::radians_per_second_t>();
    Vector3_CanMultiplyByScalarAngularAcc<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanMultiplyByScalarAngularAcc<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanMultiplyByScalarAngularAcc<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanMultiplyByScalarAngularAcc<units::force::newton_t>();
    Vector3_CanMultiplyByScalarAngularAcc<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanMultiplyByScalarDimensionlessVector)
{
    mc::Vector3d v(1.0, 2.0, 3.0);
    mc::Vector3<units::length::meter_t> vr = v * 2.0_m;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

template <typename T>
void Vector3_CanMultiplyByScalarDimensionless()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});
    mc::Vector3<T> vr = v * 2.0;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanMultiplyByScalarDimensionless)
{
    Vector3_CanMultiplyByScalarDimensionless<units::length::meter_t>();
    Vector3_CanMultiplyByScalarDimensionless<units::velocity::meters_per_second_t>();
    Vector3_CanMultiplyByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanMultiplyByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
    Vector3_CanMultiplyByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanMultiplyByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanMultiplyByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanMultiplyByScalarDimensionless<units::force::newton_t>();
    Vector3_CanMultiplyByScalarDimensionless<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanCalculateDotProduct()
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

TEST_F(TestVector3WithUnits, CanCalculateDotProduct)
{
    Vector3_CanCalculateDotProduct<units::length::meter_t>();
    Vector3_CanCalculateDotProduct<units::velocity::meters_per_second_t>();
    Vector3_CanCalculateDotProduct<units::acceleration::meters_per_second_squared_t>();

    // angular velocity and angular acceleration excluded from this test
    // because they are treated in a special way

    Vector3_CanCalculateDotProduct<units::force::newton_t>();
    Vector3_CanCalculateDotProduct<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanCalculateVectorDotProductAngularVel()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});
    mc::Vector3_deg_per_s v2(4.0_rad_per_s, 5.0_rad_per_s, 6.0_rad_per_s);

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


TEST_F(TestVector3WithUnits, CanCalculateVectorDotProductAngularVel)
{
    Vector3_CanCalculateVectorDotProductAngularVel<units::length::meter_t>();
    Vector3_CanCalculateVectorDotProductAngularVel<units::velocity::meters_per_second_t>();
    Vector3_CanCalculateVectorDotProductAngularVel<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanCalculateVectorDotProductAngularVel<units::angular_velocity::radians_per_second_t>();
    Vector3_CanCalculateVectorDotProductAngularVel<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanCalculateVectorDotProductAngularVel<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanCalculateVectorDotProductAngularVel<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanCalculateVectorDotProductAngularVel<units::force::newton_t>();
    Vector3_CanCalculateVectorDotProductAngularVel<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanCalculateVectorDotProductAngularAcc()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});
    mc::Vector3_deg_per_s_sq v2(4.0_rad_per_s_sq, 5.0_rad_per_s_sq, 6.0_rad_per_s_sq);

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

TEST_F(TestVector3WithUnits, CanCalculateVectorDotProductAngularAcc)
{
    Vector3_CanCalculateVectorDotProductAngularAcc<units::length::meter_t>();
    Vector3_CanCalculateVectorDotProductAngularAcc<units::velocity::meters_per_second_t>();
    Vector3_CanCalculateVectorDotProductAngularAcc<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanCalculateVectorDotProductAngularAcc<units::angular_velocity::radians_per_second_t>();
    Vector3_CanCalculateVectorDotProductAngularAcc<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanCalculateVectorDotProductAngularAcc<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanCalculateVectorDotProductAngularAcc<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanCalculateVectorDotProductAngularAcc<units::force::newton_t>();
    Vector3_CanCalculateVectorDotProductAngularAcc<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanCalculateDotProductDimensionless()
{
    mc::Vector3<T> v1(T{1}, T{2}, T{3});
    mc::Vector3d v2(4.0, 5.0, 6.0);

    T s12 = v1 * v2;
    T s21 = v2 * v1;

    // expected values calculated with wxMaxima
    // tests/mcsim/utils/math/python/test_vector3_dot_product.py
    EXPECT_NEAR(s12(), 32.0, TOLERANCE);
    EXPECT_NEAR(s21(), 32.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanCalculateDotProductDimensionless)
{
    Vector3_CanCalculateDotProductDimensionless<units::length::meter_t>();
    Vector3_CanCalculateDotProductDimensionless<units::velocity::meters_per_second_t>();
    Vector3_CanCalculateDotProductDimensionless<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanCalculateDotProductDimensionless<units::angular_velocity::radians_per_second_t>();
    Vector3_CanCalculateDotProductDimensionless<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanCalculateDotProductDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanCalculateDotProductDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanCalculateDotProductDimensionless<units::force::newton_t>();
    Vector3_CanCalculateDotProductDimensionless<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanDivideByScalar()
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

TEST_F(TestVector3WithUnits, CanDivideByScalar)
{
    Vector3_CanDivideByScalar<units::length::meter_t>();
    Vector3_CanDivideByScalar<units::velocity::meters_per_second_t>();
    Vector3_CanDivideByScalar<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanDivideByScalar<units::angular_velocity::radians_per_second_t>();
    Vector3_CanDivideByScalar<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanDivideByScalar<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanDivideByScalar<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanDivideByScalar<units::force::newton_t>();
    Vector3_CanDivideByScalar<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanDivideByScalarDimensionlessVector)
{
    mc::Vector3<double> v(1.0, 2.0, 3.0);

    constexpr units::time::second_t val = 2.0_s;
    mc::Vector3<units::frequency::hertz_t> vr = v / val;

    EXPECT_NEAR(vr.x()(), 0.5, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 1.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 1.5, TOLERANCE);
}

template <typename T>
void Vector3_CanDivideByScalarDimensionless()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});

    double val = 2.0;

    mc::Vector3<T> vr = v / val;

    EXPECT_NEAR(vr.x()(), 0.5, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 1.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 1.5, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanDivideByScalarDimensionless)
{
    Vector3_CanDivideByScalarDimensionless<units::length::meter_t>();
    Vector3_CanDivideByScalarDimensionless<units::velocity::meters_per_second_t>();
    Vector3_CanDivideByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanDivideByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
    Vector3_CanDivideByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanDivideByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanDivideByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanDivideByScalarDimensionless<units::force::newton_t>();
    Vector3_CanDivideByScalarDimensionless<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanCalculateVectorCrossProduct()
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
    // tests/mcsim/utils/math/octave/test_vector3_cross_product.m
    EXPECT_NEAR(vr.x()(), -3.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(),  6.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), -3.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanCalculateVectorCrossProduct)
{
    Vector3_CanCalculateVectorCrossProduct<units::length::meter_t>();
    Vector3_CanCalculateVectorCrossProduct<units::velocity::meters_per_second_t>();
    Vector3_CanCalculateVectorCrossProduct<units::acceleration::meters_per_second_squared_t>();

    // angular velocity and angular acceleration excluded from this test
    // because they are treated in a special way

    Vector3_CanCalculateVectorCrossProduct<units::force::newton_t>();
    Vector3_CanCalculateVectorCrossProduct<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanCalculateVectorCrossProductAngularVel()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});

    mc::Vector3<units::angular_velocity::radians_per_second_t>
        omega(4.0_rad_per_s, 5.0_rad_per_s, 6.0_rad_per_s);

    mc::Vector3<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_t>::unit_type
            >
        >
    > v1, v2;

    v1 = v % omega;
    v2 = omega % v;

    // expected values calculated with wxMaxima
    // tests/mcsim/utils/math/octave/test_vector3_cross_product.m
    EXPECT_NEAR(v1.x()(), -3.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(),  6.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), -3.0, TOLERANCE);

    EXPECT_NEAR(v2.x()(),  3.0, TOLERANCE);
    EXPECT_NEAR(v2.y()(), -6.0, TOLERANCE);
    EXPECT_NEAR(v2.z()(),  3.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanCalculateVectorCrossProductAngularVel)
{
    Vector3_CanCalculateVectorCrossProductAngularVel<units::length::meter_t>();
    Vector3_CanCalculateVectorCrossProductAngularVel<units::velocity::meters_per_second_t>();
    Vector3_CanCalculateVectorCrossProductAngularVel<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanCalculateVectorCrossProductAngularVel<units::angular_velocity::radians_per_second_t>();
    Vector3_CanCalculateVectorCrossProductAngularVel<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanCalculateVectorCrossProductAngularVel<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanCalculateVectorCrossProductAngularVel<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanCalculateVectorCrossProductAngularVel<units::force::newton_t>();
    Vector3_CanCalculateVectorCrossProductAngularVel<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanCalculateVectorCrossProductAngularAcc()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});

    mc::Vector3<units::angular_acceleration::radians_per_second_squared_t>
        omega(4.0_rad_per_s_sq, 5.0_rad_per_s_sq, 6.0_rad_per_s_sq);

    mc::Vector3<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_squared_t>::unit_type
            >
        >
    > v1, v2;

    v1 = v % omega;
    v2 = omega % v;

    // expected values calculated with wxMaxima
    // tests/mcsim/utils/math/octave/test_vector3_cross_product.m
    EXPECT_NEAR(v1.x()(), -3.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(),  6.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), -3.0, TOLERANCE);

    EXPECT_NEAR(v2.x()(),  3.0, TOLERANCE);
    EXPECT_NEAR(v2.y()(), -6.0, TOLERANCE);
    EXPECT_NEAR(v2.z()(),  3.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanCalculateVectorCrossProductAngularAcc)
{
    Vector3_CanCalculateVectorCrossProductAngularAcc<units::length::meter_t>();
    Vector3_CanCalculateVectorCrossProductAngularAcc<units::velocity::meters_per_second_t>();
    Vector3_CanCalculateVectorCrossProductAngularAcc<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanCalculateVectorCrossProductAngularAcc<units::angular_velocity::radians_per_second_t>();
    Vector3_CanCalculateVectorCrossProductAngularAcc<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanCalculateVectorCrossProductAngularAcc<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanCalculateVectorCrossProductAngularAcc<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanCalculateVectorCrossProductAngularAcc<units::force::newton_t>();
    Vector3_CanCalculateVectorCrossProductAngularAcc<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanCalculateVectorCrossProductDimensionless()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});

    mc::Vector3d vd(4.0, 5.0, 6.0);

    mc::Vector3<T>v1 = v % vd;
    mc::Vector3<T>v2 = vd % v;

    // expected values calculated with wxMaxima
    // tests/mcsim/utils/math/octave/test_vector3_cross_product.m
    EXPECT_NEAR(v1.x()(), -3.0, TOLERANCE);
    EXPECT_NEAR(v1.y()(),  6.0, TOLERANCE);
    EXPECT_NEAR(v1.z()(), -3.0, TOLERANCE);

    EXPECT_NEAR(v2.x()(),  3.0, TOLERANCE);
    EXPECT_NEAR(v2.y()(), -6.0, TOLERANCE);
    EXPECT_NEAR(v2.z()(),  3.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanCalculateVectorCrossProductDimensionless)
{
    Vector3_CanCalculateVectorCrossProductDimensionless<units::length::meter_t>();
    Vector3_CanCalculateVectorCrossProductDimensionless<units::velocity::meters_per_second_t>();
    Vector3_CanCalculateVectorCrossProductDimensionless<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanCalculateVectorCrossProductDimensionless<units::angular_velocity::radians_per_second_t>();
    Vector3_CanCalculateVectorCrossProductDimensionless<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanCalculateVectorCrossProductDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanCalculateVectorCrossProductDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanCalculateVectorCrossProductDimensionless<units::force::newton_t>();
    Vector3_CanCalculateVectorCrossProductDimensionless<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanUnaryAdd()
{
    mc::Vector3<T> v0(T{1}, T{2}, T{3});
    mc::Vector3<T> v1(T{2}, T{3}, T{4});

    v0 += v1;

    EXPECT_NEAR(v0.x()(), 3.0, TOLERANCE);
    EXPECT_NEAR(v0.y()(), 5.0, TOLERANCE);
    EXPECT_NEAR(v0.z()(), 7.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanUnaryAdd)
{
    Vector3_CanUnaryAdd<units::length::meter_t>();
    Vector3_CanUnaryAdd<units::velocity::meters_per_second_t>();
    Vector3_CanUnaryAdd<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanUnaryAdd<units::angular_velocity::radians_per_second_t>();
    Vector3_CanUnaryAdd<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanUnaryAdd<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanUnaryAdd<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanUnaryAdd<units::force::newton_t>();
    Vector3_CanUnaryAdd<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanUnarySubtract()
{
    mc::Vector3<T> v0(T{3}, T{5}, T{7});
    mc::Vector3<T> v1(T{2}, T{3}, T{4});

    v0 -= v1;

    EXPECT_NEAR(v0.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v0.y()(), 2.0, TOLERANCE);
    EXPECT_NEAR(v0.z()(), 3.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanUnarySubtract)
{
    Vector3_CanUnarySubtract<units::length::meter_t>();
    Vector3_CanUnarySubtract<units::velocity::meters_per_second_t>();
    Vector3_CanUnarySubtract<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanUnarySubtract<units::angular_velocity::radians_per_second_t>();
    Vector3_CanUnarySubtract<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanUnarySubtract<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanUnarySubtract<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanUnarySubtract<units::force::newton_t>();
    Vector3_CanUnarySubtract<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanUnaryMultiplyByScalarDimensionless()
{
    mc::Vector3<T> v0(T{2}, T{4}, T{6});

    v0 *= 0.5;

    EXPECT_NEAR(v0.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v0.y()(), 2.0, TOLERANCE);
    EXPECT_NEAR(v0.z()(), 3.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanUnaryMultiplyByScalarDimensionless)
{
    Vector3_CanUnaryMultiplyByScalarDimensionless<units::length::meter_t>();
    Vector3_CanUnaryMultiplyByScalarDimensionless<units::velocity::meters_per_second_t>();
    Vector3_CanUnaryMultiplyByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanUnaryMultiplyByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
    Vector3_CanUnaryMultiplyByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanUnaryMultiplyByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanUnaryMultiplyByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanUnaryMultiplyByScalarDimensionless<units::force::newton_t>();
    Vector3_CanUnaryMultiplyByScalarDimensionless<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanUnaryDivideByScalarDimensionless()
{
    mc::Vector3<T> v0(T{2}, T{4}, T{6});

    v0 /= 2.0;

    EXPECT_NEAR(v0.x()(), 1.0, TOLERANCE);
    EXPECT_NEAR(v0.y()(), 2.0, TOLERANCE);
    EXPECT_NEAR(v0.z()(), 3.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanUnaryDivideByScalarDimensionless)
{
    Vector3_CanUnaryDivideByScalarDimensionless<units::length::meter_t>();
    Vector3_CanUnaryDivideByScalarDimensionless<units::velocity::meters_per_second_t>();
    Vector3_CanUnaryDivideByScalarDimensionless<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanUnaryDivideByScalarDimensionless<units::angular_velocity::radians_per_second_t>();
    Vector3_CanUnaryDivideByScalarDimensionless<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanUnaryDivideByScalarDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanUnaryDivideByScalarDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanUnaryDivideByScalarDimensionless<units::force::newton_t>();
    Vector3_CanUnaryDivideByScalarDimensionless<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanMultiplyScalarByVector()
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

TEST_F(TestVector3WithUnits, CanMultiplyScalarByVector)
{
    Vector3_CanMultiplyScalarByVector<units::length::meter_t>();
    Vector3_CanMultiplyScalarByVector<units::velocity::meters_per_second_t>();
    Vector3_CanMultiplyScalarByVector<units::acceleration::meters_per_second_squared_t>();

    // angular velocity and angular acceleration excluded from this test
    // because they are treated in a special way

    Vector3_CanMultiplyScalarByVector<units::force::newton_t>();
    Vector3_CanMultiplyScalarByVector<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanMultiplyScalarByVectorTime()
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
    > vr = val * v;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanMultiplyScalarByVectorTime)
{
    Vector3_CanMultiplyScalarByVectorTime<units::length::meter_t>();
    Vector3_CanMultiplyScalarByVectorTime<units::velocity::meters_per_second_t>();
    Vector3_CanMultiplyScalarByVectorTime<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanMultiplyScalarByVectorTime<units::angular_velocity::radians_per_second_t>();
    Vector3_CanMultiplyScalarByVectorTime<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanMultiplyScalarByVectorTime<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanMultiplyScalarByVectorTime<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanMultiplyScalarByVectorTime<units::force::newton_t>();
    Vector3_CanMultiplyScalarByVectorTime<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanMultiplyScalarByVectorAngularVel()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});

    units::angular_velocity::degrees_per_second_t val = 2.0_rad_per_s;

    mc::Vector3<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_t>::unit_type
            >
        >
    > vr = val * v;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanMultiplyScalarByVectorAngularVel)
{
    Vector3_CanMultiplyScalarByVectorAngularVel<units::length::meter_t>();
    Vector3_CanMultiplyScalarByVectorAngularVel<units::velocity::meters_per_second_t>();
    Vector3_CanMultiplyScalarByVectorAngularVel<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanMultiplyScalarByVectorAngularVel<units::angular_velocity::radians_per_second_t>();
    Vector3_CanMultiplyScalarByVectorAngularVel<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanMultiplyScalarByVectorAngularVel<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanMultiplyScalarByVectorAngularVel<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanMultiplyScalarByVectorAngularVel<units::force::newton_t>();
    Vector3_CanMultiplyScalarByVectorAngularVel<units::torque::newton_meter_t>();
}

template <typename T>
void Vector3_CanMultiplyScalarByVectorAngularAcc()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});

    units::angular_acceleration::degrees_per_second_squared_t val = 2.0_rad_per_s_sq;

    mc::Vector3<
        units::unit_t<
        units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_squared_t>::unit_type
            >
        >
    > vr = val * v;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanMultiplyScalarByVectorAngularAcc)
{
    Vector3_CanMultiplyScalarByVectorAngularAcc<units::length::meter_t>();
    Vector3_CanMultiplyScalarByVectorAngularAcc<units::velocity::meters_per_second_t>();
    Vector3_CanMultiplyScalarByVectorAngularAcc<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanMultiplyScalarByVectorAngularAcc<units::angular_velocity::radians_per_second_t>();
    Vector3_CanMultiplyScalarByVectorAngularAcc<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanMultiplyScalarByVectorAngularAcc<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanMultiplyScalarByVectorAngularAcc<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanMultiplyScalarByVectorAngularAcc<units::force::newton_t>();
    Vector3_CanMultiplyScalarByVectorAngularAcc<units::torque::newton_meter_t>();
}

TEST_F(TestVector3WithUnits, CanMultiplyScalarByVectorDimensionlessVector)
{
    mc::Vector3d v(1.0, 2.0, 3.0);
    mc::Vector3<units::length::meter_t> vr = 2.0_m * v;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

template <typename T>
void Vector3_CanMultiplyScalarByVectorDimensionless()
{
    mc::Vector3<T> v(T{1}, T{2}, T{3});
    mc::Vector3<T> vr = 2.0 * v;

    EXPECT_NEAR(vr.x()(), 2.0, TOLERANCE);
    EXPECT_NEAR(vr.y()(), 4.0, TOLERANCE);
    EXPECT_NEAR(vr.z()(), 6.0, TOLERANCE);
}

TEST_F(TestVector3WithUnits, CanMultiplyScalarByVectorDimensionless)
{
    Vector3_CanMultiplyScalarByVectorDimensionless<units::length::meter_t>();
    Vector3_CanMultiplyScalarByVectorDimensionless<units::velocity::meters_per_second_t>();
    Vector3_CanMultiplyScalarByVectorDimensionless<units::acceleration::meters_per_second_squared_t>();
    Vector3_CanMultiplyScalarByVectorDimensionless<units::angular_velocity::radians_per_second_t>();
    Vector3_CanMultiplyScalarByVectorDimensionless<units::angular_velocity::degrees_per_second_t>();
    Vector3_CanMultiplyScalarByVectorDimensionless<units::angular_acceleration::radians_per_second_squared_t>();
    Vector3_CanMultiplyScalarByVectorDimensionless<units::angular_acceleration::degrees_per_second_squared_t>();
    Vector3_CanMultiplyScalarByVectorDimensionless<units::force::newton_t>();
    Vector3_CanMultiplyScalarByVectorDimensionless<units::torque::newton_meter_t>();
}