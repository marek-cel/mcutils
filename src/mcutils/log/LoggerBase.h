/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef MCUTILS_LOG_LOGGERBASE_H_
#define MCUTILS_LOG_LOGGERBASE_H_

#include <cstdarg>

#include <mcutils/log/ILogger.h>
#include <mcutils/log/VerboseLevel.h>

namespace mc {

/**
 * \brief Base class for logging functionality.
 *
 * This class implements the ILogger interface and provides default implementations
 * for the logging methods. It is intended to be subclassed by specific logger
 * implementations that define how the log messages are actually printed.
 */
class LoggerBase : public ILogger
{
public:

    /**
     * \brief Prints a log message.
     * \param format message format
     * \param args variable argument list
     */
    inline void print(const char* format, va_list args) override
    {
        print(VerboseLevel::Error, false, format, args);
    }

    /**
     * \brief Prints a debug log message.
     * \param format message format
     * \param args variable argument list
     */
    inline void error(const char* format, va_list args) override
    {
        print(VerboseLevel::Error, true, format, args);
    }

    /**
     * \brief Prints a warning log message.
     * \param format message format
     * \param args variable argument list
     */
    inline void warning(const char* format, va_list args) override
    {
        print(VerboseLevel::Warning, true, format, args);
    }

    /**
     * \brief Prints an info log message.
     * \param format message format
     * \param args variable argument list
     */
    inline void info(const char* format, va_list args) override
    {
        print(VerboseLevel::Info, true, format, args);
    }

    /**
     * \brief Prints a debug log message.
     * \param format message format
     * \param args variable argument list
     */
    inline void debug(const char* format, va_list args) override
    {
        print(VerboseLevel::Debug, true, format, args);
    }

protected:

    /**
     * \brief Prints log message.
     * \param level verbose level
     * \param tag specifies if tag should be printed
     * \param format message format
     * \param args variable argument list
     */
    virtual void print(VerboseLevel level, bool tag, const char* format, va_list args) = 0;

};

} // namespace mc

#endif // MCUTILS_LOG_LOGGERBASE_H_
