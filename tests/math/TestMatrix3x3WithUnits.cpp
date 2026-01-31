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

namespace test {
namespace Matrix3x3 {

template <typename T>
void CanGetIdentityMatrix()
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

template <typename T>
void CanInstantiate()
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

template <typename T>
void CanInstantiateAndSetData()
{
    mc::Matrix3x3<T> m( 
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    );

    EXPECT_DOUBLE_EQ(m(0,0)(), 1.0);
    EXPECT_DOUBLE_EQ(m(0,1)(), 2.0);
    EXPECT_DOUBLE_EQ(m(0,2)(), 3.0);

    EXPECT_DOUBLE_EQ(m(1,0)(), 4.0);
    EXPECT_DOUBLE_EQ(m(1,1)(), 5.0);
    EXPECT_DOUBLE_EQ(m(1,2)(), 6.0);

    EXPECT_DOUBLE_EQ(m(2,0)(), 7.0);
    EXPECT_DOUBLE_EQ(m(2,1)(), 8.0);
    EXPECT_DOUBLE_EQ(m(2,2)(), 9.0);
}

template <typename T>
void CanGetTransposed()
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

template <typename T>
void CanTranspose()
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

template <typename T1, typename T2>
void CanCastToOtherMatrixType()
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

template <typename T>
void CanAdd()
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

template <typename T1, typename T2>
void CanAddDifferentTypes()
{
    constexpr T2 val = T1{2};

    std::vector<T1> x
    {
        T1{1}, T1{2}, T1{3},
        T1{4}, T1{5}, T1{6},
        T1{7}, T1{8}, T1{9}
    };

    mc::Matrix3x3<T1> m1;
    mc::Matrix3x3<T2> m2;
    mc::Matrix3x3<T1> mr;
    m1.setFromStdVector(x);
    m2.fill(val);
    mr = m2 + m1;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            T1 ref = val + x[r*SIZE + c];
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref()) << "Error at row " << r << " and col " << c;
        }
    }
}

template <typename T>
void CanNegate()
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

template <typename T>
void CanSubtract()
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

template <typename T1, typename T2>
void CanSubtractDifferentTypes()
{
    constexpr T2 val = T1{2};

    std::vector<T1> x
    {
        T1{1}, T1{2}, T1{3},
        T1{4}, T1{5}, T1{6},
        T1{7}, T1{8}, T1{9}
    };

    mc::Matrix3x3<T1> m1;
    mc::Matrix3x3<T2> m2;
    mc::Matrix3x3<T1> mr;
    m1.setFromStdVector(x);
    m2.fill(val);
    mr = m2 - m1;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            T1 ref = val - x[r*SIZE + c];
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref()) << "Error at row " << r << " and col " << c;
        }
    }
}

template <typename T>
void CanMultiplyByScalar()
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

template <typename T>
void CanMultiplyByAngularVelScalar()
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
                typename units::traits::unit_t_traits<units::inverted::per_second_t>::unit_type
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

template <typename T>
void CanMultiplyByAngularAccScalar()
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
                typename units::traits::unit_t_traits<units::inverted::per_second_squared_t>::unit_type
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

template <typename T>
void CanMultiplyByDimensionlessScalar()
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

template <typename T>
void CanMultiplyMatrixByVector()
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

template <typename T>
void CanMultiplyMatrixByAngularVelVector()
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
                typename units::traits::unit_t_traits<units::inverted::per_second_t>::unit_type
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

template <typename T>
void CanMultiplyMatrixByAngularAccVector()
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
                typename units::traits::unit_t_traits<units::inverted::per_second_squared_t>::unit_type
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

template <typename T>
void CanMultiplyMatrixByDimensionlessVector()
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

template <typename T>
void CanMultiplyMatrixByMatrix()
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

template <typename T>
void CanMultiplyDimensionlessMatrixByMatrix()
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

template <typename T>
void CanDivideByScalar()
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

template <typename T>
void CanDivideByDimensionlessScalar()
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

template <typename T>
void CanUnaryAdd()
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

template <typename T1, typename T2>
void CanUnaryAddDifferentTypes()
{
    constexpr T2 val = T1{2};

    std::vector<T1> x
    {
        T1{1}, T1{2}, T1{3},
        T1{4}, T1{5}, T1{6},
        T1{7}, T1{8}, T1{9}
    };

    mc::Matrix3x3<T1> m1;
    mc::Matrix3x3<T2> m2;
    m1.setFromStdVector(x);
    m2.fill(val);
    m1 += m2;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            T1 ref = x[r*SIZE + c] + val;
            EXPECT_DOUBLE_EQ(m1(r,c)(), ref()) << "Error at row " << r << " and col " << c;
        }
    }
}

template <typename T>
void CanUnarySubtract()
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

template <typename T1, typename T2>
void CanUnarySubtractDifferentTypes()
{
    constexpr T2 val = T1{2};

    std::vector<T1> x
    {
        T1{1}, T1{2}, T1{3},
        T1{4}, T1{5}, T1{6},
        T1{7}, T1{8}, T1{9}
    };

    mc::Matrix3x3<T1> m1;
    mc::Matrix3x3<T2> m2;
    m1.setFromStdVector(x);
    m2.fill(val);
    m1 -= m2;

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            T1 ref = x[r*SIZE + c] - val;
            EXPECT_DOUBLE_EQ(m1(r,c)(), ref()) << "Error at row " << r << " and col " << c;
        }
    }
}

template <typename T>
void CanUnaryMultiplyByDimensionlessScalar()
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

template <typename T>
void CanUnaryDivideByDimensionlessScalar()
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

template <typename T>
void CanCompare()
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

template <typename T>
void CanMultiplyScalarByMatrix()
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

template <typename T>
void CanMultiplyScalarByMatrixAngularVel()
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
                typename units::traits::unit_t_traits<units::inverted::per_second_t>::unit_type
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

template <typename T>
void CanMultiplyScalarByMatrixAngularAcc()
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
                typename units::traits::unit_t_traits<units::inverted::per_second_squared_t>::unit_type
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

template <typename T>
void CanMultiplyScalarByMatrixDimensionless()
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

} // namespace Matrix3x3
} // namespace test

TEST_F(TestMatrix3x3WithUnits, CanGetIdentityMatrix)
{
    test::Matrix3x3::CanGetIdentityMatrix<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanInstantiate)
{
    test::Matrix3x3::CanInstantiate<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanInstantiateAndSetData)
{
        test::Matrix3x3::CanInstantiateAndSetData<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanInstantiateAndSetDataDifferentTypes)
{
    units::moment_of_inertia::kilogram_meter_squared_t xx = 1.0_kg_m_sq;
    units::moment_of_inertia::slug_foot_squared_t      xy = 2.0_kg_m_sq;
    units::moment_of_inertia::kilogram_meter_squared_t xz = 3.0_kg_m_sq;
    units::moment_of_inertia::slug_foot_squared_t      yx = 4.0_kg_m_sq;
    units::moment_of_inertia::kilogram_meter_squared_t yy = 5.0_kg_m_sq;
    units::moment_of_inertia::slug_foot_squared_t      yz = 6.0_kg_m_sq;
    units::moment_of_inertia::kilogram_meter_squared_t zx = 7.0_kg_m_sq;
    units::moment_of_inertia::slug_foot_squared_t      zy = 8.0_kg_m_sq;
    units::moment_of_inertia::kilogram_meter_squared_t zz = 9.0_kg_m_sq;

    mc::Matrix3x3<units::moment_of_inertia::kilogram_meter_squared_t> m( 
        xx, xy, xz,
        yx, yy, yz,
        zx, zy, zz
    );

    EXPECT_DOUBLE_EQ(m(0,0)(), 1.0);
    EXPECT_DOUBLE_EQ(m(0,1)(), 2.0);
    EXPECT_DOUBLE_EQ(m(0,2)(), 3.0);

    EXPECT_DOUBLE_EQ(m(1,0)(), 4.0);
    EXPECT_DOUBLE_EQ(m(1,1)(), 5.0);
    EXPECT_DOUBLE_EQ(m(1,2)(), 6.0);

    EXPECT_DOUBLE_EQ(m(2,0)(), 7.0);
    EXPECT_DOUBLE_EQ(m(2,1)(), 8.0);
    EXPECT_DOUBLE_EQ(m(2,2)(), 9.0);
}

TEST_F(TestMatrix3x3WithUnits, CanGetTransposed)
{
    test::Matrix3x3::CanGetTransposed<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanTranspose)
{
    test::Matrix3x3::CanTranspose<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanCastToOtherMatrixType)
{
    test::Matrix3x3::CanCastToOtherMatrixType<
        units::moment_of_inertia::kilogram_meter_squared_t,
        units::moment_of_inertia::slug_foot_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanAdd)
{
    test::Matrix3x3::CanAdd<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanAddDifferentTypes)
{
    test::Matrix3x3::CanAddDifferentTypes<
        units::moment_of_inertia::kilogram_meter_squared_t,
        units::moment_of_inertia::slug_foot_squared_t
    >();
}

TEST_F(TestMatrix3x3WithUnits, CanNegate)
{
    test::Matrix3x3::CanNegate<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanSubtract)
{
    test::Matrix3x3::CanSubtract<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanSubtractDifferentTypes)
{
    test::Matrix3x3::CanSubtractDifferentTypes<
        units::moment_of_inertia::kilogram_meter_squared_t,
        units::moment_of_inertia::slug_foot_squared_t
    >();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyByScalar)
{
    test::Matrix3x3::CanMultiplyByScalar<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyByAngularVelScalar)
{
    test::Matrix3x3::CanMultiplyByAngularVelScalar<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyByAngularAccScalar)
{
    test::Matrix3x3::CanMultiplyByAngularAccScalar<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyByDimensionlessScalar)
{
    test::Matrix3x3::CanMultiplyByDimensionlessScalar<units::moment_of_inertia::kilogram_meter_squared_t>();
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

TEST_F(TestMatrix3x3WithUnits, CanMultiplyMatrixByVector)
{
    test::Matrix3x3::CanMultiplyMatrixByVector<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyMatrixByAngularVelVector)
{
    test::Matrix3x3::CanMultiplyMatrixByAngularVelVector<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyMatrixByAngularAccVector)
{
    test::Matrix3x3::CanMultiplyMatrixByAngularAccVector<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyMatrixByDimensionlessVector)
{
    test::Matrix3x3::CanMultiplyMatrixByDimensionlessVector<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyDimensionlessMatrixByVector)
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

TEST_F(TestMatrix3x3WithUnits, CanMultiplyMatrixByMatrix)
{
    test::Matrix3x3::CanMultiplyMatrixByMatrix<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyDimensionlessMatrixByMatrix)
{
    test::Matrix3x3::CanMultiplyDimensionlessMatrixByMatrix<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanDivideByScalar)
{
    test::Matrix3x3::CanDivideByScalar<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanDivideByDimensionlessScalar)
{
    test::Matrix3x3::CanDivideByDimensionlessScalar<units::moment_of_inertia::kilogram_meter_squared_t>();
}


TEST_F(TestMatrix3x3WithUnits, CanDivideDimensionlessMatrixByScalar)
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

TEST_F(TestMatrix3x3WithUnits, CanUnaryAdd)
{
    test::Matrix3x3::CanUnaryAdd<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanUnaryAddDifferentTypes)
{
    test::Matrix3x3::CanUnaryAddDifferentTypes<
        units::moment_of_inertia::kilogram_meter_squared_t,
        units::moment_of_inertia::slug_foot_squared_t
    >();
}

TEST_F(TestMatrix3x3WithUnits, CanUnarySubtract)
{
    test::Matrix3x3::CanUnarySubtract<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanUnarySubtractDifferentTypes)
{
    test::Matrix3x3::CanUnarySubtractDifferentTypes<
        units::moment_of_inertia::kilogram_meter_squared_t,
        units::moment_of_inertia::slug_foot_squared_t
    >();
}

TEST_F(TestMatrix3x3WithUnits, CanUnaryMultiplyByDimensionlessScalar)
{
    test::Matrix3x3::CanUnaryMultiplyByDimensionlessScalar<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanUnaryDivideByDimensionlessScalar)
{
    test::Matrix3x3::CanUnaryDivideByDimensionlessScalar<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanCompare)
{
    test::Matrix3x3::CanCompare<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyScalarByMatrix)
{
    test::Matrix3x3::CanMultiplyScalarByMatrix<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyScalarByMatrixAngularVel)
{
    test::Matrix3x3::CanMultiplyScalarByMatrixAngularVel<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyScalarByMatrixAngularAcc)
{
    test::Matrix3x3::CanMultiplyScalarByMatrixAngularAcc<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrix3x3WithUnits, CanMultiplyScalarByMatrixDimensionless)
{
    test::Matrix3x3::CanMultiplyScalarByMatrixDimensionless<units::moment_of_inertia::kilogram_meter_squared_t>();
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
