#ifdef __linux__

#include <gtest/gtest.h>

#include <chrono>
#include <memory>

#include <mcutils/log/Log.h>
#include <mcutils/log/SysLogger.h>

#define MSG std::string("Lorem ipsum dolor sit amet")
#define TIME_DELAY() std::chrono::milliseconds(1000);

std::string getSyslogLastLineStripped()
{
    std::string result;
    FILE* file = popen("tail -n 1 /var/log/syslog", "r");
    if (file)
    {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file))
        {
            result += buffer;
        }
        pclose(file);
    }

    // Format of syslog line:
    // [timestamp] [hostname] [program]: [message]

    // Remove the timestamp and hostname
    size_t pos = result.find(" tests-mcutils: ");
    if (pos != std::string::npos)
    {
        result = result.substr(pos + 16); // 16 is the length of " tests-mcutils: "
    }

    return result;
}

class TestSysLogger : public ::testing::Test
{
protected:

    TestSysLogger() {}
    virtual ~TestSysLogger() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestSysLogger, CanPrintFormatedMsg)
{
    std::shared_ptr<mc::SysLogger> logger = std::make_shared<mc::SysLogger>();
    mc::Log::setLogger(logger);

    EXPECT_NO_THROW(mc::Log::print("aaa %s bbb", MSG.c_str()));
    TIME_DELAY();
    std::string result = getSyslogLastLineStripped();
    std::string expected = "aaa " + MSG + " bbb\n";
    EXPECT_EQ(result, expected);
}

TEST_F(TestSysLogger, CanPrintErrorMsg)
{
    std::shared_ptr<mc::SysLogger> logger = std::make_shared<mc::SysLogger>();
    mc::Log::setLogger(logger);

    EXPECT_NO_THROW(mc::Log::error(MSG.c_str()));
    TIME_DELAY();
    std::string result = getSyslogLastLineStripped();
    std::string expected = "[ERROR] " + MSG + "\n";
    EXPECT_EQ(result, expected);
}

TEST_F(TestSysLogger, CanPrintWarningMsg)
{
    std::shared_ptr<mc::SysLogger> logger = std::make_shared<mc::SysLogger>();
    mc::Log::setLogger(logger);

    EXPECT_NO_THROW(mc::Log::warning(MSG.c_str()));
    TIME_DELAY();
    std::string result = getSyslogLastLineStripped();
    std::string expected = "[WARNING] " + MSG + "\n";
    EXPECT_EQ(result, expected);
}

TEST_F(TestSysLogger, CanPrintInfoMsg)
{
    std::shared_ptr<mc::SysLogger> logger = std::make_shared<mc::SysLogger>();
    mc::Log::setLogger(logger);

    EXPECT_NO_THROW(mc::Log::info(MSG.c_str()));
    TIME_DELAY();
    std::string result = getSyslogLastLineStripped();
    std::string expected = "[INFO] " + MSG + "\n";
    EXPECT_EQ(result, expected);
}

TEST_F(TestSysLogger, CanPrintDebugMsg)
{
    std::shared_ptr<mc::SysLogger> logger = std::make_shared<mc::SysLogger>();
    mc::Log::setLogger(logger);

    EXPECT_NO_THROW(mc::Log::debug(MSG.c_str()));
    TIME_DELAY();
    std::string result = getSyslogLastLineStripped();
    std::string expected = "[DEBUG] " + MSG + "\n";
    EXPECT_EQ(result, expected);
}

#endif // __linux__
