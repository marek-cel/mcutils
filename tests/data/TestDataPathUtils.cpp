#include <gtest/gtest.h>

#include <mcutils/data/DataPathUtils.h>

class TestDataPathUtils : public ::testing::Test
{
protected:
    TestDataPathUtils() {}
    virtual ~TestDataPathUtils() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestDataPathUtils, CanSplitDataPath)
{
    mc::SplittedDataPath spath;

    spath = mc::splitDataPath("group.data");
    EXPECT_STREQ(spath.lead.c_str(), "group");
    EXPECT_STREQ(spath.trail.c_str(), "data");

    spath = mc::splitDataPath("group.subgroup.data");
    EXPECT_STREQ(spath.lead.c_str(), "group");
    EXPECT_STREQ(spath.trail.c_str(), "subgroup.data");
}

TEST_F(TestDataPathUtils, CanStripDataPathDots)
{
    std::string result;

    result = mc::stripDataPathDots(".group.data");
    EXPECT_STREQ(result.c_str(), "group.data");

    result = mc::stripDataPathDots("group.data.");
    EXPECT_STREQ(result.c_str(), "group.data");

    result = mc::stripDataPathDots(".group.data.");
    EXPECT_STREQ(result.c_str(), "group.data");

    result = mc::stripDataPathDots("..group.data..");
    EXPECT_STREQ(result.c_str(), "group.data");
}