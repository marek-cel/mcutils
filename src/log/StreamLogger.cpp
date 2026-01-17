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

#include <mcutils/log/StreamLogger.h>

#include <cmath>
#include <ctime>
#include <sstream>
#include <string>

#ifdef __linux__
#   include <sys/time.h>
#endif

#ifdef WIN32
#   include <Windows.h>
#endif

#include <mcutils/time/ISO8601.h>

namespace mc {

void StreamLogger::print(VerboseLevel level, bool tag, const char* format, va_list args)
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

    std::stringstream ss;
    if ( tag )
    {
        switch (level)
        {
        case VerboseLevel::Error:
            ss << "[ERROR]";
            break;

        case VerboseLevel::Warning:
            ss << "[WARNING]";
            break;

        case VerboseLevel::Info:
            ss << "[INFO]";
            break;

        case VerboseLevel::Debug:
            ss << "[DEBUG]";
            break;
        }
    }

    ss << " " << (buf ? buf : "") << "\n";
    std::string msg = ss.str();

    if ( buf ) { delete [] buf; } buf = nullptr;

    std::ostream* out = _out_stream == nullptr ? &std::cout : _out_stream;
    if ( tag )
    {
        *out << timestamp();
    }
    *out << msg;
    out->flush();
}

std::string StreamLogger::timestamp()
{
    int year = 2000;
    int mon  = 1;
    int day  = 1;
    int hour = 0;
    int min  = 0;
    int sec  = 0;
    int msec = 0;

#   ifdef __linux__
    struct timeval tp;
    gettimeofday(&tp, NULL);
    std::tm *tm = std::localtime(&tp.tv_sec);

    year = 1900 + tm->tm_year;
    mon  = tm->tm_mon + 1;
    day  = tm->tm_mday;
    hour = tm->tm_hour;
    min  = tm->tm_min;
    sec  = tm->tm_sec;
    msec = floor(tp.tv_usec * 0.001);
#   endif // __linux__

#   ifdef WIN32
    SYSTEMTIME st;
    GetLocalTime(&st);

    year = st.wYear;
    mon  = st.wMonth;
    day  = st.wDay;
    hour = st.wHour;
    min  = st.wMinute;
    sec  = st.wSecond;
    msec = st.wMilliseconds;
#   endif // WIN32

    return "[" + toISO8601(year, mon, day, hour, min, sec, msec) + "]";
}

} // namespace mc
