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
#ifndef MCUTILS_LOG_LOG_H_
#define MCUTILS_LOG_LOG_H_

#include <cstdarg>
#include <memory>
#include <mutex>

#include <mcutils/mcutils_api.h>

#include <mcutils/log/ILogger.h>
#include <mcutils/log/VerboseLevel.h>

namespace mc {

/**
 * \brief Interface for logging functionality.
 */
class MCUTILS_API Log
{
public:

    /**
     * \brief Sets the logger instance.
     * \param logger shared pointer to the logger instance
     */
    static void setLogger(std::shared_ptr<ILogger> logger)
    {
        std::lock_guard<std::mutex> guard(_mtx);
        _logger = logger;
    }

    /**
     * \brief Prints a formatted log message.
     * \param format message format
     */
    inline static void print(const char* format, ...)
    {
        std::lock_guard<std::mutex> guard(_mtx);
        if ( _logger )
        {
            va_list args;
            va_start(args, format);
            _logger->print(format, args);
            va_end(args);
        }
    }

    /**
     * \brief Prints error log message.
     * \param format message format
     */
    inline static void error(const char* format, ...)
    {
        std::lock_guard<std::mutex> guard(_mtx);
        if ( _logger )
        {
            va_list args;
            va_start(args, format);
            _logger->error(format, args);
            va_end(args);
        }
    }

    /**
     * \brief Prints warning log message.
     * \param format message format
     */
    inline static void warning(const char* format, ...)
    {
        std::lock_guard<std::mutex> guard(_mtx);
        if ( _logger && _verb_level >= VerboseLevel::Warning )
        {
            va_list args;
            va_start(args, format);
            _logger->warning(format, args);
            va_end(args);
        }
    }

    /**
     * \brief Prints info log message.
     * \param format message format
     */
    inline static void info(const char* format, ...)
    {
        std::lock_guard<std::mutex> guard(_mtx);
        if ( _logger && _verb_level >= VerboseLevel::Info )
        {
            va_list args;
            va_start(args, format);
            _logger->info(format, args);
            va_end(args);
        }
    }

    /**
     * \brief Prints debug log message.
     * \param format message format
     */
    inline static void debug(const char* format, ...)
    {
        std::lock_guard<std::mutex> guard(_mtx);
        if ( _logger && _verb_level >= VerboseLevel::Debug )
        {
            va_list args;
            va_start(args, format);
            _logger->debug(format, args);
            va_end(args);
        }
    }

    inline static void setVerboseLevel(VerboseLevel level)
    {
        std::lock_guard<std::mutex> guard(_mtx);
        _verb_level = level;
    }

protected:

    static std::mutex _mtx;                     ///< mutex for thread safety
    static std::shared_ptr<ILogger> _logger;    ///< shared pointer to the logger instance
    static VerboseLevel _verb_level;            ///< verbose level (default Info)
};

} // namespace mc

#endif // MCUTILS_LOG_LOG_H_
