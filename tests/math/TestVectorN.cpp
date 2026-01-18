#include <gtest/gtest.h>

#include <mcutils/math/Vector.h>

#define SIZE 3

class TestVectorN : public ::testing::Test
{
protected:
    TestVectorN() {}
    virtual ~TestVectorN() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestVectorN, CanInstantiate)
{
    mc::VectorN<double,SIZE> v;

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), 0.0) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanInstantiateFromDifferentTypes)
{
    mc::VectorN<float,SIZE> v1;
    v1(0) = 1.0f;
    v1(1) = 2.0f;
    v1(2) = 3.0f;

    mc::VectorN<double,SIZE> v2(v1);

    EXPECT_DOUBLE_EQ(v2(0), 1.0);
    EXPECT_DOUBLE_EQ(v2(1), 2.0);
    EXPECT_DOUBLE_EQ(v2(2), 3.0);
}

TEST_F(TestVectorN, CanValidate)
{
    std::vector<double> x { 1.0, 2.0, 3.0 };
    mc::VectorN<double,SIZE> v;
    v.setFromStdVector(x);
    EXPECT_TRUE(v.isValid());
    v(0) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(v.isValid());
}

TEST_F(TestVectorN, CanGetLengthSquared)
{
    mc::VectorN<double,SIZE> v;

    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    // 1^2 + 2^2 + 3^2 = 1 + 4 + 9 = 14
    EXPECT_DOUBLE_EQ(v.getLengthSq(), 14.0);
}

TEST_F(TestVectorN, CanGetLength)
{
    mc::VectorN<double,SIZE> v;

    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    // expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_vector.m
    // sqrt( 1^2 + 2^2 + 3^2 ) = sqrt( 1 + 4 + 9 ) = sqrt( 14 )
    EXPECT_NEAR(v.getLength(), 3.741657, 1.0e-5);
}

TEST_F(TestVectorN, CanGetNormalized)
{
    mc::VectorN<double,SIZE> v;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    v.setFromStdVector(x);

    mc::VectorN<double,SIZE> vn = v.getNormalized();

    // expected values calculated with GNU Octave
    // tests/mcsim/utils/math/octave/test_vector.m
    EXPECT_NEAR(vn(0), 0.267261, 1.0e-5);
    EXPECT_NEAR(vn(1), 0.534522, 1.0e-5);
    EXPECT_NEAR(vn(2), 0.801784, 1.0e-5);

    EXPECT_DOUBLE_EQ(vn.getLength(), 1.0);
}

TEST_F(TestVectorN, CanGetStdArray)
{
    mc::VectorN<double,SIZE> v;
    std::array<double, SIZE> x { 1.0, 2.0, 3.0 };
    v.setFromStdArray(x);
    std::array<double, SIZE> result;
    result = v.getStdArray();

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_DOUBLE_EQ(result[i], x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanGetStdVector)
{
    mc::VectorN<double,SIZE> v;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    v.setFromStdVector(x);
    std::vector<double> result;
    result = v.getStdVector();

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_DOUBLE_EQ(result[i], x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanSetFromStdArray)
{
    mc::VectorN<double,SIZE> v;
    std::array<double, SIZE> x { 1.0, 2.0, 3.0 };
    v.setFromStdArray(x);

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanSetFromStdVector)
{
    mc::VectorN<double,SIZE> v;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    v.setFromStdVector(x);

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanSetFromString)
{
    char str[] = { " 1.0  2.0  3.0 " };
    mc::VectorN<double,SIZE> v;
    v.setFromString(str);

    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
}

TEST_F(TestVectorN, CanSetFromInvalidString)
{
    char str[] = { "lorem ipsum" };
    mc::VectorN<double,SIZE> v;
    v.setFromString(str);
    EXPECT_FALSE(v.isValid());
}

TEST_F(TestVectorN, CanSwapRows)
{
    mc::VectorN<double,SIZE> v;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    v.setFromStdVector(x);

    v.swapRows(0, 1);
    EXPECT_DOUBLE_EQ(v(0), 2.0);
    EXPECT_DOUBLE_EQ(v(1), 1.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
}

TEST_F(TestVectorN, CanConvertToString)
{
    mc::VectorN<double,SIZE> v;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    v.setFromStdVector(x);

    std::stringstream ss;
    ss << 1.0 << "\t" << 2.0 << "\t" << 3.0;

    EXPECT_STREQ(v.toString().c_str(), ss.str().c_str());
}

TEST_F(TestVectorN, CanZeroize)
{
    mc::VectorN<double,SIZE> v;
    std::vector<double> x { 1.0, 2.0, 3.0 };
    v.setFromStdVector(x);
    v.zeroize();

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), 0.0) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanCast)
{
    mc::VectorN<double,SIZE> v1;
    v1(0) = 1.0;
    v1(1) = 2.0;
    v1(2) = 3.0;

    mc::VectorN<float,SIZE> v2;
    v2 = static_cast<mc::VectorN<float,SIZE>>(v1);
    EXPECT_DOUBLE_EQ(v2(0), 1.0);
    EXPECT_DOUBLE_EQ(v2(1), 2.0);
    EXPECT_DOUBLE_EQ(v2(2), 3.0);
}

TEST_F(TestVectorN, CanAccessElement)
{
    mc::VectorN<double,SIZE> v;

    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 3.0);
}

TEST_F(TestVectorN, CanAddSameType)
{
    mc::VectorN<double,SIZE> v1;
    mc::VectorN<double,SIZE> v2;

    v1(0) = 4.0;
    v1(1) = 5.0;
    v1(2) = 6.0;

    v2(0) = 3.0;
    v2(1) = 2.0;
    v2(2) = 1.0;

    mc::VectorN<double,SIZE> vr = v1 + v2;

    EXPECT_DOUBLE_EQ(vr(0), 7.0);
    EXPECT_DOUBLE_EQ(vr(1), 7.0);
    EXPECT_DOUBLE_EQ(vr(2), 7.0);
}

TEST_F(TestVectorN, CanAddDifferentTypes)
{
    mc::VectorN<float,SIZE> v1;
    mc::VectorN<double,SIZE> v2;

    v1(0) = 4.0f;
    v1(1) = 5.0f;
    v1(2) = 6.0f;

    v2(0) = 3.0;
    v2(1) = 2.0;
    v2(2) = 1.0;

    mc::VectorN<double,SIZE> vr = v1 + v2;

    EXPECT_DOUBLE_EQ(vr(0), 7.0);
    EXPECT_DOUBLE_EQ(vr(1), 7.0);
    EXPECT_DOUBLE_EQ(vr(2), 7.0);
}

TEST_F(TestVectorN, CanNegate)
{
    mc::VectorN<double,SIZE> v;

    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    mc::VectorN<double,SIZE> vr = -v;

    EXPECT_DOUBLE_EQ(vr(0), -1.0);
    EXPECT_DOUBLE_EQ(vr(1), -2.0);
    EXPECT_DOUBLE_EQ(vr(2), -3.0);
}

TEST_F(TestVectorN, CanSubtract)
{
    mc::VectorN<double,SIZE> v1;
    mc::VectorN<double,SIZE> v2;

    v1(0) = 4.0;
    v1(1) = 5.0;
    v1(2) = 6.0;

    v2(0) = 3.0;
    v2(1) = 2.0;
    v2(2) = 1.0;

    mc::VectorN<double,SIZE> vr = v1 - v2;

    EXPECT_DOUBLE_EQ(vr(0), 1.0);
    EXPECT_DOUBLE_EQ(vr(1), 3.0);
    EXPECT_DOUBLE_EQ(vr(2), 5.0);
}

TEST_F(TestVectorN, CanSubtractDifferentTypes)
{
    mc::VectorN<float,SIZE> v1;
    mc::VectorN<double,SIZE> v2;

    v1(0) = 4.0f;
    v1(1) = 5.0f;
    v1(2) = 6.0f;

    v2(0) = 3.0;
    v2(1) = 2.0;
    v2(2) = 1.0;

    mc::VectorN<double,SIZE> vr = v1 - v2;

    EXPECT_DOUBLE_EQ(vr(0), 1.0);
    EXPECT_DOUBLE_EQ(vr(1), 3.0);
    EXPECT_DOUBLE_EQ(vr(2), 5.0);
}

TEST_F(TestVectorN, CanMultiplyFloatVectorByFloatScalar)
{
    std::vector<float> x { 1.0f, 2.0f, 3.0f };
    mc::VectorN<float,SIZE> v;
    v.setFromStdVector(x);

    constexpr float val = 2.0f;
    mc::VectorN<float,SIZE> vr = v * val;

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_FLOAT_EQ(vr(i), x[i] * val) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanMultiplyDoubleVectorByFloatScalar)
{
    std::vector<double> x { 1.0, 2.0, 3.0 };
    mc::VectorN<double,SIZE> v;
    v.setFromStdVector(x);

    constexpr float val = 2.0f;
    mc::VectorN<double,SIZE> vr = v * val;

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x[i] * val) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanMultiplyFloatVectorByDoubleScalar)
{
    std::vector<float> x { 1.0f, 2.0f, 3.0f };
    mc::VectorN<float,SIZE> v;
    v.setFromStdVector(x);

    constexpr double val = 2.0;
    mc::VectorN<double,SIZE> vr = v * val;

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x[i] * val) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanCalculateDotProduct)
{
    std::vector<double> x1 { 1.0, 0.0, 0.0 };
    std::vector<double> x2 { 0.0, 1.0, 0.0 };
    std::vector<double> x3 { 0.0, 0.0, 1.0 };
    std::vector<double> x4 { 1.0, 2.0, 3.0 };

    mc::VectorN<double,SIZE> v1;
    mc::VectorN<double,SIZE> v2;
    mc::VectorN<double,SIZE> v3;
    mc::VectorN<double,SIZE> v4;

    v1.setFromStdVector(x1);
    v2.setFromStdVector(x2);
    v3.setFromStdVector(x3);
    v4.setFromStdVector(x4);

    double s1 = v4 * v1;
    double s2 = v4 * v2;
    double s3 = v4 * v3;
    double s4 = v4 * v4;

    EXPECT_DOUBLE_EQ(s1,  1.0);
    EXPECT_DOUBLE_EQ(s2,  2.0);
    EXPECT_DOUBLE_EQ(s3,  3.0);
    EXPECT_DOUBLE_EQ(s4, 14.0);
}

TEST_F(TestVectorN, CanDivideByScalar)
{
    std::vector<double> x { 1.0, 2.0, 3.0 };
    mc::VectorN<double,SIZE> v;
    v.setFromStdVector(x);

    constexpr double val = 2.0;
    mc::VectorN<double,SIZE> vr = v / val;

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x[i] / val) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanAssign)
{
    mc::VectorN<double,SIZE> v1;
    mc::VectorN<double,SIZE> v2;

    v1(0) = 1.0;
    v1(1) = 2.0;
    v1(2) = 3.0;

    v2 = v1;

    EXPECT_DOUBLE_EQ(v2(0), 1.0);
    EXPECT_DOUBLE_EQ(v2(1), 2.0);
    EXPECT_DOUBLE_EQ(v2(2), 3.0);
}

TEST_F(TestVectorN, CanAssignDifferentTypes)
{
    mc::VectorN<float,SIZE> v1;
    mc::VectorN<double,SIZE> v2;

    v1(0) = 1.0f;
    v1(1) = 2.0f;
    v1(2) = 3.0f;

    v2 = v1;

    EXPECT_DOUBLE_EQ(v2(0), 1.0);
    EXPECT_DOUBLE_EQ(v2(1), 2.0);
    EXPECT_DOUBLE_EQ(v2(2), 3.0);
}

TEST_F(TestVectorN, CanUnaryAdd)
{
    std::vector<double> x1 { 1.0, 2.0, 3.0 };
    std::vector<double> x2 { 4.0, 5.0, 6.0 };

    mc::VectorN<double,SIZE> v1;
    mc::VectorN<double,SIZE> v2;

    v1.setFromStdVector(x1);
    v2.setFromStdVector(x2);

    v1 += v2;

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_DOUBLE_EQ(v1(i), x1[i] + x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnarySubtract)
{
    std::vector<double> x1 { 1.0, 2.0, 3.0 };
    std::vector<double> x2 { 4.0, 5.0, 6.0 };

    mc::VectorN<double,SIZE> v1;
    mc::VectorN<double,SIZE> v2;

    v1.setFromStdVector(x1);
    v2.setFromStdVector(x2);

    v1 -= v2;

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_DOUBLE_EQ(v1(i), x1[i] - x2[i]) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnaryMultiplyByScalar)
{
    std::vector<double> x { 1.0, 2.0, 3.0 };
    mc::VectorN<double,SIZE> v;
    v.setFromStdVector(x);

    constexpr double val = 2.0;
    v *= val;

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i] * val) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanUnaryDivideByScalar)
{
    std::vector<double> x { 1.0, 2.0, 3.0 };
    mc::VectorN<double,SIZE> v;
    v.setFromStdVector(x);

    constexpr double val = 2.0;
    v /= val;

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_DOUBLE_EQ(v(i), x[i] / val) << "Error at index " << i;
    }
}

TEST_F(TestVectorN, CanCompareVectors)
{
    std::vector<double> x1 { 1.0, 2.0, 3.0 };
    std::vector<double> x2 { 4.0, 5.0, 6.0 };
    std::vector<double> x3 { 1.0, 2.0, 3.0 };

    mc::VectorN<double,SIZE> v1;
    mc::VectorN<double,SIZE> v2;
    mc::VectorN<double,SIZE> v3;

    v1.setFromStdVector(x1);
    v2.setFromStdVector(x2);
    v3.setFromStdVector(x3);

    EXPECT_FALSE(v1 == v2);
    EXPECT_FALSE(v1 != v3);
    EXPECT_TRUE(v1 == v3);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(TestVectorN, CanMultiplyScalarByVector)
{
    std::vector<double> x { 1.0, 2.0, 3.0 };
    mc::VectorN<double,SIZE> v;
    v.setFromStdVector(x);

    constexpr double val = 2.0;
    mc::VectorN<double,SIZE> vr = val * v;

    for ( int i = 0; i < SIZE; ++i )
    {
        EXPECT_DOUBLE_EQ(vr(i), x[i] * val) << "Error at index " << i;
    }
}