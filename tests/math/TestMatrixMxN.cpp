#include <gtest/gtest.h>

#include <mcutils/math/Matrix.h>

#define TYPE double
#define ROWS 3
#define COLS 3

class TestMatrixMxN : public ::testing::Test
{
protected:
    TestMatrixMxN() {}
    virtual ~TestMatrixMxN() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMatrixMxN, CanInstantiate)
{
    mc::MatrixMxN<double,ROWS,COLS> m;
    for ( int r = 0; r < ROWS; ++r )
    {
        for ( int c = 0; c < COLS; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), 0.0) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanFill)
{
    constexpr double val = 666.0;

    mc::MatrixMxN<TYPE,ROWS,COLS> mat;
    mat.fill(val);

    for ( int r = 0; r < ROWS; ++r )
    {
        for ( int c = 0; c < COLS; ++c )
        {
            EXPECT_DOUBLE_EQ(mat(r,c), val) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanValidate)
{
    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<TYPE,ROWS,COLS> m1;
    EXPECT_TRUE(m1.isValid());

    mc::MatrixMxN<TYPE,ROWS,COLS> m2;
    m2.setFromStdVector(x);
    EXPECT_TRUE(m2.isValid());

    mc::MatrixMxN<TYPE,ROWS,COLS> m3;
    m3.setFromStdVector(x);
    m3(0,0) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(m3.isValid());

    mc::MatrixMxN<TYPE,ROWS,COLS> m4;
    m4.setFromStdVector(x);
    m4(1,1) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(m4.isValid());

    mc::MatrixMxN<TYPE,ROWS,COLS> m5;
    m5.fill(std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(m5.isValid());
}

TEST_F(TestMatrixMxN, CanGetTransposed)
{
    std::vector<TYPE> x
    {
        1.0, 2.0,
        3.0, 4.0,
        5.0, 6.0
    };
    mc::MatrixMxN<TYPE,3,2> m;
    m.setFromStdVector(x);

    mc::MatrixMxN<TYPE,2,3> mt = m.getTransposed();

    EXPECT_DOUBLE_EQ(mt(0,0), 1.0);
    EXPECT_DOUBLE_EQ(mt(0,1), 3.0);
    EXPECT_DOUBLE_EQ(mt(0,2), 5.0);

    EXPECT_DOUBLE_EQ(mt(1,0), 2.0);
    EXPECT_DOUBLE_EQ(mt(1,1), 4.0);
    EXPECT_DOUBLE_EQ(mt(1,2), 6.0);
}

TEST_F(TestMatrixMxN, CanGetStdArray)
{
    std::array<TYPE, ROWS * COLS> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };
    std::array<TYPE, ROWS * COLS> xx;

    mc::MatrixMxN<TYPE,ROWS,COLS> m;
    m.setFromStdArray(x);
    xx = m.getStdArray();

    for ( int i = 0; i < ROWS * COLS; ++i )
    {
        EXPECT_DOUBLE_EQ(xx[i], x[i]) << "Error at index " << i;
    }
}

TEST_F(TestMatrixMxN, CanGetStdVector)
{
    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };
    std::vector<TYPE> xx;

    mc::MatrixMxN<TYPE,ROWS,COLS> m;
    m.setFromStdVector(x);
    xx = m.getStdVector();

    for ( int i = 0; i < ROWS * COLS; ++i )
    {
        EXPECT_DOUBLE_EQ(xx[i], x[i]) << "Error at index " << i;
    }
}

TEST_F(TestMatrixMxN, CanSetFromStdArray)
{
    std::array<TYPE, ROWS * COLS> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };
    std::array<TYPE, ROWS * COLS> xx;

    mc::MatrixMxN<TYPE,ROWS,COLS> m;
    m.setFromStdArray(x);
    xx = m.getStdArray();

    for ( int i = 0; i < ROWS * COLS; ++i )
    {
        EXPECT_DOUBLE_EQ(xx[i], x[i]) << "Error at index " << i;
    }
}

TEST_F(TestMatrixMxN, CanSetFromStdVector)
{
    mc::MatrixMxN<TYPE,ROWS,COLS> m;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    m.setFromStdVector(x);

    for ( int r = 0; r < ROWS; ++r )
    {
        for ( int c = 0; c < COLS; ++c )
        {
            int index = r * COLS + c;
            EXPECT_DOUBLE_EQ(m(r,c), x[index]) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanSetFromString)
{
    char str[] =
    { R"##(
        1.0 2.0 3.0
        4.0 5.0 6.0
        7.0 8.0 9.0
    )##" };

    mc::MatrixMxN<TYPE,ROWS,COLS> m;
    m.setFromString(str);

    EXPECT_DOUBLE_EQ(m(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m(0,1), 2.0);
    EXPECT_DOUBLE_EQ(m(0,2), 3.0);

    EXPECT_DOUBLE_EQ(m(1,0), 4.0);
    EXPECT_DOUBLE_EQ(m(1,1), 5.0);
    EXPECT_DOUBLE_EQ(m(1,2), 6.0);

    EXPECT_DOUBLE_EQ(m(2,0), 7.0);
    EXPECT_DOUBLE_EQ(m(2,1), 8.0);
    EXPECT_DOUBLE_EQ(m(2,2), 9.0);
}

TEST_F(TestMatrixMxN, CanSetFromInvalidString)
{
    char str[] = { "lorem ipsum" };
    mc::MatrixMxN<TYPE,ROWS,COLS> m;
    m.setFromString(str);
    EXPECT_FALSE(m.isValid());
}

TEST_F(TestMatrixMxN, CanSwapRows)
{
    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<TYPE,ROWS,COLS> m;
    m.setFromStdVector(x);
    m.swapRows(0, 1);

    EXPECT_DOUBLE_EQ(m(1,0), 1.0);
    EXPECT_DOUBLE_EQ(m(1,1), 2.0);
    EXPECT_DOUBLE_EQ(m(1,2), 3.0);

    EXPECT_DOUBLE_EQ(m(0,0), 4.0);
    EXPECT_DOUBLE_EQ(m(0,1), 5.0);
    EXPECT_DOUBLE_EQ(m(0,2), 6.0);

    EXPECT_DOUBLE_EQ(m(2,0), 7.0);
    EXPECT_DOUBLE_EQ(m(2,1), 8.0);
    EXPECT_DOUBLE_EQ(m(2,2), 9.0);
}

TEST_F(TestMatrixMxN, CanConvertToString)
{
    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<double,3,3> m;
    m.setFromStdVector(x);

    std::stringstream ss;
    ss << 1.0 << "\t" << 2.0 << "\t" << 3.0 << "\n";
    ss << 4.0 << "\t" << 5.0 << "\t" << 6.0 << "\n";
    ss << 7.0 << "\t" << 8.0 << "\t" << 9.0;
    std::string ref = ss.str();

    EXPECT_STREQ(m.toString().c_str(), ss.str().c_str());
}

TEST_F(TestMatrixMxN, CanZeroize)
{
    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<TYPE,ROWS,COLS> m;
    m.setFromStdVector(x);
    m.zeroize();

    EXPECT_DOUBLE_EQ(m(1,0), 0.0);
    EXPECT_DOUBLE_EQ(m(1,1), 0.0);
    EXPECT_DOUBLE_EQ(m(1,2), 0.0);

    EXPECT_DOUBLE_EQ(m(0,0), 0.0);
    EXPECT_DOUBLE_EQ(m(0,1), 0.0);
    EXPECT_DOUBLE_EQ(m(0,2), 0.0);

    EXPECT_DOUBLE_EQ(m(2,0), 0.0);
    EXPECT_DOUBLE_EQ(m(2,1), 0.0);
    EXPECT_DOUBLE_EQ(m(2,2), 0.0);
}

TEST_F(TestMatrixMxN, CanAccessItem)
{
    mc::MatrixMxN<TYPE,ROWS,COLS> m;
    m(0,0) = 1.0;
    m(1,1) = 2.0;
    m(2,2) = 3.0;
    m(0,2) = 9.0;

    mc::MatrixMxN<TYPE,ROWS,COLS> mr(m);
    EXPECT_DOUBLE_EQ(mr(0,0), 1.0);
    EXPECT_DOUBLE_EQ(mr(1,1), 2.0);
    EXPECT_DOUBLE_EQ(mr(2,2), 3.0);
    EXPECT_DOUBLE_EQ(mr(0,2), 9.0);
}

TEST_F(TestMatrixMxN, CanAdd)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<TYPE,ROWS,COLS> m1;
    mc::MatrixMxN<TYPE,ROWS,COLS> m2;
    mc::MatrixMxN<TYPE,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    m2.fill(val);
    mr = m1 + m2;

    for ( int r = 0; r < ROWS; ++r )
    {
        for ( int c = 0; c < COLS; ++c )
        {
            double ref_value = x[r*COLS + c] + val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanAddDifferentType)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<TYPE,ROWS,COLS> m1;
    mc::MatrixMxN<float,ROWS,COLS> m2;
    mc::MatrixMxN<TYPE,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    m2.fill(val);
    mr = m1 + m2;

    for ( int r = 0; r < ROWS; ++r )
    {
        for ( int c = 0; c < COLS; ++c )
        {
            double ref_value = x[r*COLS + c] + val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanNegate)
{
    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<TYPE,ROWS,COLS> m1;
    mc::MatrixMxN<TYPE,ROWS,COLS> m2;
    mc::MatrixMxN<TYPE,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    m2.setFromStdVector(x);
    mr = -m1;

        for ( int r = 0; r < ROWS; ++r )
    {
        for ( int c = 0; c < COLS; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), -m2(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanSubtract)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<TYPE,ROWS,COLS> m1;
    mc::MatrixMxN<TYPE,ROWS,COLS> m2;
    mc::MatrixMxN<TYPE,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    m2.fill(val);
    mr = m1 - m2;

    for ( int r = 0; r < ROWS; ++r )
    {
        for ( int c = 0; c < COLS; ++c )
        {
            double ref_value = x[r*COLS + c] - val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanSubtractDifferentType)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<TYPE,ROWS,COLS> m1;
    mc::MatrixMxN<float,ROWS,COLS> m2;
    mc::MatrixMxN<TYPE,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    m2.fill(val);
    mr = m1 - m2;

    for ( int r = 0; r < ROWS; ++r )
    {
        for ( int c = 0; c < COLS; ++c )
        {
            double ref_value = x[r*COLS + c] - val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanMultiplyByNumber)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<TYPE,ROWS,COLS> m1;
    mc::MatrixMxN<TYPE,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    mr = m1 * val;

    for ( int r = 0; r < ROWS; ++r )
    {
        for ( int c = 0; c < COLS; ++c )
        {
            double ref_value = x[r*COLS + c] * val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanMultiplyIdentityMatrixByVector)
{
    mc::MatrixMxN<TYPE,ROWS,COLS> m;

    m(0,0) =  1.0;
    m(0,1) =  0.0;
    m(0,2) =  0.0;

    m(1,0) =  0.0;
    m(1,1) =  1.0;
    m(1,2) =  0.0;

    m(2,0) =  0.0;
    m(2,1) =  0.0;
    m(2,2) =  1.0;

    mc::VectorN<TYPE,ROWS> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<TYPE,ROWS> vr = m * v;
    EXPECT_DOUBLE_EQ(vr(0),  1.0);
    EXPECT_DOUBLE_EQ(vr(1),  2.0);
    EXPECT_DOUBLE_EQ(vr(2),  3.0);
}

TEST_F(TestMatrixMxN, CanMultiplyNegativeIdentityMatrixByVector)
{
    mc::MatrixMxN<TYPE,ROWS,COLS> m;

    m(0,0) = -1.0;
    m(0,1) =  0.0;
    m(0,2) =  0.0;

    m(1,0) =  0.0;
    m(1,1) = -1.0;
    m(1,2) =  0.0;

    m(2,0) =  0.0;
    m(2,1) =  0.0;
    m(2,2) = -1.0;

    mc::VectorN<TYPE,ROWS> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<TYPE,ROWS> vr = m * v;
    EXPECT_DOUBLE_EQ(vr(0), -1.0);
    EXPECT_DOUBLE_EQ(vr(1), -2.0);
    EXPECT_DOUBLE_EQ(vr(2), -3.0);
}

TEST_F(TestMatrixMxN, CanMultiplySkewXYMatrixByVector)
{
    mc::MatrixMxN<TYPE,ROWS,COLS> m;

    m(0,0) =  0.0;
    m(0,1) =  1.0;
    m(0,2) =  0.0;

    m(1,0) =  1.0;
    m(1,1) =  0.0;
    m(1,2) =  0.0;

    m(2,0) =  0.0;
    m(2,1) =  0.0;
    m(2,2) =  1.0;

    mc::VectorN<TYPE,ROWS> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<TYPE,ROWS> vr = m * v;
    EXPECT_DOUBLE_EQ(vr(0),  2.0);
    EXPECT_DOUBLE_EQ(vr(1),  1.0);
    EXPECT_DOUBLE_EQ(vr(2),  3.0);
}

TEST_F(TestMatrixMxN, CanMultiplyRandomMatrixByVector)
{
    mc::MatrixMxN<TYPE,ROWS,COLS> m3;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };
    mc::MatrixMxN<TYPE,ROWS,COLS> m;
    m.setFromStdVector(x);

    mc::VectorN<TYPE,ROWS> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<TYPE,ROWS> vr = m * v;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(vr(0), 14.0);
    EXPECT_DOUBLE_EQ(vr(1), 32.0);
    EXPECT_DOUBLE_EQ(vr(2), 50.0);
}

TEST_F(TestMatrixMxN, CanMultiplyIdentityMatrixByMatrixMNP)
{
    std::vector<TYPE> x01
    {
        1.0, 2.0,
        2.0, 4.0,
        5.0, 6.0
    };

    std::vector<TYPE> x02
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0
    };

    mc::MatrixMxN<TYPE,3,2> m01;
    mc::MatrixMxN<TYPE,2,3> m02;

    m01.setFromStdVector(x01);
    m02.setFromStdVector(x02);

    mc::MatrixMxN<TYPE,3,3> m0r = m01 * m02;

    // Following tests uses expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_matrix.m
    EXPECT_DOUBLE_EQ(m0r(0,0),  9.0);
    EXPECT_DOUBLE_EQ(m0r(0,1), 12.0);
    EXPECT_DOUBLE_EQ(m0r(0,2), 15.0);
    EXPECT_DOUBLE_EQ(m0r(1,0), 18.0);
    EXPECT_DOUBLE_EQ(m0r(1,1), 24.0);
    EXPECT_DOUBLE_EQ(m0r(1,2), 30.0);
    EXPECT_DOUBLE_EQ(m0r(2,0), 29.0);
    EXPECT_DOUBLE_EQ(m0r(2,1), 40.0);
    EXPECT_DOUBLE_EQ(m0r(2,2), 51.0);
}

// TEST_F(TestMatrixMxN, CanMultiplyIdentityMatrixByMatrix3x3)
// {
//     std::vector<TYPE> x
//     {
//         1.0, 2.0, 3.0,
//         4.0, 5.0, 6.0,
//         7.0, 8.0, 9.0
//     };

//     mc::MatrixMxN<TYPE,ROWS,COLS> m;
//     m.setFromStdVector(x);

//     mc::MatrixMxN<TYPE,ROWS,COLS> mr = m * m;

//     // Following tests uses expected values calculated with GNU Octave
//     // tests/mcsim/utils/math/octave/test_matrix.m
//     EXPECT_DOUBLE_EQ(mr(0,0),  30.0);
//     EXPECT_DOUBLE_EQ(mr(0,1),  36.0);
//     EXPECT_DOUBLE_EQ(mr(0,2),  42.0);

//     EXPECT_DOUBLE_EQ(mr(1,0),  66.0);
//     EXPECT_DOUBLE_EQ(mr(1,1),  81.0);
//     EXPECT_DOUBLE_EQ(mr(1,2),  96.0);

//     EXPECT_DOUBLE_EQ(mr(2,0), 102.0);
//     EXPECT_DOUBLE_EQ(mr(2,1), 126.0);
//     EXPECT_DOUBLE_EQ(mr(2,2), 150.0);
// }

// TEST_F(TestMatrixMxN, CanDivideByNumber)
// {
//     constexpr double val = 2.0;

//     std::vector<TYPE> x
//     {
//         1.0, 2.0, 3.0,
//         4.0, 5.0, 6.0,
//         7.0, 8.0, 9.0
//     };

//     mc::MatrixMxN<TYPE,ROWS,COLS> m1;
//     mc::MatrixMxN<TYPE,ROWS,COLS> mr;
//     m1.setFromStdVector(x);
//     mr = m1 / val;

//     for ( int r = 0; r < ROWS; ++r )
//     {
//         for ( int c = 0; c < COLS; ++c )
//         {
//             double ref_value = x[r*COLS + c] / val;
//             EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
//         }
//     }
// }

TEST_F(TestMatrixMxN, CanUnaryAdd)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<TYPE,ROWS,COLS> m1;
    mc::MatrixMxN<TYPE,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    mr.fill(val);
    mr += m1;

    for ( int r = 0; r < ROWS; ++r )
    {
        for ( int c = 0; c < COLS; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val + m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixMxN, CanUnarySubtract)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<TYPE,ROWS,COLS> m1;
    mc::MatrixMxN<TYPE,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    mr.fill(val);
    mr -= m1;

    for ( int r = 0; r < ROWS; ++r )
    {
        for ( int c = 0; c < COLS; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val - m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

// TEST_F(TestMatrixMxN, CanUnaryMultiplyByNumber)
// {
//     constexpr double val = 2.0;

//     std::vector<TYPE> x
//     {
//         1.0, 2.0, 3.0,
//         4.0, 5.0, 6.0,
//         7.0, 8.0, 9.0
//     };

//     mc::MatrixMxN<TYPE,ROWS,COLS> m;
//     m.setFromStdVector(x);
//     m *= val;

//     for ( int r = 0; r < ROWS; ++r )
//     {
//         for ( int c = 0; c < COLS; ++c )
//         {
//             double ref_value = x[r*COLS + c] * val;
//             EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
//         }
//     }
// }

// TEST_F(TestMatrixMxN, CanUnaryDivideByNumber)
// {
//     constexpr double val = 2.0;

//     std::vector<TYPE> x
//     {
//         1.0, 2.0, 3.0,
//         4.0, 5.0, 6.0,
//         7.0, 8.0, 9.0
//     };

//     mc::MatrixMxN<TYPE,ROWS,COLS> m;
//     m.setFromStdVector(x);
//     m /= val;

//     for ( int r = 0; r < ROWS; ++r )
//     {
//         for ( int c = 0; c < COLS; ++c )
//         {
//             double ref_value = x[r*COLS + c] / val;
//             EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
//         }
//     }
// }

TEST_F(TestMatrixMxN, CanCompare)
{
    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<TYPE,ROWS,COLS> m0;
    mc::MatrixMxN<TYPE,ROWS,COLS> m1;
    mc::MatrixMxN<TYPE,ROWS,COLS> m2;

    m1.setFromStdVector(x);
    m2.setFromStdVector(x);

    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m1 != m0);

    EXPECT_FALSE(m1 != m2);
    EXPECT_FALSE(m1 == m0);
}

TEST_F(TestMatrixMxN, CanMultiplyNumberByMatrix)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixMxN<TYPE,ROWS,COLS> m1;
    mc::MatrixMxN<TYPE,ROWS,COLS> mr;
    m1.setFromStdVector(x);
    mr = val * m1;

    for ( int r = 0; r < ROWS; ++r )
    {
        for ( int c = 0; c < COLS; ++c )
        {
            double ref_value = x[r*COLS + c] * val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}
