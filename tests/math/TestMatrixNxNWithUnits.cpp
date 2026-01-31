#include <gtest/gtest.h>

#include <mcutils/math/Matrix.h>

#define SIZE 3
#define TOLERANCE 1.0e-12

using namespace units::literals;

class TestMatrixNxNWithUnits : public ::testing::Test
{
protected:
    TestMatrixNxNWithUnits() {}
    virtual ~TestMatrixNxNWithUnits() {}
    void SetUp() override {}
    void TearDown() override {}
};

namespace test {
namespace MatrixNxN {

template <typename T>
void CanGetIdentityMatrix()
{
    mc::MatrixNxN<T,SIZE> m = mc::MatrixNxN<T,SIZE>::getIdentityMatrix();

    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            if ( r == c )
            {
                EXPECT_DOUBLE_EQ(m(r,c)(), 1.0) << "Error at row " << r << " and col " << c;
            }
            else
            {
                EXPECT_DOUBLE_EQ(m(r,c)(), 0.0) << "Error at row " << r << " and col " << c;
            }
        }
    }
}

template <typename T>
void CanInstantiate()
{
    mc::MatrixNxN<T,SIZE> m;
    for ( unsigned int r = 0; r < SIZE; ++r )
    {
        for ( unsigned int c = 0; c < SIZE; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c)(), 0.0) << "Error at row " << r << " and col " << c;
        }
    }
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
    mc::MatrixNxN<T,SIZE> m;
    m.setFromStdVector(x);

    mc::MatrixNxN<T,SIZE> mt = m.getTransposed();

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
    mc::MatrixNxN<T,SIZE> m;
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
    mc::MatrixNxN<T1,SIZE> m1;

    m1(0,0) = T2{1}; // sic!
    m1(0,1) = T2{2}; // sic!
    m1(0,2) = T2{3}; // sic!

    m1(1,0) = T2{4}; // sic!
    m1(1,1) = T2{5}; // sic!
    m1(1,2) = T2{6}; // sic!

    m1(2,0) = T2{7}; // sic!
    m1(2,1) = T2{8}; // sic!
    m1(2,2) = T2{9}; // sic!

    mc::MatrixNxN<T2,SIZE> m2;
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

    mc::MatrixNxN<T,SIZE> m1;
    mc::MatrixNxN<T,SIZE> m2;
    mc::MatrixNxN<T,SIZE> mr;
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

template <typename T>
void CanNegate()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixNxN<T,SIZE> m1;
    mc::MatrixNxN<T,SIZE> m2;
    mc::MatrixNxN<T,SIZE> mr;
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

    mc::MatrixNxN<T,SIZE> m1;
    mc::MatrixNxN<T,SIZE> m2;
    mc::MatrixNxN<T,SIZE> mr;
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

    mc::MatrixNxN<T,SIZE> m1;
    mc::MatrixNxN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::length::meter
            >
        >,
        SIZE
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
void CanMultiplyByScalarAngularVel()
{
    constexpr units::angular_velocity::radians_per_second_t val = 2.0_rad_per_s;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixNxN<T,SIZE> m1;
    mc::MatrixNxN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_t>::unit_type
            >
        >,
        SIZE
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
void CanMultiplyByScalarAngularAcc()
{
    constexpr units::angular_acceleration::radians_per_second_squared_t val = 2.0_rad_per_s_sq;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixNxN<T,SIZE> m1;
    mc::MatrixNxN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_squared_t>::unit_type
            >
        >,
        SIZE
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
void CanMultiplyByScalarDimensionless()
{
    constexpr double val = 2.0;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixNxN<T,SIZE> m1;
    mc::MatrixNxN<T,SIZE> mr;
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

    mc::MatrixNxN<T,SIZE> m;
    m.setFromStdVector(x);

    mc::VectorN<units::length::meter_t,SIZE> v;
    v(0) = 1.0_m;
    v(1) = 2.0_m;
    v(2) = 3.0_m;

    mc::VectorN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::length::meter
            >
        >,
        SIZE
    > vr;

    vr = m * v;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0)(), 14.0);
    EXPECT_DOUBLE_EQ(vr(1)(), 32.0);
    EXPECT_DOUBLE_EQ(vr(2)(), 50.0);
}

template <typename T>
void CanMultiplyMatrixByVectorAngularVel()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixNxN<T,SIZE> m;
    m.setFromStdVector(x);

    mc::VectorN<units::angular_velocity::radians_per_second_t,SIZE> v;
    v(0) = 1.0_rad_per_s;
    v(1) = 2.0_rad_per_s;
    v(2) = 3.0_rad_per_s;

    mc::VectorN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_t>::unit_type
            >
        >,
        SIZE
    > vr;

    vr = m * v;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0)(), 14.0);
    EXPECT_DOUBLE_EQ(vr(1)(), 32.0);
    EXPECT_DOUBLE_EQ(vr(2)(), 50.0);
}

template <typename T>
void CanMultiplyMatrixByVectorAngularAcc()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixNxN<T,SIZE> m;
    m.setFromStdVector(x);

    mc::VectorN<units::angular_acceleration::radians_per_second_squared_t,SIZE> v;
    v(0) = 1.0_rad_per_s_sq;
    v(1) = 2.0_rad_per_s_sq;
    v(2) = 3.0_rad_per_s_sq;

    mc::VectorN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_squared_t>::unit_type
            >
        >,
        SIZE
    > vr;

    vr = m * v;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0)(), 14.0);
    EXPECT_DOUBLE_EQ(vr(1)(), 32.0);
    EXPECT_DOUBLE_EQ(vr(2)(), 50.0);
}

template <typename T>
void CanMultiplyMatrixByVectorDimensionless()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixNxN<T,SIZE> m;
    m.setFromStdVector(x);

    mc::VectorN<double,SIZE> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<T,SIZE> vr;

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

    mc::MatrixNxN<units::length::meter_t,SIZE> m1;
    mc::MatrixNxN<T,SIZE> m2;

    m1.setFromStdVector(x1);
    m2.setFromStdVector(x2);

    mc::MatrixNxN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::length::meter_t>::unit_type
            >
        >,
        SIZE
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
void CanMultiplyMatrixByMatrixDimensionless()
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

    mc::MatrixNxN<double,SIZE> m1;
    mc::MatrixNxN<T,SIZE> m2;

    m1.setFromStdVector(x1);
    m2.setFromStdVector(x2);

    mc::MatrixNxN<T,SIZE> mr12 = m1 * m2;
    mc::MatrixNxN<T,SIZE> mr21 = m2 * m1;

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

    mc::MatrixNxN<T,SIZE> m1;
    m1.setFromStdVector(x);

    mc::MatrixNxN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::inverse<units::length::meter>
            >
        >,
        SIZE
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
void CanDivideByScalarDimensionless()
{
    constexpr double val = 2.0;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixNxN<T,SIZE> m1;
    m1.setFromStdVector(x);

    mc::MatrixNxN<T,SIZE> mr = m1 / val;

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

    mc::MatrixNxN<T,SIZE> m1;
    mc::MatrixNxN<T,SIZE> mr;
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

    mc::MatrixNxN<T,SIZE> m1;
    mc::MatrixNxN<T,SIZE> mr;
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

template <typename T>
void CanUnaryMultiplyByScalarDimensionless()
{
    constexpr double val = 2.0;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixNxN<T,SIZE> m1;
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
void CanUnaryDivideByScalarDimensionless()
{
    constexpr double val = 2.0;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixNxN<T,SIZE> m1;
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

    mc::MatrixNxN<T,SIZE> m1;
    mc::MatrixNxN<T,SIZE> m2;
    mc::MatrixNxN<T,SIZE> m3;

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

    mc::MatrixNxN<T,SIZE> m1;
    mc::MatrixNxN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::length::meter
            >
        >,
        SIZE
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

    mc::MatrixNxN<T,SIZE> m1;
    mc::MatrixNxN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_t>::unit_type
            >
        >,
        SIZE
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

    mc::MatrixNxN<T,SIZE> m1;
    mc::MatrixNxN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::inverted::per_second_squared_t>::unit_type
            >
        >,
        SIZE
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

    mc::MatrixNxN<T,SIZE> m1;
    mc::MatrixNxN<T,SIZE> mr;
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

} // namespace MatrixNxN
} // namespace test

TEST_F(TestMatrixNxNWithUnits, CanGetIdentityMatrix)
{
    test::MatrixNxN::CanGetIdentityMatrix<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanInstantiate)
{
    test::MatrixNxN::CanInstantiate<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanGetTransposed)
{
    test::MatrixNxN::CanGetTransposed<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanTranspose)
{
    test::MatrixNxN::CanTranspose<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanCastToOtherMatrixType)
{
    test::MatrixNxN::CanCastToOtherMatrixType<
        units::moment_of_inertia::kilogram_meter_squared_t,
        units::moment_of_inertia::slug_foot_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanAdd)
{
    test::MatrixNxN::CanAdd<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanNegate)
{
    test::MatrixNxN::CanNegate<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanSubtract)
{
    test::MatrixNxN::CanSubtract<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyByScalar)
{
    test::MatrixNxN::CanMultiplyByScalar<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyByScalarAngularVel)
{
    test::MatrixNxN::CanMultiplyByScalarAngularVel<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyByScalarAngularAcc)
{
    test::MatrixNxN::CanMultiplyByScalarAngularAcc<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyByScalarDimensionless)
{
    test::MatrixNxN::CanMultiplyByScalarDimensionless<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyByScalarDimensionlessMatrix)
{
    constexpr units::length::meter_t val = 2.0_m;

    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<double,SIZE> m1;
    mc::MatrixNxN<units::length::meter_t,SIZE> mr;
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

TEST_F(TestMatrixNxNWithUnits, CanMultiplyMatrixByVector)
{
    test::MatrixNxN::CanMultiplyMatrixByVector<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyMatrixByVectorAngularVel)
{
    test::MatrixNxN::CanMultiplyMatrixByVectorAngularVel<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyMatrixByVectorAngularAcc)
{
    test::MatrixNxN::CanMultiplyMatrixByVectorAngularAcc<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyMatrixByVectorDimensionless)
{
    test::MatrixNxN::CanMultiplyMatrixByVectorDimensionless<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyMatrixByVectorDimensionlessMatrix)
{
    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };
    mc::MatrixNxN<double,SIZE> m;
    m.setFromStdVector(x);

    mc::VectorN<units::length::meter_t,SIZE> v;
    v(0) = 1.0_m;
    v(1) = 2.0_m;
    v(2) = 3.0_m;

    mc::VectorN<units::length::meter_t,SIZE> vr = m * v;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0)(), 14.0);
    EXPECT_DOUBLE_EQ(vr(1)(), 32.0);
    EXPECT_DOUBLE_EQ(vr(2)(), 50.0);
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyMatrixByMatrix)
{
    test::MatrixNxN::CanMultiplyMatrixByMatrix<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyMatrixByMatrixDimensionless)
{
    test::MatrixNxN::CanMultiplyMatrixByMatrixDimensionless<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanDivideByScalar)
{
    test::MatrixNxN::CanDivideByScalar<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanDivideByScalarDimensionless)
{
    test::MatrixNxN::CanDivideByScalarDimensionless<units::moment_of_inertia::kilogram_meter_squared_t>();
}


TEST_F(TestMatrixNxNWithUnits, CanDivideByScalarDimensionlessMatrix)
{
    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<double,SIZE> m1;
    mc::MatrixNxN<units::frequency::hertz_t,SIZE> mr;
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

TEST_F(TestMatrixNxNWithUnits, CanUnaryAdd)
{
    test::MatrixNxN::CanUnaryAdd<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanUnarySubtract)
{
    test::MatrixNxN::CanUnarySubtract<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanUnaryMultiplyByScalarDimensionless)
{
    test::MatrixNxN::CanUnaryMultiplyByScalarDimensionless<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanUnaryDivideByScalarDimensionless)
{
    test::MatrixNxN::CanUnaryDivideByScalarDimensionless<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanCompare)
{
    test::MatrixNxN::CanCompare<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyScalarByMatrix)
{
    test::MatrixNxN::CanMultiplyScalarByMatrix<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyScalarByMatrixAngularVel)
{
    test::MatrixNxN::CanMultiplyScalarByMatrixAngularVel<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyScalarByMatrixAngularAcc)
{
    test::MatrixNxN::CanMultiplyScalarByMatrixAngularAcc<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyScalarByMatrixDimensionless)
{
    test::MatrixNxN::CanMultiplyScalarByMatrixDimensionless<units::moment_of_inertia::kilogram_meter_squared_t>();
}

TEST_F(TestMatrixNxNWithUnits, CanMultiplyScalarByMatrixDimensionlessMatrix)
{
    constexpr units::length::meter_t val = 2.0_m;

    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<double,SIZE> m1;
    mc::MatrixNxN<units::length::meter_t,SIZE> mr;
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
