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
#ifndef MCUTILS_LOG_ILOGGER_H_
#define MCUTILS_LOG_ILOGGER_H_

namespace mc {

/**
 * \brief Interface for logging functionality.
 */
class ILogger
{
public:

    // LCOV_EXCL_START
    ILogger() = default;
    ILogger(const ILogger&) = delete;
    ILogger(ILogger&&) = delete;
    virtual ~ILogger() = default;
    ILogger& operator=(const ILogger&) = delete;
    ILogger& operator=(ILogger&&) = delete;
    // LCOV_EXCL_STOP

    /**
     * \brief Prints a log message.
     * \param format message format
     * \param args variable argument list
     */
    virtual void print(const char* format, va_list args) = 0;

    /**
     * \brief Prints a debug log message.
     * \param format message format
     * \param args variable argument list
     */
    virtual void error(const char* format, va_list args) = 0;

    /**
     * \brief Prints a warning log message.
     * \param format message format
     * \param args variable argument list
     */
    virtual void warning(const char* format, va_list args) = 0;

    /**
     * \brief Prints an info log message.
     * \param format message format
     * \param args variable argument list
     */
    virtual void info(const char* format, va_list args) = 0;

    /**
     * \brief Prints a debug log message.
     * \param format message format
     * \param args variable argument list
     */
    virtual void debug(const char* format, va_list args) = 0;
};

} // namespace mc

#endif // MCUTILS_LOG_ILOGGER_H_
