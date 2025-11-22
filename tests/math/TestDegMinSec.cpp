#include <gtest/gtest.h>

#include <mcutils/math/DegMinSec.h>

class TestDegMinSec : public ::testing::Test
{
protected:
    TestDegMinSec() {}
    virtual ~TestDegMinSec() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestDegMinSec, CanInstantiate)
{
    mc::DegMinSec dms;

    EXPECT_EQ(dms.deg(), 0);
    EXPECT_EQ(dms.min(), 0);
    EXPECT_DOUBLE_EQ(dms.sec(), 0.0);
}

TEST_F(TestDegMinSec, CanInstantiateAndSetData)
{
    mc::DegMinSec dms(1.0_deg + 2.0_deg / 60.0 + 3.0_deg / 3600.0);

    EXPECT_EQ(dms.deg(), 1);
    EXPECT_EQ(dms.min(), 2);
    EXPECT_NEAR(dms.sec(), 3.0, 1e-9);
}

TEST_F(TestDegMinSec, CanValidate)
{
    mc::DegMinSec dms1(45_deg);
    EXPECT_TRUE(dms1.isValid());

    units::angle::degree_t deg_nan { std::numeric_limits<double>::quiet_NaN() };
    mc::DegMinSec dms2(deg_nan);
    EXPECT_FALSE(dms2.isValid());
}

TEST_F(TestDegMinSec, CanGetAngle)
{
    mc::DegMinSec dms(45_deg);
    EXPECT_DOUBLE_EQ(dms.getAngle()(), 45.0);
}

TEST_F(TestDegMinSec, CanSetAngle)
{
    mc::DegMinSec dms;
    dms.setAngle(45_deg);
    EXPECT_DOUBLE_EQ(dms.getAngle()(), 45.0);
}

TEST_F(TestDegMinSec, CanConvertToString)
{
    mc::DegMinSec dms(1.0_deg + 2.0_deg / 60.0 + 3.0_deg / 3600.0);
    EXPECT_STREQ(dms.toString().c_str(), "1 deg 2 min 3.00 sec");
}

TEST_F(TestDegMinSec, CanCompare)
{
    mc::DegMinSec dms;

    mc::DegMinSec dms1(1.0_deg + 2.0_deg / 60.0 + 3.0_deg / 3600.0);

    EXPECT_FALSE(dms == dms1);
    EXPECT_TRUE(dms != dms1);
    dms = dms1;
    EXPECT_TRUE(dms == dms1);
    EXPECT_FALSE(dms != dms1);
}
