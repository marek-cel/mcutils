#include <gtest/gtest.h>

#include <mcutils/time/ClockTime.h>

class TestClockTime : public ::testing::Test
{
protected:
    TestClockTime() {}
    virtual ~TestClockTime() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestClockTime, CanGetClockTime)
{
#   ifdef __linux__
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    double expectedValue = ts.tv_sec + 1.0e-9 * ts.tv_nsec;
#   endif

#   ifdef WIN32
    double expectedValue = static_cast<double>(clock()) / static_cast<double>(CLOCKS_PER_SEC);
#   endif

    double outputValue = mc::getClockTime();

    EXPECT_NEAR(expectedValue, outputValue, 1.0e-6);
}
