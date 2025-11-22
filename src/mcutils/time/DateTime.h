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
#ifndef MCUTILS_TIME_DATETIME_H_
#define MCUTILS_TIME_DATETIME_H_

#include <cstdint>

namespace mc {

/**
 * \brief The date struct
 */
struct Date
{
    uint16_t year   = 0;    ///< year
    uint8_t  month  = 0;    ///< month
    uint8_t  day    = 0;    ///< day
};

/**
 * \brief The time struct
 */
struct Time
{
    uint8_t  hour   = 0;    ///< hour
    uint8_t  minute = 0;    ///< minute
    uint8_t  second = 0;    ///< second
    uint16_t msec   = 0;    ///< millisecond
};

/**
 * \brief The date and time struct
 */
struct DateTime : public Date , public Time
{};

} // namespace mc

#endif // MCUTILS_TIME_DATETIME_H_
