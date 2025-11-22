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
#ifndef MCUTILS_LOG_STREAMLOGGER_H_
#define MCUTILS_LOG_STREAMLOGGER_H_

#include <iostream>

#include <mcutils/mcutils_api.h>

#include <mcutils/log/LoggerBase.h>

namespace mc {

/**
 * \brief Logging class that outputs messages to a stream.
 */
class MCUTILS_API StreamLogger : public LoggerBase
{
public:

    /**
     * \brief Sets output stream.
     * \param outputStream output stream
     */
    inline void setOutStream(std::ostream* out_stream)
    {
        _out_stream = out_stream;
    }

protected:

    std::ostream* _out_stream = &std::cout; ///< output stream, default is std::cout

    /**
     * \brief Prints log message.
     * \param level verbose level
     * \param tag specifies if tag should be printed
     * \param format message format
     * \param args variable argument list
     */
    void print(VerboseLevel level, bool tag, const char* format, va_list args) override;

    /**
     * \brief Returns current timestamp in ISO 8601 format.
     * \return timestamp string
     */
    std::string timestamp();

};

} // namespace mc

#endif // MCUTILS_LOG_STREAMLOGGER_H_
