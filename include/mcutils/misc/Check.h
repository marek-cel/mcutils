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
#ifndef MCUTILS_MISC_CHECK_H_
#define MCUTILS_MISC_CHECK_H_

#ifdef _MSC_VER
#   include <float.h>
#endif

#include <cmath>
#include <vector>

namespace mc {
namespace check {

/**
 * \brief Checks if given varaible is Infinite.
 * \param val value to test
 * \return function returns TRUE if tested value is Infinite, TRUE otherwise
 */
template <typename T>
inline bool isInf(const T& val)
{
#   ifdef _MSC_VER
    return !_finite(static_cast<double>(val));
#   else
    return std::isinf(static_cast<double>(val));
#   endif
}

/**
 * \brief Checks if given varaible is NaN.
 * \param val value to test
 * \return function returns TRUE if tested value is NaN, TRUE otherwise
 */
template <typename T>
inline bool isNaN(const T& val)
{
    return val != val;
}

/**
 * \brief Checks if given varaible is Infinite or NaN.
 * \param val value to test
 * \return function returns FALSE if tested value is Infinite or NaN, TRUE otherwise
 */
template <typename T>
inline bool isValid(const T& val)
{
    return !(isNaN(val) || isInf(val));
}

/**
 * \brief Checks if given array is Infinite or NaN.
 * \param array array to test
 * \param size the size of given array
 * \return function returns FALSE if tested array is Infinite or NaN, TRUE otherwise
 */
template <typename T>
inline bool isValid(const T array[], unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        if ( isNaN(array[i]) || isInf(array[i]) ) 
            return false;
    }

    return true;
}

} // namespace check
} // namespace mc

#endif // MCUTILS_MISC_CHECK_H_
