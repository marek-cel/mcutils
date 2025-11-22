#include <gtest/gtest.h>

#include <memory>
#include <sstream>

#include <mcutils/log/Log.h>
#include <mcutils/log/StreamLogger.h>

#define MSG std::string("Lorem ipsum dolor sit amet")

class TestLog : public ::testing::Test
{
protected:

    std::stringstream ss;

    TestLog()
    {
        std::shared_ptr<mc::StreamLogger> logger = std::make_shared<mc::StreamLogger>();
        logger->setOutStream(&ss);
        mc::Log::setLogger(logger);
    }
    virtual ~TestLog() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestLog, CanPrintFormatedMsg)
{
    std::string expected = " aaa " + MSG + " bbb\n";

    EXPECT_NO_THROW(mc::Log::print("aaa %s bbb", MSG.c_str()));
    std::string result = ss.str();
    EXPECT_TRUE(result == expected) << "Expected: " << expected << ", got: " << result;
}

TEST_F(TestLog, CanPrintErrorMsg)
{
    std::string expected = "[ERROR] " + MSG + "\n";

    mc::Log::setVerboseLevel(mc::VerboseLevel::Error);

    EXPECT_NO_THROW(mc::Log::error(MSG.c_str()));
    std::string result = ss.str().substr(25); // 25 characters for timestamp
    EXPECT_TRUE(result == expected);
}

TEST_F(TestLog, CanPrintWarningMsg)
{
    std::string expected;
    std::string result;

    mc::Log::setVerboseLevel(mc::VerboseLevel::Error);

    EXPECT_NO_THROW(mc::Log::warning(MSG.c_str()));
    expected = "";
    result = ss.str();
    EXPECT_TRUE(result == expected);

    mc::Log::setVerboseLevel(mc::VerboseLevel::Warning);
    EXPECT_NO_THROW(mc::Log::warning(MSG.c_str()));
    result   = ss.str().substr(25); // 25 characters for timestamp
    expected = "[WARNING] " + MSG + "\n";
    EXPECT_TRUE(result == expected);
}

TEST_F(TestLog, CanPrintInfoMsg)
{
    std::string result;
    std::string expected;

    mc::Log::setVerboseLevel(mc::VerboseLevel::Warning);
    EXPECT_NO_THROW(mc::Log::info(MSG.c_str()));
    result   = ss.str();
    expected = "";
    EXPECT_TRUE(result == expected);

    mc::Log::setVerboseLevel(mc::VerboseLevel::Info);
    EXPECT_NO_THROW(mc::Log::info(MSG.c_str()));
    result   = ss.str().substr(25); // 25 characters for timestamp
    expected = "[INFO] " + MSG + "\n";
    EXPECT_TRUE(result == expected);
}

TEST_F(TestLog, CanPrintDebugMsg)
{
    std::string result;
    std::string expected;

    mc::Log::setVerboseLevel(mc::VerboseLevel::Info);
    EXPECT_NO_THROW(mc::Log::debug(MSG.c_str()));
    result   = ss.str();
    expected = "";
    EXPECT_TRUE(result == expected);

    mc::Log::setVerboseLevel(mc::VerboseLevel::Debug);
    EXPECT_NO_THROW(mc::Log::debug(MSG.c_str()));
    result   = ss.str().substr(25); // 25 characters for timestamp
    expected = "[DEBUG] " + MSG + "\n";
    EXPECT_TRUE(result == expected);
}

TEST_F(TestLog, CanSetVerboseLevel)
{
    std::stringstream ss;
    EXPECT_NO_THROW(mc::Log::setVerboseLevel(mc::VerboseLevel::Debug));
}
