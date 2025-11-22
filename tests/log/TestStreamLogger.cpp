#include <gtest/gtest.h>

#include <memory>
#include <sstream>

#include <mcutils/log/Log.h>
#include <mcutils/log/StreamLogger.h>

#define MSG std::string("Lorem ipsum dolor sit amet")

class TestStreamLogger : public ::testing::Test
{
protected:

    TestStreamLogger() {}
    virtual ~TestStreamLogger() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestStreamLogger, CanSetOutStream)
{
    std::stringstream ss;
    mc::StreamLogger logger;
    EXPECT_NO_THROW(logger.setOutStream(&ss));
}

TEST_F(TestStreamLogger, CanPrintFormatedMsg)
{
    std::stringstream ss;
    std::shared_ptr<mc::StreamLogger> logger = std::make_shared<mc::StreamLogger>();
    logger->setOutStream(&ss);
    mc::Log::setLogger(logger);

    EXPECT_NO_THROW(mc::Log::print("aaa %s bbb", MSG.c_str()));
    std::string result = ss.str();
    std::string expected = " aaa " + MSG + " bbb\n";
    EXPECT_EQ(result, expected);
}

TEST_F(TestStreamLogger, CanPrintErrorMsg)
{
    std::stringstream ss;
    std::shared_ptr<mc::StreamLogger> logger = std::make_shared<mc::StreamLogger>();
    logger->setOutStream(&ss);
    mc::Log::setLogger(logger);

    EXPECT_NO_THROW(mc::Log::error(MSG.c_str()));
    std::string result = ss.str().substr(25); // 25 characters for timestamp
    std::string expected = "[ERROR] " + MSG + "\n";
    EXPECT_EQ(result, expected);
}

TEST_F(TestStreamLogger, CanPrintWarningMsg)
{
    std::stringstream ss;
    std::shared_ptr<mc::StreamLogger> logger = std::make_shared<mc::StreamLogger>();
    logger->setOutStream(&ss);
    mc::Log::setLogger(logger);

    EXPECT_NO_THROW(mc::Log::warning(MSG.c_str()));
    std::string result = ss.str().substr(25); // 25 characters for timestamp
    std::string expected = "[WARNING] " + MSG + "\n";
    EXPECT_EQ(result, expected);
}

TEST_F(TestStreamLogger, CanPrintInfoMsg)
{
    std::stringstream ss;
    std::shared_ptr<mc::StreamLogger> logger = std::make_shared<mc::StreamLogger>();
    logger->setOutStream(&ss);
    mc::Log::setLogger(logger);

    EXPECT_NO_THROW(mc::Log::info(MSG.c_str()));
    std::string result = ss.str().substr(25); // 25 characters for timestamp
    std::string expected = "[INFO] " + MSG + "\n";
    EXPECT_EQ(result, expected);
}

TEST_F(TestStreamLogger, CanPrintDebugMsg)
{
    std::stringstream ss;
    std::shared_ptr<mc::StreamLogger> logger = std::make_shared<mc::StreamLogger>();
    logger->setOutStream(&ss);
    mc::Log::setLogger(logger);

    EXPECT_NO_THROW(mc::Log::debug(MSG.c_str()));
    std::string result = ss.str();//.substr(25); // 25 characters for timestamp
    std::string expected = "[DEBUG] " + MSG + "\n";
    std::cout << "Result: " << result << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    EXPECT_EQ(result, expected);
}
