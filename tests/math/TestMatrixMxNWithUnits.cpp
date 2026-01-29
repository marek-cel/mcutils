#include <gtest/gtest.h>

#include <mcutils/math/Matrix.h>

#define ROWS 3
#define COLS 3
#define TOLERANCE 1.0e-12

using namespace units::literals;

class TestMatrixMxNWithUnits : public ::testing::Test
{
protected:
    TestMatrixMxNWithUnits() {}
    virtual ~TestMatrixMxNWithUnits() {}
    void SetUp() override {}
    void TearDown() override {}
};

template <typename T>
void MatrixMxN_CanInstantiate()
{
    mc::MatrixMxN<T,ROWS,COLS> m;
    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c)(), 0.0) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanInstantiate)
{
    MatrixMxN_CanInstantiate<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanFill()
{
    constexpr T val = T{123};

    mc::MatrixMxN<T,ROWS,COLS> mat;
    mat.fill(val);

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            EXPECT_DOUBLE_EQ(mat(r,c)(), val()) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanFill)
{
    MatrixMxN_CanFill<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanValidate()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    EXPECT_TRUE(m1.isValid());

    mc::MatrixMxN<T,ROWS,COLS> m2;
    m2.setFromStdVector(x);
    EXPECT_TRUE(m2.isValid());

    mc::MatrixMxN<T,ROWS,COLS> m3;
    m3.setFromStdVector(x);
    m3(0,0) = T{ std::numeric_limits<double>::quiet_NaN() };
    EXPECT_FALSE(m3.isValid());

    mc::MatrixMxN<T,ROWS,COLS> m4;
    m4.setFromStdVector(x);
    m4(1,1) = T{ std::numeric_limits<double>::quiet_NaN() };
    EXPECT_FALSE(m4.isValid());

    mc::MatrixMxN<T,ROWS,COLS> m5;
    m5.fill(T{ std::numeric_limits<double>::quiet_NaN() });
    EXPECT_FALSE(m5.isValid());
}

TEST_F(TestMatrixMxNWithUnits, CanValidate)
{
    MatrixMxN_CanValidate<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanGetTransposed()
{
    std::vector<T> x
    {
        T{1}, T{2},
        T{3}, T{4},
        T{5}, T{6}
    };
    mc::MatrixMxN<T,3,2> m;
    m.setFromStdVector(x);

    mc::MatrixMxN<T,2,3> mt = m.getTransposed();

    EXPECT_DOUBLE_EQ(mt(0,0)(), 1.0);
    EXPECT_DOUBLE_EQ(mt(0,1)(), 3.0);
    EXPECT_DOUBLE_EQ(mt(0,2)(), 5.0);

    EXPECT_DOUBLE_EQ(mt(1,0)(), 2.0);
    EXPECT_DOUBLE_EQ(mt(1,1)(), 4.0);
    EXPECT_DOUBLE_EQ(mt(1,2)(), 6.0);
}

TEST_F(TestMatrixMxNWithUnits, CanGetTransposed)
{
    MatrixMxN_CanGetTransposed<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanGetStdVector()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };
    std::vector<T> xx;

    mc::MatrixMxN<T,ROWS,COLS> m;
    m.setFromStdVector(x);
    xx = m.getStdVector();

    for ( unsigned int i = 0; i < ROWS * COLS; ++i )
    {
        EXPECT_DOUBLE_EQ(xx[i](), x[i]()) << "Error at index " << i;
    }
}

TEST_F(TestMatrixMxNWithUnits, CanGetStdVector)
{
    MatrixMxN_CanGetStdVector<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanSetFromStdVector()
{
    mc::MatrixMxN<T,ROWS,COLS> m;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    m.setFromStdVector(x);

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            int index = r * COLS + c;
            EXPECT_DOUBLE_EQ(m(r,c)(), x[index]()) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanSetFromStdVector)
{
    MatrixMxN_CanSetFromStdVector<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanSetFromString()
{
    char str[] =
    { R"##(
        1.0 2.0 3.0
        4.0 5.0 6.0
        7.0 8.0 9.0
    )##" };

    mc::MatrixMxN<T,ROWS,COLS> m;
    m.setFromString(str);

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

TEST_F(TestMatrixMxNWithUnits, CanSetFromString)
{
    MatrixMxN_CanSetFromString<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanSetFromInvalidString()
{
    char str[] = { "lorem ipsum" };
    mc::MatrixMxN<T,ROWS,COLS> m;
    m.setFromString(str);
    EXPECT_FALSE(m.isValid());
}

TEST_F(TestMatrixMxNWithUnits, CanSetFromInvalidString)
{
    MatrixMxN_CanSetFromInvalidString<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanSwapRows()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m;
    m.setFromStdVector(x);
    m.swapRows(0, 1);

    EXPECT_DOUBLE_EQ(m(1,0)(), 1.0);
    EXPECT_DOUBLE_EQ(m(1,1)(), 2.0);
    EXPECT_DOUBLE_EQ(m(1,2)(), 3.0);

    EXPECT_DOUBLE_EQ(m(0,0)(), 4.0);
    EXPECT_DOUBLE_EQ(m(0,1)(), 5.0);
    EXPECT_DOUBLE_EQ(m(0,2)(), 6.0);

    EXPECT_DOUBLE_EQ(m(2,0)(), 7.0);
    EXPECT_DOUBLE_EQ(m(2,1)(), 8.0);
    EXPECT_DOUBLE_EQ(m(2,2)(), 9.0);
}

TEST_F(TestMatrixMxNWithUnits, CanSwapRows)
{
    MatrixMxN_CanSwapRows<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanConvertToString()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,3,3> m;
    m.setFromStdVector(x);

    std::stringstream ss;
    ss << T{1} << "\t" << T{2} << "\t" << T{3} << "\n";
    ss << T{4} << "\t" << T{5} << "\t" << T{6} << "\n";
    ss << T{7} << "\t" << T{8} << "\t" << T{9};
    std::string ref = ss.str();

    EXPECT_STREQ(m.toString().c_str(), ss.str().c_str());
}

TEST_F(TestMatrixMxNWithUnits, CanConvertToString)
{
    MatrixMxN_CanConvertToString<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanZeroize()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m;
    m.setFromStdVector(x);
    m.zeroize();

    EXPECT_DOUBLE_EQ(m(1,0)(), 0.0);
    EXPECT_DOUBLE_EQ(m(1,1)(), 0.0);
    EXPECT_DOUBLE_EQ(m(1,2)(), 0.0);

    EXPECT_DOUBLE_EQ(m(0,0)(), 0.0);
    EXPECT_DOUBLE_EQ(m(0,1)(), 0.0);
    EXPECT_DOUBLE_EQ(m(0,2)(), 0.0);

    EXPECT_DOUBLE_EQ(m(2,0)(), 0.0);
    EXPECT_DOUBLE_EQ(m(2,1)(), 0.0);
    EXPECT_DOUBLE_EQ(m(2,2)(), 0.0);
}

TEST_F(TestMatrixMxNWithUnits, CanZeroize)
{
    MatrixMxN_CanZeroize<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T1, typename T2>
void MatrixMxN_CanCastToOtherMatrixType()
{
    mc::MatrixMxN<T1,ROWS,COLS> m1;

    m1(0,0) = T2{1}; // sic!
    m1(0,1) = T2{2}; // sic!
    m1(0,2) = T2{3}; // sic!

    m1(1,0) = T2{4}; // sic!
    m1(1,1) = T2{5}; // sic!
    m1(1,2) = T2{6}; // sic!

    m1(2,0) = T2{7}; // sic!
    m1(2,1) = T2{8}; // sic!
    m1(2,2) = T2{9}; // sic!

    mc::MatrixMxN<T2,ROWS,COLS> m2;
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

TEST_F(TestMatrixMxNWithUnits, CanCastToOtherMatrixType)
{
    MatrixMxN_CanCastToOtherMatrixType<
        units::moment_of_inertia::kilograms_meters_squared_t,
        units::moment_of_inertia::slugs_feet_squared_t>();
}

template <typename T>
void MatrixMxN_CanAccessItem()
{
    mc::MatrixMxN<T,ROWS,COLS> m;

    m(0,0) = T{1};
    m(0,1) = T{2};
    m(0,2) = T{3};

    m(1,0) = T{4};
    m(1,1) = T{5};
    m(1,2) = T{6};

    m(2,0) = T{7};
    m(2,1) = T{8};
    m(2,2) = T{9};

    const mc::MatrixMxN<T,ROWS,COLS> mm = m;

    EXPECT_DOUBLE_EQ(mm(0,0)(), 1.0);
    EXPECT_DOUBLE_EQ(mm(0,1)(), 2.0);
    EXPECT_DOUBLE_EQ(mm(0,2)(), 3.0);

    EXPECT_DOUBLE_EQ(mm(1,0)(), 4.0);
    EXPECT_DOUBLE_EQ(mm(1,1)(), 5.0);
    EXPECT_DOUBLE_EQ(mm(1,2)(), 6.0);

    EXPECT_DOUBLE_EQ(mm(2,0)(), 7.0);
    EXPECT_DOUBLE_EQ(mm(2,1)(), 8.0);
    EXPECT_DOUBLE_EQ(mm(2,2)(), 9.0);
}

TEST_F(TestMatrixMxNWithUnits, CanAccessItem)
{
    MatrixMxN_CanAccessItem<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanAdd()
{
    constexpr T val = T{2};

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    mc::MatrixMxN<T,ROWS,COLS> m2;
    mc::MatrixMxN<T,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    m2.fill(val);
    mr = m1 + m2;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            double ref = x[r*COLS + c]() + val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanAdd)
{
    MatrixMxN_CanAdd<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanNegate()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    mc::MatrixMxN<T,ROWS,COLS> m2;
    mc::MatrixMxN<T,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    m2.setFromStdVector(x);
    mr = -m1;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c)(), -m2(r,c)()) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanNegate)
{
    MatrixMxN_CanNegate<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanSubtract()
{
    constexpr T val = T{2};

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    mc::MatrixMxN<T,ROWS,COLS> m2;
    mc::MatrixMxN<T,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    m2.fill(val);
    mr = m1 - m2;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            double ref = x[r*COLS + c]() - val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanSubtract)
{
    MatrixMxN_CanSubtract<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanMultiplyByScalar()
{
    constexpr units::length::meter_t val = 2.0_m;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    mc::MatrixMxN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::length::meter
            >
        >,
        ROWS,COLS
    > mr;
    m1.setFromStdVector(x);
    mr = m1 * val;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            double ref = x[r*COLS + c]() * val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanMultiplyByScalar)
{
    MatrixMxN_CanMultiplyByScalar<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanMultiplyByScalarDimensionless()
{
    constexpr double val = 2.0;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    mc::MatrixMxN<T,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    mr = m1 * val;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            double ref = x[r*COLS + c]() * val;
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanMultiplyByScalarDimensionless)
{
    MatrixMxN_CanMultiplyByScalarDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}

TEST_F(TestMatrixMxNWithUnits, CanMultiplyByScalarDimensionlessMatrix)
{
    constexpr units::length::meter_t val = 2.0_m;

    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<double,ROWS,COLS> m1;
    mc::MatrixMxN<units::length::meter_t,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    mr = m1 * val;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            double ref = x[r*COLS + c] * val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

template <typename T>
void MatrixMxN_CanMultiplyMatrixByVector()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m;
    m.setFromStdVector(x);

    mc::VectorN<units::length::meter_t,ROWS> v;
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
        ROWS
    > vr;

    vr = m * v;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0)(), 14.0);
    EXPECT_DOUBLE_EQ(vr(1)(), 32.0);
    EXPECT_DOUBLE_EQ(vr(2)(), 50.0);
}

TEST_F(TestMatrixMxNWithUnits, CanMultiplyMatrixByVector)
{
    MatrixMxN_CanMultiplyMatrixByVector<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanMultiplyMatrixByVectorDimensionless()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m;
    m.setFromStdVector(x);

    mc::VectorN<double,ROWS> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<T,ROWS> vr;

    vr = m * v;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0)(), 14.0);
    EXPECT_DOUBLE_EQ(vr(1)(), 32.0);
    EXPECT_DOUBLE_EQ(vr(2)(), 50.0);
}

TEST_F(TestMatrixMxNWithUnits, CanMultiplyMatrixByVectorDimensionless)
{
    MatrixMxN_CanMultiplyMatrixByVectorDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}

TEST_F(TestMatrixMxNWithUnits, CanMultiplyMatrixByVectorDimensionlessMatrix)
{
    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };
    mc::MatrixMxN<double,ROWS,COLS> m;
    m.setFromStdVector(x);

    mc::VectorN<units::length::meter_t,ROWS> v;
    v(0) = 1.0_m;
    v(1) = 2.0_m;
    v(2) = 3.0_m;

    mc::VectorN<units::length::meter_t,ROWS> vr = m * v;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0)(), 14.0);
    EXPECT_DOUBLE_EQ(vr(1)(), 32.0);
    EXPECT_DOUBLE_EQ(vr(2)(), 50.0);
}

template <typename T>
void MatrixMxN_CanMultiplyMatrixByMatrix()
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

    mc::MatrixMxN<units::length::meter_t,ROWS,COLS> m1;
    mc::MatrixMxN<T,ROWS,COLS> m2;

    m1.setFromStdVector(x1);
    m2.setFromStdVector(x2);

    mc::MatrixMxN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                typename units::traits::unit_t_traits<units::length::meter_t>::unit_type
            >
        >,
        ROWS,COLS
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

TEST_F(TestMatrixMxNWithUnits, CanMultiplyMatrixByMatrix)
{
    MatrixMxN_CanMultiplyMatrixByMatrix<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanMultiplyMatrixByMatrixDimensionless()
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

    mc::MatrixMxN<double,ROWS,COLS> m1;
    mc::MatrixMxN<T,ROWS,COLS> m2;

    m1.setFromStdVector(x1);
    m2.setFromStdVector(x2);

    mc::MatrixMxN<T,ROWS,COLS> mr12 = m1 * m2;
    mc::MatrixMxN<T,ROWS,COLS> mr21 = m2 * m1;

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

TEST_F(TestMatrixMxNWithUnits, CanMultiplyMatrixByMatrixDimensionless)
{
    MatrixMxN_CanMultiplyMatrixByMatrixDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanDivideByScalar()
{
    constexpr units::length::meter_t val = 2.0_m;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    m1.setFromStdVector(x);

    mc::MatrixMxN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::inverse<units::length::meter>
            >
        >,
        ROWS,COLS
    > mr;

    mr = m1 / val;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            double ref = x[r*COLS + c]() / val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanDivideByScalar)
{
    MatrixMxN_CanDivideByScalar<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanDivideByScalarDimensionless()
{
    constexpr double val = 2.0;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    m1.setFromStdVector(x);

    mc::MatrixMxN<T,ROWS,COLS> mr = m1 / val;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            double ref = x[r*COLS + c]() / val;
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanDivideByScalarDimensionless)
{
    MatrixMxN_CanDivideByScalarDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}


TEST_F(TestMatrixMxNWithUnits, CanDivideByScalarDimensionlessMatrix)
{
    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<double,ROWS,COLS> m1;
    mc::MatrixMxN<units::frequency::hertz_t,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    mr = m1 / 1.0_s;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c)(), x[r*COLS + c]) << "Error at row " << r << " and col " << c;
        }
    }
}

template <typename T>
void MatrixMxN_CanUnaryAdd()
{
    constexpr T val = T{2};

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    mc::MatrixMxN<T,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    mr.fill(val);
    mr += m1;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c)(), val() + m1(r,c)()) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanUnaryAdd)
{
    MatrixMxN_CanUnaryAdd<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanUnarySubtract()
{
    constexpr T val = T{2};

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    mc::MatrixMxN<T,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    mr.fill(val);
    mr -= m1;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c)(), val() - m1(r,c)()) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanUnarySubtract)
{
    MatrixMxN_CanUnarySubtract<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanUnaryMultiplyByScalarDimensionless()
{
    constexpr double val = 2.0;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    m1.setFromStdVector(x);

    m1 *= val;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            double ref = x[r*COLS + c]() * val;
            EXPECT_DOUBLE_EQ(m1(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanUnaryMultiplyByScalarDimensionless)
{
    MatrixMxN_CanUnaryMultiplyByScalarDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanUnaryDivideByScalarDimensionless()
{
    constexpr double val = 2.0;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    m1.setFromStdVector(x);

    m1 /= val;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            double ref = x[r*COLS + c]() / val;
            EXPECT_DOUBLE_EQ(m1(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanUnaryDivideByScalarDimensionless)
{
    MatrixMxN_CanUnaryDivideByScalarDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanCompare()
{
    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    mc::MatrixMxN<T,ROWS,COLS> m2;
    mc::MatrixMxN<T,ROWS,COLS> m3;

    m1.setFromStdVector(x);
    m2.setFromStdVector(x);
    m3.fill(T{123});

    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m1 != m3);
    EXPECT_FALSE(m1 != m2);
    EXPECT_FALSE(m1 == m3);
}

TEST_F(TestMatrixMxNWithUnits, CanCompare)
{
    MatrixMxN_CanCompare<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanMultiplyScalarByMatrix()
{
    constexpr units::length::meter_t val = 2.0_m;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    mc::MatrixMxN<
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<T>::unit_type,
                units::length::meter
            >
        >,
        ROWS,COLS
    > mr;
    m1.setFromStdVector(x);
    mr = val * m1;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            double ref = x[r*COLS + c]() * val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanMultiplyScalarByMatrix)
{
    MatrixMxN_CanMultiplyScalarByMatrix<units::moment_of_inertia::kilograms_meters_squared_t>();
}

template <typename T>
void MatrixMxN_CanMultiplyScalarByMatrixDimensionless()
{
    constexpr double val = 2.0;

    std::vector<T> x
    {
        T{1}, T{2}, T{3},
        T{4}, T{5}, T{6},
        T{7}, T{8}, T{9}
    };

    mc::MatrixMxN<T,ROWS,COLS> m1;
    mc::MatrixMxN<T,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    mr = val * m1;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            double ref = x[r*COLS + c]() * val;
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxNWithUnits, CanMultiplyScalarByMatrixDimensionless)
{
    MatrixMxN_CanMultiplyScalarByMatrixDimensionless<units::moment_of_inertia::kilograms_meters_squared_t>();
}

TEST_F(TestMatrixMxNWithUnits, CanMultiplyScalarByMatrixDimensionlessMatrix)
{
    constexpr units::length::meter_t val = 2.0_m;

    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<double,ROWS,COLS> m1;
    mc::MatrixMxN<units::length::meter_t,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    mr = val * m1;

    for ( unsigned int r = 0; r < ROWS; ++r )
    {
        for ( unsigned int c = 0; c < COLS; ++c )
        {
            double ref = x[r*COLS + c] * val();
            EXPECT_DOUBLE_EQ(mr(r,c)(), ref) << "Error at row " << r << " and col " << c;
        }
    }
}
