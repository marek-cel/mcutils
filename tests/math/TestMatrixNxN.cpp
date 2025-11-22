#include <gtest/gtest.h>

#include <mcutils/math/Matrix.h>

#define TYPE double
#define SIZE 3

class TestMatrixNxN : public ::testing::Test
{
protected:
    TestMatrixNxN() {}
    virtual ~TestMatrixNxN() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMatrixNxN, CanGetIdentityMatrix)
{
    mc::MatrixNxN<TYPE,SIZE> m = mc::MatrixNxN<TYPE,SIZE>::getIdentityMatrix();

    EXPECT_DOUBLE_EQ(m(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m(0,1), 0.0);
    EXPECT_DOUBLE_EQ(m(0,2), 0.0);

    EXPECT_DOUBLE_EQ(m(1,0), 0.0);
    EXPECT_DOUBLE_EQ(m(1,1), 1.0);
    EXPECT_DOUBLE_EQ(m(1,2), 0.0);

    EXPECT_DOUBLE_EQ(m(2,0), 0.0);
    EXPECT_DOUBLE_EQ(m(2,1), 0.0);
    EXPECT_DOUBLE_EQ(m(2,2), 1.0);
}

TEST_F(TestMatrixNxN, CanInstantiate)
{
    mc::MatrixNxN<TYPE,SIZE> m;
    for ( int r = 0; r < SIZE; ++r )
    {
        for ( int c = 0; c < SIZE; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), 0.0) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanInstantiateAndCopy)
{
    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<TYPE,SIZE> m0;
    m0.setFromStdVector(x);

    mc::MatrixNxN<TYPE,SIZE> m1(m0);

    for ( int r = 0; r < SIZE; ++r )
    {
        for ( int c = 0; c < SIZE; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanTranspose)
{
    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<TYPE,SIZE> m;
    m.setFromStdVector(x);

    m.transpose();

    for ( int r = 0; r < SIZE; ++r )
    {
        for ( int c = 0; c < SIZE; ++c )
        {
            int index = r * SIZE + c;
            // matrix 'm' transposed (row and col inverted)
            EXPECT_DOUBLE_EQ(m(c,r), x[index]) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, GetDimensionless)
{
    mc::MatrixNxN<TYPE,SIZE> m1;

    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(0,2) = 3.0;

    m1(1,0) = 4.0;
    m1(1,1) = 5.0;
    m1(1,2) = 6.0;

    m1(2,0) = 7.0;
    m1(2,1) = 8.0;
    m1(2,2) = 9.0;

    mc::MatrixNxN<double,SIZE> m2;
    m2 = m1.getDimensionless();

    EXPECT_DOUBLE_EQ(m2(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m2(0,1), 2.0);
    EXPECT_DOUBLE_EQ(m2(0,2), 3.0);

    EXPECT_DOUBLE_EQ(m2(1,0), 4.0);
    EXPECT_DOUBLE_EQ(m2(1,1), 5.0);
    EXPECT_DOUBLE_EQ(m2(1,2), 6.0);

    EXPECT_DOUBLE_EQ(m2(2,0), 7.0);
    EXPECT_DOUBLE_EQ(m2(2,1), 8.0);
    EXPECT_DOUBLE_EQ(m2(2,2), 9.0);
}

TEST_F(TestMatrixNxN, CanAdd)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<TYPE,SIZE> m1;
    mc::MatrixNxN<TYPE,SIZE> m2;
    mc::MatrixNxN<TYPE,SIZE> mr;
    m1.setFromStdVector(x);
    m2.fill(val);
    mr = m1 + m2;

    for ( int r = 0; r < SIZE; ++r )
    {
        for ( int c = 0; c < SIZE; ++c )
        {
            double ref_value = x[r*SIZE + c] + val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanNegate)
{
    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<TYPE,SIZE> m1;
    mc::MatrixNxN<TYPE,SIZE> m2;
    mc::MatrixNxN<TYPE,SIZE> mr;
    m1.setFromStdVector(x);
    m2.setFromStdVector(x);
    mr = -m1;

    for ( int r = 0; r < SIZE; ++r )
    {
        for ( int c = 0; c < SIZE; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), -m2(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanSubstract)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<TYPE,SIZE> m1;
    mc::MatrixNxN<TYPE,SIZE> m2;
    mc::MatrixNxN<TYPE,SIZE> mr;
    m1.setFromStdVector(x);
    m2.fill(val);
    mr = m1 - m2;

    for ( int r = 0; r < SIZE; ++r )
    {
        for ( int c = 0; c < SIZE; ++c )
        {
            double ref_value = x[r*SIZE + c] - val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanMultiplyByNumber)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<TYPE,SIZE> m1;
    mc::MatrixNxN<TYPE,SIZE> mr;
    m1.setFromStdVector(x);
    mr = m1 * val;

    for ( int r = 0; r < SIZE; ++r )
    {
        for ( int c = 0; c < SIZE; ++c )
        {
            double ref_value = x[r*SIZE + c] * val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanMultiplyByMatrix)
{
    std::vector<TYPE> x1 { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    mc::MatrixNxN<TYPE,SIZE> m1;
    m1.setFromStdVector(x1);

    std::vector<TYPE> x2 { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
    mc::MatrixNxN<TYPE,SIZE> m2;
    m2.setFromStdVector(x2);

    mc::MatrixNxN<TYPE,SIZE> mr = m1 * m2;

    EXPECT_NEAR(mr(0,0),  33.0, 1.0e-9);
    EXPECT_NEAR(mr(0,1),  39.6, 1.0e-9);
    EXPECT_NEAR(mr(0,2),  46.2, 1.0e-9);

    EXPECT_NEAR(mr(1,0),  72.6, 1.0e-9);
    EXPECT_NEAR(mr(1,1),  89.1, 1.0e-9);
    EXPECT_NEAR(mr(1,2), 105.6, 1.0e-9);

    EXPECT_NEAR(mr(2,0), 112.2, 1.0e-9);
    EXPECT_NEAR(mr(2,1), 138.6, 1.0e-9);
    EXPECT_NEAR(mr(2,2), 165.0, 1.0e-9);
}

TEST_F(TestMatrixNxN, CanMultiplyIdentityMatrixByVector)
{
    mc::MatrixNxN<TYPE,SIZE> m;

    m(0,0) =  1.0;
    m(0,1) =  0.0;
    m(0,2) =  0.0;

    m(1,0) =  0.0;
    m(1,1) =  1.0;
    m(1,2) =  0.0;

    m(2,0) =  0.0;
    m(2,1) =  0.0;
    m(2,2) =  1.0;

    mc::VectorN<TYPE,SIZE> v;
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<TYPE,SIZE> vr = m * v;
    EXPECT_DOUBLE_EQ(vr(0),  1.0);
    EXPECT_DOUBLE_EQ(vr(1),  2.0);
    EXPECT_DOUBLE_EQ(vr(2),  3.0);
}

TEST_F(TestMatrixNxN, CanDivideByNumber)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<TYPE,SIZE> m1;
    mc::MatrixNxN<TYPE,SIZE> mr;
    m1.setFromStdVector(x);
    mr = m1 / val;

    for ( int r = 0; r < SIZE; ++r )
    {
        for ( int c = 0; c < SIZE; ++c )
        {
            double ref_value = x[r*SIZE + c] / val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanUnaryAdd)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<TYPE,SIZE> m1;
    mc::MatrixNxN<TYPE,SIZE> mr;
    m1.setFromStdVector(x);
    mr.fill(val);
    mr += m1;

    for ( int r = 0; r < SIZE; ++r )
    {
        for ( int c = 0; c < SIZE; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val + m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanUnarySubstract)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<TYPE,SIZE> m1;
    mc::MatrixNxN<TYPE,SIZE> mr;
    m1.setFromStdVector(x);
    mr.fill(val);
    mr -= m1;

    for ( int r = 0; r < SIZE; ++r )
    {
        for ( int c = 0; c < SIZE; ++c )
        {
            EXPECT_DOUBLE_EQ(mr(r,c), val - m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanUnaryMultiplyByNumber)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<TYPE,SIZE> m;
    m.setFromStdVector(x);
    m *= val;

    for ( int r = 0; r < SIZE; ++r )
    {
        for ( int c = 0; c < SIZE; ++c )
        {
            double ref_value = x[r*SIZE + c] * val;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanUnaryDivideByNumber)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<TYPE,SIZE> m;
    m.setFromStdVector(x);
    m /= val;

    for ( int r = 0; r < SIZE; ++r )
    {
        for ( int c = 0; c < SIZE; ++c )
        {
            double ref_value = x[r*SIZE + c] / val;
            EXPECT_DOUBLE_EQ(m(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrixNxN, CanMultiplyNumberByMatrix)
{
    constexpr double val = 2.0;

    std::vector<TYPE> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::MatrixNxN<TYPE,SIZE> m1;
    mc::MatrixNxN<TYPE,SIZE> mr;
    m1.setFromStdVector(x);
    mr = val * m1;

    for ( int r = 0; r < SIZE; ++r )
    {
        for ( int c = 0; c < SIZE; ++c )
        {
            double ref_value = x[r*SIZE + c] * val;
            EXPECT_DOUBLE_EQ(mr(r,c), ref_value) << "Error at row " << r << " and col " << c;
        }
    }
}
