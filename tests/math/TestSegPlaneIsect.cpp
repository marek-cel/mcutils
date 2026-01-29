#include <gtest/gtest.h>

#include <mcutils/math/SegPlaneIsect.h>

using namespace units::literals;

class TestSegPlaneIsect : public ::testing::Test
{
protected:
    TestSegPlaneIsect() {}
    virtual ~TestSegPlaneIsect() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestSegPlaneIsect, CanCheckIfThereIsSegPlaneIsect)
{
    mc::Vector3_m b;
    mc::Vector3_m e;
    mc::Vector3_m r;
    mc::Vector3d n;

    b = {0.0_m, 0.0_m,  1.0_m};
    e = {0.0_m, 0.0_m, -1.0_m};
    r = {0.0_m, 0.0_m,  0.0_m};
    n = {0.0, 0.0,  1.0};
    EXPECT_TRUE(mc::isSegmentPlaneIsect(b, e, r, n));

    b = {0.0_m, 0.0_m,  1.0_m};
    e = {0.0_m, 0.0_m,  0.0_m};
    r = {0.0_m, 0.0_m, -1.0_m};
    n = {0.0, 0.0,  1.0};
    EXPECT_FALSE(mc::isSegmentPlaneIsect(b, e, r, n));
}

TEST_F(TestSegPlaneIsect, CanGetSegPlaneIsectWithPlaneAtZ0)
{
    mc::Vector3_m b;
    mc::Vector3_m e;
    mc::Vector3_m r;
    mc::Vector3d n;
    mc::Vector3_m i;

    b = {0.0_m, 0.0_m,  1.0_m};
    e = {0.0_m, 0.0_m, -1.0_m};
    r = {0.0_m, 0.0_m,  0.0_m};
    n = {0.0, 0.0,  1.0};
    i = mc::getSegmentPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ(0.0, i.x()());
    EXPECT_DOUBLE_EQ(0.0, i.y()());
    EXPECT_DOUBLE_EQ(0.0, i.z()());

    b = {1.0_m, 1.0_m,  1.0_m};
    e = {1.0_m, 1.0_m, -1.0_m};
    r = {0.0_m, 0.0_m,  0.0_m};
    n = {0.0, 0.0,  1.0};
    i = mc::getSegmentPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ(1.0, i.x()());
    EXPECT_DOUBLE_EQ(1.0, i.y()());
    EXPECT_DOUBLE_EQ(0.0, i.z()());
}

TEST_F(TestSegPlaneIsect, CanGetSegPlaneIsectWithPlaneAtZ05)
{
    mc::Vector3d b;
    mc::Vector3d e;
    mc::Vector3d r;
    mc::Vector3d n;
    mc::Vector3d i;

    b = {0.0, 0.0,  1.0};
    e = {0.0, 0.0, -1.0};
    r = {0.0, 0.0,  0.5};
    n = {0.0, 0.0,  1.0};
    i = mc::getSegmentPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ(0.0, i.x());
    EXPECT_DOUBLE_EQ(0.0, i.y());
    EXPECT_DOUBLE_EQ(0.5, i.z());

    b = {1.0, 1.0,  1.0};
    e = {1.0, 1.0, -1.0};
    r = {0.0, 0.0,  0.5};
    n = {0.0, 0.0,  1.0};
    i = mc::getSegmentPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ(1.0, i.x());
    EXPECT_DOUBLE_EQ(1.0, i.y());
    EXPECT_DOUBLE_EQ(0.5, i.z());
}

TEST_F(TestSegPlaneIsect, CanGetSegPlaneIsectNoIntersection)
{
    mc::Vector3d b;
    mc::Vector3d e;
    mc::Vector3d r;
    mc::Vector3d n;
    mc::Vector3d i;

    // no intersection
    b = {0.0, 0.0,  1.0};
    e = {0.0, 0.0,  0.0};
    r = {0.0, 0.0, -1.0};
    n = {0.0, 0.0,  1.0};
    i = mc::getSegmentPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ(0.0, i.x());
    EXPECT_DOUBLE_EQ(0.0, i.y());
    EXPECT_DOUBLE_EQ(0.0, i.z());

    // no intersection (parallel)
    b = {0.0, 0.0,  1.0};
    e = {1.0, 1.0,  1.0};
    r = {0.0, 0.0, -1.0};
    n = {0.0, 0.0,  1.0};
    i = mc::getSegmentPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ(1.0, i.x());
    EXPECT_DOUBLE_EQ(1.0, i.y());
    EXPECT_DOUBLE_EQ(1.0, i.z());
}

TEST_F(TestSegPlaneIsect, CanGetSegPlaneIsectOnThePlane)
{
    mc::Vector3d b;
    mc::Vector3d e;
    mc::Vector3d r;
    mc::Vector3d n;
    mc::Vector3d i;

    // on the plane
    b = {1.0, 1.0,  0.0};
    e = {0.0, 0.0,  0.0};
    r = {0.0, 0.0,  0.0};
    n = {0.0, 0.0,  1.0};
    i = mc::getSegmentPlaneIsect(b, e, r, n);
    EXPECT_DOUBLE_EQ(1.0, i.x());
    EXPECT_DOUBLE_EQ(1.0, i.y());
    EXPECT_DOUBLE_EQ(0.0, i.z());
}
