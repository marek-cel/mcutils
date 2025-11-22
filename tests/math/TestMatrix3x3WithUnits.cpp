#include <gtest/gtest.h>

#include <mcutils/math/Matrix.h>

#define SIZE 3
#define TOLERANCE 1.0e-12

using namespace units::literals;

class TestMatrix3x3WithUnits : public ::testing::Test
{
protected:
    constexpr static int size = 3;
    TestMatrix3x3WithUnits() {}
    virtual ~TestMatrix3x3WithUnits() {}
    void SetUp() override {}
    void TearDown() override {}
};

template <typename T>
void Matrix3x3_CanGetIdentityMatrix()
{
    mc::Matrix3x3<T> m = mc::Matrix3x3<T>::getIdentityMatrix();

    EXPECT_DOUBLE_EQ(m(0,0)(), 1.0);
    EXPECT_DOUBLE_EQ(m(0,1)(), 0.0);
    EXPECT_DOUBLE_EQ(m(0,2)(), 0.0);

    EXPECT_DOUBLE_EQ(m(1,0)(), 0.0);
    EXPECT_DOUBLE_EQ(m(1,1)(), 1.0);
    EXPECT_DOUBLE_EQ(m(1,2)(), 0.0);

    EXPECT_DOUBLE_EQ(m(2,0)(), 0.0);
    EXPECT_DOUBLE_EQ(m(2,1)(), 0.0);
    EXPECT_DOUBLE_EQ(m(2,2)(), 1.0);
}

TEST_F(TestMatrix3x3WithUnits, CanGetIdentityMatrix)
{
    Matrix3x3_CanGetIdentityMatrix<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanInstantiate()
{
    mc::Matrix3x3<T> m;

    EXPECT_DOUBLE_EQ(m(0,0)(), 0.0);
    EXPECT_DOUBLE_EQ(m(0,1)(), 0.0);
    EXPECT_DOUBLE_EQ(m(0,2)(), 0.0);

    EXPECT_DOUBLE_EQ(m(1,0)(), 0.0);
    EXPECT_DOUBLE_EQ(m(1,1)(), 0.0);
    EXPECT_DOUBLE_EQ(m(1,2)(), 0.0);

    EXPECT_DOUBLE_EQ(m(2,0)(), 0.0);
    EXPECT_DOUBLE_EQ(m(2,1)(), 0.0);
    EXPECT_DOUBLE_EQ(m(2,2)(), 0.0);
}

TEST_F(TestMatrix3x3WithUnits, CanInstantiate)
{
    Matrix3x3_CanInstantiate<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanGetTransposed()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };
    mc::Matrix3x3<T> m;
    m.setFromStdVector(x);

    mc::Matrix3x3<T> mt = m.getTransposed();

    EXPECT_DOUBLE_EQ(mt(0,0)(), 1.0);
    EXPECT_DOUBLE_EQ(mt(0,1)(), 4.0);
    EXPECT_DOUBLE_EQ(mt(0,2)(), 7.0);

    EXPECT_DOUBLE_EQ(mt(1,0)(), 2.0);
    EXPECT_DOUBLE_EQ(mt(1,1)(), 5.0);
    EXPECT_DOUBLE_EQ(mt(1,2)(), 8.0);

    EXPECT_DOUBLE_EQ(mt(2,0)(), 3.0);
    EXPECT_DOUBLE_EQ(mt(2,1)(), 6.0);
    EXPECT_DOUBLE_EQ(mt(2,2)(), 9.0);
}

TEST_F(TestMatrix3x3WithUnits, CanGetTransposed)
{
    Matrix3x3_CanGetTransposed<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanTranspose()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };
    mc::Matrix3x3<T> m;
    m.setFromStdVector(x);

    m.transpose();

    EXPECT_DOUBLE_EQ(m(0,0)(), 1.0);
    EXPECT_DOUBLE_EQ(m(0,1)(), 4.0);
    EXPECT_DOUBLE_EQ(m(0,2)(), 7.0);

    EXPECT_DOUBLE_EQ(m(1,0)(), 2.0);
    EXPECT_DOUBLE_EQ(m(1,1)(), 5.0);
    EXPECT_DOUBLE_EQ(m(1,2)(), 8.0);

    EXPECT_DOUBLE_EQ(m(2,0)(), 3.0);
    EXPECT_DOUBLE_EQ(m(2,1)(), 6.0);
    EXPECT_DOUBLE_EQ(m(2,2)(), 9.0);
}

TEST_F(TestMatrix3x3WithUnits, CanTranspose)
{
    Matrix3x3_CanTranspose<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanGetDimensionless()
{
    mc::Matrix3x3<T> m1;

    m1(0,0) = T{1};
    m1(0,1) = T{2};
    m1(0,2) = T{3};

    m1(1,0) = T{4};
    m1(1,1) = T{5};
    m1(1,2) = T{6};

    m1(2,0) = T{7};
    m1(2,1) = T{8};
    m1(2,2) = T{9};

    mc::Matrix3x3<double> m2;
    m2 = m1.getDimensionless();

    EXPECT_NEAR(m2(0,0), 1.0, TOLERANCE);
    EXPECT_NEAR(m2(0,1), 2.0, TOLERANCE);
    EXPECT_NEAR(m2(0,2), 3.0, TOLERANCE);

    EXPECT_NEAR(m2(1,0), 4.0, TOLERANCE);
    EXPECT_NEAR(m2(1,1), 5.0, TOLERANCE);
    EXPECT_NEAR(m2(1,2), 6.0, TOLERANCE);

    EXPECT_NEAR(m2(2,0), 7.0, TOLERANCE);
    EXPECT_NEAR(m2(2,1), 8.0, TOLERANCE);
    EXPECT_NEAR(m2(2,2), 9.0, TOLERANCE);
}

TEST_F(TestMatrix3x3WithUnits, GetDimensionless)
{
    Matrix3x3_CanGetDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T1, typename T2>
void Matrix3x3_CanCastToOtherMatrixType()
{
    mc::Matrix3x3<T1> m1;

    m1(0,0) = T2{1}; // sic!
    m1(0,1) = T2{2}; // sic!
    m1(0,2) = T2{3}; // sic!

    m1(1,0) = T2{4}; // sic!
    m1(1,1) = T2{5}; // sic!
    m1(1,2) = T2{6}; // sic!

    m1(2,0) = T2{7}; // sic!
    m1(2,1) = T2{8}; // sic!
    m1(2,2) = T2{9}; // sic!

    mc::Matrix3x3<T2> m2;
    m2 = m1;

    EXPECT_NEAR(m2(0,0)(), 1.0, TOLERANCE);
    EXPECT_NEAR(m2(0,1)(), 2.0, TOLERANCE);
    EXPECT_NEAR(m2(0,2)(), 3.0, TOLERANCE);

    EXPECT_NEAR(m2(1,0)(), 4.0, TOLERANCE);
    EXPECT_NEAR(m2(1,1)(), 5.0, TOLERANCE);
    EXPECT_NEAR(m2(1,2)(), 6.0, TOLERANCE);

    EXPECT_NEAR(m2(2,0)(), 7.0, TOLERANCE);
    EXPECT_NEAR(m2(2,1)(), 8.0, TOLERANCE);
    EXPECT_NEAR(m2(2,2)(), 9.0, TOLERANCE);
}

TEST_F(TestMatrix3x3WithUnits, CanCastToOtherMatrixType)
{
    Matrix3x3_CanCastToOtherMatrixType<
        units::moment_of_inertia::kilograms_meters_squared_t,
        units::moment_of_inertia::slugs_feet_squared_t>();
}

template <typename T>
void Matrix3x3_CanAdd()
{
    constexpr T val = T{2};

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    mc::Matrix3x3<T> m2;
    mc::Matrix3x3<T> mr;
    m1.setFromStdVector(x);
    m2.fill(val);
    mr = m1 + m2;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c]() + val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanAdd)
{
    Matrix3x3_CanAdd<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanNegate()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    mc::Matrix3x3<T> m2;
    mc::Matrix3x3<T> mr;
    m1.setFromStdVector(x);
    m2.setFromStdVector(x);
    mr = -m1;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c)(), -m2(r,c)()) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanNegate)
{
    Matrix3x3_CanNegate<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanSubtract()
{
    constexpr T val = T{2};

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    mc::Matrix3x3<T> m2;
    mc::Matrix3x3<T> mr;
    m1.setFromStdVector(x);
    m2.fill(val);
    mr = m1 - m2;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c]() - val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanSubtract)
{
    Matrix3x3_CanSubtract<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanMultiplyByScalar()
{
    constexpr units::length::meter_t val = 2.0_m;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    mc::Matrix3x3<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::length::meter
            >
        >
    > mr;
    m1.setFromStdVector(x);
    mr = m1 * val;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c]() * val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyByScalar)
{
    Matrix3x3_CanMultiplyByScalar<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanMultiplyByScalarAngularVel()
{
    constexpr units::angular_velocity::radians_per_second_t val = 2.0_rad_per_s;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    mc::Matrix3x3<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
            >
        >
    > mr;
    m1.setFromStdVector(x);
    mr = m1 * val;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c]() * val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyByScalarAngularVel)
{
    Matrix3x3_CanMultiplyByScalarAngularVel<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanMultiplyByScalarAngularAcc()
{
    constexpr units::angular_acceleration::radians_per_second_squared_t val = 2.0_rad_per_s_sq;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    mc::Matrix3x3<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
            >
        >
    > mr;
    m1.setFromStdVector(x);
    mr = m1 * val;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c]() * val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyByScalarAngularAcc)
{
    Matrix3x3_CanMultiplyByScalarAngularAcc<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanMultiplyByScalarDimensionless()
{
    constexpr double val = 2.0;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    mc::Matrix3x3<T> mr;
    m1.setFromStdVector(x);
    mr = m1 * val;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c]() * val;
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyByScalarDimensionless)
{
    Matrix3x3_CanMultiplyByScalarDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyByScalarDimensionlessMatrix)
{
    constexpr units::length::meter_t val = 2.0_m;

    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::Matrix3x3<double> m1;
    mc::Matrix3x3<units::length::meter_t> mr;
    m1.setFromStdVector(x);
    mr = m1 * val;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c] * val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

template <typename T>
void Matrix3x3_CanMultiplyMatrixByVector()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m;
    m.setFromStdVector(x);

    mc::Vector3<units::length::meter_t> v;
    v(0) = 1.0_m;
    v(1) = 2.0_m;
    v(2) = 3.0_m;

    mc::Vector3<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::length::meter
            >
        >
    > vr;

    vr = m * v;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0)(), 14.0);
    EXPECT_DOUBLE_EQ(vr(1)(), 32.0);
    EXPECT_DOUBLE_EQ(vr(2)(), 50.0);
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyMatrixByVector)
{
    Matrix3x3_CanMultiplyMatrixByVector<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanMultiplyMatrixByVectorAngularVel()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m;
    m.setFromStdVector(x);

    mc::Vector3<units::angular_velocity::radians_per_second_t> v;
    v(0) = 1.0_rad_per_s;
    v(1) = 2.0_rad_per_s;
    v(2) = 3.0_rad_per_s;

    mc::Vector3<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
            >
        >
    > vr;

    vr = m * v;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0)(), 14.0);
    EXPECT_DOUBLE_EQ(vr(1)(), 32.0);
    EXPECT_DOUBLE_EQ(vr(2)(), 50.0);
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyMatrixByVectorAngularVel)
{
    Matrix3x3_CanMultiplyMatrixByVectorAngularVel<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanMultiplyMatrixByVectorAngularAcc()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m;
    m.setFromStdVector(x);

    mc::Vector3<units::angular_acceleration::radians_per_second_squared_t> v;
    v(0) = 1.0_rad_per_s_sq;
    v(1) = 2.0_rad_per_s_sq;
    v(2) = 3.0_rad_per_s_sq;

    mc::Vector3<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
            >
        >
    > vr;

    vr = m * v;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0)(), 14.0);
    EXPECT_DOUBLE_EQ(vr(1)(), 32.0);
    EXPECT_DOUBLE_EQ(vr(2)(), 50.0);
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyMatrixByVectorAngularAcc)
{
    Matrix3x3_CanMultiplyMatrixByVectorAngularAcc<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanMultiplyMatrixByVectorDimensionless()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m;
    m.setFromStdVector(x);

    mc::Vector3<double> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::Vector3<T> vr;

    vr = m * v;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0)(), 14.0);
    EXPECT_DOUBLE_EQ(vr(1)(), 32.0);
    EXPECT_DOUBLE_EQ(vr(2)(), 50.0);
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyMatrixByVectorDimensionless)
{
    Matrix3x3_CanMultiplyMatrixByVectorDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyMatrixByVectorDimensionlessMatrix)
{
    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };
    mc::Matrix3x3<double> m;
    m.setFromStdVector(x);

    mc::Vector3<units::length::meter_t> v;
    v(0) = 1.0_m;
    v(1) = 2.0_m;
    v(2) = 3.0_m;

    mc::Vector3<units::length::meter_t> vr = m * v;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0)(), 14.0);
    EXPECT_DOUBLE_EQ(vr(1)(), 32.0);
    EXPECT_DOUBLE_EQ(vr(2)(), 50.0);
}

template <typename T>
void Matrix3x3_CanMultiplyMatrixByMatrix()
{
    std::vector<units::length::meter_t> x1
    {
        1.0_m, 2.0_m, 3.0_m,
        4.0_m, 5.0_m, 6.0_m,
        7.0_m, 8.0_m, 9.0_m
    };

    std::vector<T> x2
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<units::length::meter_t> m1;
    mc::Matrix3x3<T> m2;

    m1.setFromStdVector(x1);
    m2.setFromStdVector(x2);

    mc::Matrix3x3<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::length::meter_t>::unit_type
            >
        >
    > mr;

    mr = m1 * m2;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(mr(0,0)(),  30.0);
    EXPECT_DOUBLE_EQ(mr(0,1)(),  36.0);
    EXPECT_DOUBLE_EQ(mr(0,2)(),  42.0);

    EXPECT_DOUBLE_EQ(mr(1,0)(),  66.0);
    EXPECT_DOUBLE_EQ(mr(1,1)(),  81.0);
    EXPECT_DOUBLE_EQ(mr(1,2)(),  96.0);

    EXPECT_DOUBLE_EQ(mr(2,0)(), 102.0);
    EXPECT_DOUBLE_EQ(mr(2,1)(), 126.0);
    EXPECT_DOUBLE_EQ(mr(2,2)(), 150.0);
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyMatrixByMatrix)
{
    Matrix3x3_CanMultiplyMatrixByMatrix<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanMultiplyMatrixByMatrixDimensionless()
{
    std::vector<double> x1
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    std::vector<T> x2
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<double> m1;
    mc::Matrix3x3<T> m2;

    m1.setFromStdVector(x1);
    m2.setFromStdVector(x2);

    mc::Matrix3x3<T> mr12 = m1 * m2;
    mc::Matrix3x3<T> mr21 = m2 * m1;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m

    EXPECT_DOUBLE_EQ(mr12(0,0)(),  30.0);
    EXPECT_DOUBLE_EQ(mr12(0,1)(),  36.0);
    EXPECT_DOUBLE_EQ(mr12(0,2)(),  42.0);

    EXPECT_DOUBLE_EQ(mr12(1,0)(),  66.0);
    EXPECT_DOUBLE_EQ(mr12(1,1)(),  81.0);
    EXPECT_DOUBLE_EQ(mr12(1,2)(),  96.0);

    EXPECT_DOUBLE_EQ(mr12(2,0)(), 102.0);
    EXPECT_DOUBLE_EQ(mr12(2,1)(), 126.0);
    EXPECT_DOUBLE_EQ(mr12(2,2)(), 150.0);

    EXPECT_DOUBLE_EQ(mr21(0,0)(),  30.0);
    EXPECT_DOUBLE_EQ(mr21(0,1)(),  36.0);
    EXPECT_DOUBLE_EQ(mr21(0,2)(),  42.0);

    EXPECT_DOUBLE_EQ(mr21(1,0)(),  66.0);
    EXPECT_DOUBLE_EQ(mr21(1,1)(),  81.0);
    EXPECT_DOUBLE_EQ(mr21(1,2)(),  96.0);

    EXPECT_DOUBLE_EQ(mr21(2,0)(), 102.0);
    EXPECT_DOUBLE_EQ(mr21(2,1)(), 126.0);
    EXPECT_DOUBLE_EQ(mr21(2,2)(), 150.0);
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyMatrixByMatrixDimensionless)
{
    Matrix3x3_CanMultiplyMatrixByMatrixDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanDivideByScalar()
{
    constexpr units::length::meter_t val = 2.0_m;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    m1.setFromStdVector(x);

    mc::Matrix3x3<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::inverse<units::length::meter>
            >
        >
    > mr;

    mr = m1 / val;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c]() / val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanDivideByScalar)
{
    Matrix3x3_CanDivideByScalar<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanDivideByScalarDimensionless()
{
    constexpr double val = 2.0;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    m1.setFromStdVector(x);

    mc::Matrix3x3<T> mr = m1 / val;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c]() / val;
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanDivideByScalarDimensionless)
{
    Matrix3x3_CanDivideByScalarDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}


TEST_F(TestMatrix3x3WithUnits, CanDivideByScalarDimensionlessMatrix)
{
    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::Matrix3x3<double> m1;
    mc::Matrix3x3<units::frequency::hertz_t> mr;
    m1.setFromStdVector(x);
    mr = m1 / 1.0_s;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c)(), x[r*SIZE + c]) << "Error at row " << r << " and col " << c;
        }
    }
}

template <typename T>
void Matrix3x3_CanUnaryAdd()
{
    constexpr T val = T{2};

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    mc::Matrix3x3<T> mr;
    m1.setFromStdVector(x);
    mr.fill(val);
    mr += m1;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c)(), val() + m1(r,c)()) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanUnaryAdd)
{
    Matrix3x3_CanUnaryAdd<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanUnarySubtract()
{
    constexpr T val = T{2};

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    mc::Matrix3x3<T> mr;
    m1.setFromStdVector(x);
    mr.fill(val);
    mr -= m1;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c)(), val() - m1(r,c)()) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanUnarySubtract)
{
    Matrix3x3_CanUnarySubtract<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanUnaryMultiplyByScalarDimensionless()
{
    constexpr double val = 2.0;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    m1.setFromStdVector(x);

    m1 *= val;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c]() * val;
            EXPECT_DOUBLE_EQ(m1(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanUnaryMultiplyByScalarDimensionless)
{
    Matrix3x3_CanUnaryMultiplyByScalarDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanUnaryDivideByScalarDimensionless()
{
    constexpr double val = 2.0;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    m1.setFromStdVector(x);

    m1 /= val;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c]() / val;
            EXPECT_DOUBLE_EQ(m1(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanUnaryDivideByScalarDimensionless)
{
    Matrix3x3_CanUnaryDivideByScalarDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanCompare()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    mc::Matrix3x3<T> m2;
    mc::Matrix3x3<T> m3;

    m1.setFromStdVector(x);
    m2.setFromStdVector(x);
    m3.fill(T{123});

    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m1 != m3);
    EXPECT_FALSE(m1 != m2);
    EXPECT_FALSE(m1 == m3);
}

TEST_F(TestMatrix3x3WithUnits, CanCompare)
{
    Matrix3x3_CanCompare<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanMultiplyScalarByMatrix()
{
    constexpr units::length::meter_t val = 2.0_m;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    mc::Matrix3x3<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::length::meter
            >
        >
    > mr;
    m1.setFromStdVector(x);
    mr = val * m1;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c]() * val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyScalarByMatrix)
{
    Matrix3x3_CanMultiplyScalarByMatrix<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanMultiplyScalarByMatrixAngularVel()
{
    constexpr units::angular_velocity::radians_per_second_t val = 2.0_rad_per_s;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    mc::Matrix3x3<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
            >
        >
    > mr;
    m1.setFromStdVector(x);
    mr = m1 * val;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c]() * val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyScalarByMatrixAngularVel)
{
    Matrix3x3_CanMultiplyScalarByMatrixAngularVel<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanMultiplyScalarByMatrixAngularAcc()
{
    constexpr units::angular_acceleration::radians_per_second_squared_t val = 2.0_rad_per_s_sq;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    mc::Matrix3x3<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
            >
        >
    > mr;
    m1.setFromStdVector(x);
    mr = val * m1;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c]() * val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyScalarByMatrixAngularAcc)
{
    Matrix3x3_CanMultiplyScalarByMatrixAngularAcc<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void Matrix3x3_CanMultiplyScalarByMatrixDimensionless()
{
    constexpr double val = 2.0;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::Matrix3x3<T> m1;
    mc::Matrix3x3<T> mr;
    m1.setFromStdVector(x);
    mr = val * m1;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c]() * val;
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyScalarByMatrixDimensionless)
{
    Matrix3x3_CanMultiplyScalarByMatrixDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyScalarByMatrixDimensionlessMatrix)
{
    constexpr units::length::meter_t val = 2.0_m;

    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::Matrix3x3<double> m1;
    mc::Matrix3x3<units::length::meter_t> mr;
    m1.setFromStdVector(x);
    mr = val * m1;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            double ref = x[r*SIZE + c] * val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}
