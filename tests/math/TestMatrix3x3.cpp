#include <gtest/gtest.h>

#include <mcutils/math/Matrix.h>

class TestMatrix3x3 : public ::testing::Test
{
protected:
    constexpr static int size = 3;
    TestMatrix3x3() {}
    virtual ~TestMatrix3x3() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMatrix3x3, CanGetIdentityMatrix)
{
    mc::Matrix3x3d m = mc::Matrix3x3d::getIdentityMatrix();

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

TEST_F(TestMatrix3x3, CanConstruct)
{
    mc::Matrix3x3d* m = nullptr;
    EXPECT_NO_THROW(m = new mc::Matrix3x3d());
    delete m;
}

TEST_F(TestMatrix3x3, CanDestruct)
{
    mc::Matrix3x3d* m = new mc::Matrix3x3d();
    EXPECT_NO_THROW(delete m);
}

TEST_F(TestMatrix3x3, CanInstantiate)
{
    mc::Matrix3x3d m;
    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), 0.0) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3, CanInstantiateAndCopy)
{
    constexpr int size = 3;

    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::Matrix3x3d m0;
    m0.setFromStdVector(x);

    mc::Matrix3x3d m1(m0);

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3, CanInstantiateAndSetData)
{
    mc::Matrix3x3d m1(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    EXPECT_DOUBLE_EQ(m1(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m1(0,1), 2.0);
    EXPECT_DOUBLE_EQ(m1(0,2), 3.0);
    EXPECT_DOUBLE_EQ(m1(1,0), 4.0);
    EXPECT_DOUBLE_EQ(m1(1,1), 5.0);
    EXPECT_DOUBLE_EQ(m1(1,2), 6.0);
    EXPECT_DOUBLE_EQ(m1(2,0), 7.0);
    EXPECT_DOUBLE_EQ(m1(2,1), 8.0);
    EXPECT_DOUBLE_EQ(m1(2,2), 9.0);
}

TEST_F(TestMatrix3x3, CanAccessXX)
{
    mc::Matrix3x3d m0;

    m0.xx() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessXY)
{
    mc::Matrix3x3d m0;

    m0.xy() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessXZ)
{
    mc::Matrix3x3d m0;

    m0.xz() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 1.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessYX)
{
    mc::Matrix3x3d m0;

    m0.yx() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 1.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessYY)
{
    mc::Matrix3x3d m0;

    m0.yy() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessYZ)
{
    mc::Matrix3x3d m0;

    m0.yz() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 1.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessZX)
{
    mc::Matrix3x3d m0;

    m0.zx() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 1.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessZY)
{
    mc::Matrix3x3d m0;

    m0.zy() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}

TEST_F(TestMatrix3x3, CanAccessZZ)
{
    mc::Matrix3x3d m0;

    m0.zz() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 1.0);
}

TEST_F(TestMatrix3x3, CanSetData)
{
    mc::Matrix3x3d m0;

    m0.set(11.0, 12.0, 13.0,
           21.0, 22.0, 23.0,
           31.0, 32.0, 33.0);

    EXPECT_DOUBLE_EQ(m0.xx(), 11.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 12.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 13.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 21.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 22.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 23.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 31.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 32.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 33.0);
}

TEST_F(TestMatrix3x3, CanGetTransposed)
{
    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::Matrix3x3d m0;
    m0.setFromStdVector(x);

    mc::Matrix3x3d m1(m0);
    mc::Matrix3x3d mt = m1.getTransposed();

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
            EXPECT_DOUBLE_EQ(mt(r,c), m0(c,r)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestMatrix3x3, CanAdd)
{
    mc::Matrix3x3d m1(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    mc::Matrix3x3d m2(1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0);

    mc::Matrix3x3d m0 = m1 + m2;

    EXPECT_DOUBLE_EQ(m0.xx(),  2.0);
    EXPECT_DOUBLE_EQ(m0.xy(),  3.0);
    EXPECT_DOUBLE_EQ(m0.xz(),  4.0);
    EXPECT_DOUBLE_EQ(m0.yx(),  5.0);
    EXPECT_DOUBLE_EQ(m0.yy(),  6.0);
    EXPECT_DOUBLE_EQ(m0.yz(),  7.0);
    EXPECT_DOUBLE_EQ(m0.zx(),  8.0);
    EXPECT_DOUBLE_EQ(m0.zy(),  9.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 10.0);
}

TEST_F(TestMatrix3x3, CanAddDifferentType)
{
    mc::Matrix3x3<float> m1(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    mc::Matrix3x3d m2(
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0
    );

    mc::Matrix3x3d m0 = m1 + m2;

    EXPECT_DOUBLE_EQ(m0.xx(),  2.0);
    EXPECT_DOUBLE_EQ(m0.xy(),  3.0);
    EXPECT_DOUBLE_EQ(m0.xz(),  4.0);
    EXPECT_DOUBLE_EQ(m0.yx(),  5.0);
    EXPECT_DOUBLE_EQ(m0.yy(),  6.0);
    EXPECT_DOUBLE_EQ(m0.yz(),  7.0);
    EXPECT_DOUBLE_EQ(m0.zx(),  8.0);
    EXPECT_DOUBLE_EQ(m0.zy(),  9.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 10.0);
}


TEST_F(TestMatrix3x3, CanNegate)
{
    mc::Matrix3x3d m1(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    mc::Matrix3x3d m0 = -m1;

    EXPECT_DOUBLE_EQ(m0.xx(), -1.0);
    EXPECT_DOUBLE_EQ(m0.xy(), -2.0);
    EXPECT_DOUBLE_EQ(m0.xz(), -3.0);
    EXPECT_DOUBLE_EQ(m0.yx(), -4.0);
    EXPECT_DOUBLE_EQ(m0.yy(), -5.0);
    EXPECT_DOUBLE_EQ(m0.yz(), -6.0);
    EXPECT_DOUBLE_EQ(m0.zx(), -7.0);
    EXPECT_DOUBLE_EQ(m0.zy(), -8.0);
    EXPECT_DOUBLE_EQ(m0.zz(), -9.0);
}

TEST_F(TestMatrix3x3, CanSubstract)
{
    mc::Matrix3x3d m1(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    mc::Matrix3x3d m2(1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0);

    mc::Matrix3x3d m0 = m1 - m2;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 2.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 3.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 4.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 5.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 6.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 7.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 8.0);
}

TEST_F(TestMatrix3x3, CanSubstractDifferentType)
{
    mc::Matrix3x3<float> m1(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    mc::Matrix3x3d m2(
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0
    );

    mc::Matrix3x3d m0 = m1 - m2;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 2.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 3.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 4.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 5.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 6.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 7.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 8.0);
}

TEST_F(TestMatrix3x3, CanMultiplyByNumber)
{
    mc::Matrix3x3d m1(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    mc::Matrix3x3d m0 = m1 * 0.5;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m0.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m0.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m0.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 4.5);
}

TEST_F(TestMatrix3x3, CanMultiplyByMatrix)
{
    mc::Matrix3x3d m1(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    mc::Matrix3x3d m2(1.1, 2.2, 3.3,
                      4.4, 5.5, 6.6,
                      7.7, 8.8, 9.9);

    mc::Matrix3x3d m0 = m1 * m2;

    EXPECT_NEAR(m0.xx(),  33.0, 1.0e-9);
    EXPECT_NEAR(m0.xy(),  39.6, 1.0e-9);
    EXPECT_NEAR(m0.xz(),  46.2, 1.0e-9);
    EXPECT_NEAR(m0.yx(),  72.6, 1.0e-9);
    EXPECT_NEAR(m0.yy(),  89.1, 1.0e-9);
    EXPECT_NEAR(m0.yz(), 105.6, 1.0e-9);
    EXPECT_NEAR(m0.zx(), 112.2, 1.0e-9);
    EXPECT_NEAR(m0.zy(), 138.6, 1.0e-9);
    EXPECT_NEAR(m0.zz(), 165.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanMultiplyByVector)
{
    mc::Matrix3x3d m1(1.0, 0.0, 0.0,
                      0.0, 1.0, 0.0,
                      0.0, 0.0, 1.0);

    mc::Matrix3x3d m2(-1.0,  0.0,  0.0,
                       0.0, -1.0,  0.0,
                       0.0,  0.0, -1.0);

    mc::Matrix3x3d m3(0.0, 1.0, 0.0,
                      1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0);

    mc::Matrix3x3d m4(1.0,  0.0,  0.0,
                      0.0,  0.0, -1.0,
                      0.0, -1.0,  0.0);

    mc::Vector3d v(1.0, 2.0, 3.0);

    mc::Vector3d v1 = m1 * v;
    EXPECT_NEAR(v1.x(),  1.0, 1.0e-9);
    EXPECT_NEAR(v1.y(),  2.0, 1.0e-9);
    EXPECT_NEAR(v1.z(),  3.0, 1.0e-9);

    mc::Vector3d v2 = m2 * v;
    EXPECT_NEAR(v2.x(), -1.0, 1.0e-9);
    EXPECT_NEAR(v2.y(), -2.0, 1.0e-9);
    EXPECT_NEAR(v2.z(), -3.0, 1.0e-9);

    mc::Vector3d v3 = m3 * v;
    EXPECT_NEAR(v3.x(),  2.0, 1.0e-9);
    EXPECT_NEAR(v3.y(),  1.0, 1.0e-9);
    EXPECT_NEAR(v3.z(),  3.0, 1.0e-9);

    mc::Vector3d v4 = m4 * v;
    EXPECT_NEAR(v4.x(),  1.0, 1.0e-9);
    EXPECT_NEAR(v4.y(), -3.0, 1.0e-9);
    EXPECT_NEAR(v4.z(), -2.0, 1.0e-9);
}

TEST_F(TestMatrix3x3, CanDivideByNumber)
{
    mc::Matrix3x3d m1(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);
    mc::Matrix3x3d m0 = m1 / 2.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m0.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m0.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m0.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 4.5);
}

TEST_F(TestMatrix3x3, CanUnaryAdd)
{
    mc::Matrix3x3d m1(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    mc::Matrix3x3d m2(1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0);

    m1 += m2;

    EXPECT_DOUBLE_EQ(m1.xx(),  2.0);
    EXPECT_DOUBLE_EQ(m1.xy(),  3.0);
    EXPECT_DOUBLE_EQ(m1.xz(),  4.0);
    EXPECT_DOUBLE_EQ(m1.yx(),  5.0);
    EXPECT_DOUBLE_EQ(m1.yy(),  6.0);
    EXPECT_DOUBLE_EQ(m1.yz(),  7.0);
    EXPECT_DOUBLE_EQ(m1.zx(),  8.0);
    EXPECT_DOUBLE_EQ(m1.zy(),  9.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 10.0);
}

TEST_F(TestMatrix3x3, CanUnarySubstract)
{
    mc::Matrix3x3d m1(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    mc::Matrix3x3d m2(1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0);

    m1 -= m2;

    EXPECT_DOUBLE_EQ(m1.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m1.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m1.xz(), 2.0);
    EXPECT_DOUBLE_EQ(m1.yx(), 3.0);
    EXPECT_DOUBLE_EQ(m1.yy(), 4.0);
    EXPECT_DOUBLE_EQ(m1.yz(), 5.0);
    EXPECT_DOUBLE_EQ(m1.zx(), 6.0);
    EXPECT_DOUBLE_EQ(m1.zy(), 7.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 8.0);
}

TEST_F(TestMatrix3x3, CanUnaryMultiplyByNumber)
{
    mc::Matrix3x3d m1(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    m1 *= 0.5;

    EXPECT_DOUBLE_EQ(m1.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m1.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m1.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m1.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m1.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m1.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m1.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m1.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 4.5);
}

TEST_F(TestMatrix3x3, CanUnaryDivideByNumber)
{
    mc::Matrix3x3d m1(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    m1 /= 2.0;

    EXPECT_DOUBLE_EQ(m1.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m1.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m1.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m1.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m1.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m1.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m1.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m1.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 4.5);
}

TEST_F(TestMatrix3x3, CanMultiplyNumberByMatrix)
{
    constexpr double val = 2.0;

    mc::Matrix3x3d m1(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);
    mc::Matrix3x3d mr;
    mr = val * m1;

    EXPECT_DOUBLE_EQ(mr.xx(),  2.0);
    EXPECT_DOUBLE_EQ(mr.xy(),  4.0);
    EXPECT_DOUBLE_EQ(mr.xz(),  6.0);
    EXPECT_DOUBLE_EQ(mr.yx(),  8.0);
    EXPECT_DOUBLE_EQ(mr.yy(), 10.0);
    EXPECT_DOUBLE_EQ(mr.yz(), 12.0);
    EXPECT_DOUBLE_EQ(mr.zx(), 14.0);
    EXPECT_DOUBLE_EQ(mr.zy(), 16.0);
    EXPECT_DOUBLE_EQ(mr.zz(), 18.0);
}