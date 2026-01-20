#include <gtest/gtest.h>

#include <mcutils/time/ISO8601.h>

class TestISO8601 : public ::testing::Test
{
protected:
    TestISO8601() {}
    virtual ~TestISO8601() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestISO8601, CanConvertToISO8601FromYMDHMSms)
{
    std::string result;

    result = mc::time::toISO8601(2001, 02, 03, 14, 15, 16, 123);
    EXPECT_STREQ(result.c_str(), "2001-02-03T14:15:16.123");

    result = mc::time::toISO8601(2001, 02, 03, 14, 15, 16, 123, true);
    EXPECT_STREQ(result.c_str(), "2001-02-03T14:15:16.123");

    result = mc::time::toISO8601(2001, 02, 03, 14, 15, 16, 123, false);
    EXPECT_STREQ(result.c_str(), "2001-02-03T14:15:16");
}

TEST_F(TestISO8601, CanConvertToISO8601FromYMD)
{
    std::string result;

    result = mc::time::toISO8601(2001, 02, 03);
    EXPECT_STREQ(result.c_str(), "2001-02-03");
}

TEST_F(TestISO8601, CanConvertToISO8601FromHMSms)
{
    std::string result;

    result = mc::time::toISO8601(2, 3, 4, 1);
    EXPECT_STREQ(result.c_str(), "02:03:04.001");

    result = mc::time::toISO8601(14, 15, 16, 123, true);
    EXPECT_STREQ(result.c_str(), "14:15:16.123");

    result = mc::time::toISO8601(14, 15, 16, 123, false);
    EXPECT_STREQ(result.c_str(), "14:15:16");
}

TEST_F(TestISO8601, CanConvertToISO8601FromDateTime)
{
    mc::DateTime date_time;

    date_time.year   = 2001;
    date_time.month  = 02;
    date_time.day    = 03;
    date_time.hour   = 2;
    date_time.minute = 3;
    date_time.second = 4;
    date_time.msec   = 1;

    std::string result;

    result = mc::time::toISO8601(date_time);
    EXPECT_STREQ(result.c_str(), "2001-02-03T02:03:04.001");

    result = mc::time::toISO8601(date_time, true);
    EXPECT_STREQ(result.c_str(), "2001-02-03T02:03:04.001");

    result = mc::time::toISO8601(date_time, false);
    EXPECT_STREQ(result.c_str(), "2001-02-03T02:03:04");
}
