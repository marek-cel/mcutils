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

#ifdef __linux__

#include <mcutils/log/SysLogger.h>

#include <cmath>
#include <ctime>
#include <sstream>
#include <string>

#include <syslog.h>

namespace mc {

void SysLogger::print(VerboseLevel level, bool tag, const char* format, va_list args)
{
    char* buf = nullptr;

    va_list args2;
    va_copy(args2, args);
    size_t size = vsnprintf(nullptr, 0, format, args);
    va_end(args);

    if (size > 0)
    {
        buf = new char[size+1];
        vsnprintf(buf, size+1, format, args2);
    }

    va_end(args2);

    int priority = LOG_DEBUG;
    std::string msg;

    switch (level)
    {
    case VerboseLevel::Error:
        priority = LOG_ERR;
        if ( tag ) msg = "[ERROR] ";
        break;

    case VerboseLevel::Warning:
        priority = LOG_WARNING;
        if ( tag ) msg = "[WARNING] ";
        break;

    case VerboseLevel::Info:
        priority = LOG_INFO;
        if ( tag ) msg = "[INFO] ";
        break;

    case VerboseLevel::Debug:
        priority = LOG_DEBUG;
        if ( tag ) msg = "[DEBUG] ";
        break;
    }

    msg += (buf ? buf : "");

    if ( buf ) { delete [] buf; } buf = nullptr;

    syslog(priority, "%s", msg.c_str());
}

} // namespace mc

#endif // __linux__
