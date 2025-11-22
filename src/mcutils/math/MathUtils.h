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
#ifndef MCUTILS_MATH_MATHUTILS_H_
#define MCUTILS_MATH_MATHUTILS_H_

#include <cmath>

namespace mc {
namespace math {

/**
 * \brief Checks if value is within the given range.
 * \param min minimum possible value
 * \param max maximum possible value
 * \param val variable to test
 * \return true if val greater than min and less than max, false otherwise
 */
template <typename T>
inline bool isInside(const T& min, const T& max, const T& val)
{
    return min <= val && val <= max;
}

/**
 * \brief Checks if value is outside the given range.
 * \param min minimum possible value
 * \param max maximum possible value
 * \param val variable to test
 * \return true if val greater than min and less than max, false otherwise
 */
template <typename T>
inline bool isOutside(const T& min, const T& max, const T& val)
{
    return min > val || val > max;
}

/**
 * \brief Power function template.
 * \tparam EXPONENT power exponent
 * \tparam T power base type
 * \param base power base
 * \return returns base to the power of the given EXPONENT
 */
template <unsigned int EXPONENT, typename T>
inline auto pow(const T& base)
{
    if constexpr (EXPONENT == 0)
    {
        return 1.0; // dimensionless, sic!
    }
    else
    {
        return base * pow<EXPONENT - 1, T>(base);
    }
}

/**
 * \brief Saturation function. Returns value limited to the given range.
 * \param min minimum possible value
 * \param max maximum possible value
 * \param val variable to test
 * \return min if val less than min, max if val larger than max, val if val larger than min and less than max
 */
template <typename T>
inline T satur(const T& min, const T& max, const T& val)
{
    if      (val < min) return min;
    else if (val > max) return max;
    return val;
}

/**
 * \brief Signum function.
 * \param val input value
 * \return 1 if val is possitive, -1 when val is negative, 0 if val is zero
 */
template <typename T>
inline int sign(const T& val)
{
    constexpr T zero {0};
    if      (val < zero) return -1;
    else if (val > zero) return  1;
    return 0;
}

/**
 * \brief Period of 2.0 fast sine wave approximation.
 * Valid range is -1.0 to 1.0.
 * \param x normalized input value <-1.0;1.0>
 * \return approximated sine wave
 */
inline float sineWave(const float& x)
{
    float y = 4.0f * x - 4.0f * x * fabs(x);
    return 0.225f * (y * fabs(y) - y) + y;
}

/**
 * \brief Smoothstep (sigmoid) 3rd order function.
 * \param xmin minimum argument value
 * \param xmax maximum argument value
 * \param x argument value
 * \return normalized smoothstep function value
 *
 * ### References:
 * - [Smoothstep - Wikipedia](https://en.wikipedia.org/wiki/Smoothstep)
 */
inline double smoothstep(const double& xmin, const double& xmax, double x)
{
    x = satur(0.0, 1.0, (x - xmin) / (xmax - xmin));
    return x * x * (3.0 - 2.0 * x);
}

/**
 * \brief Smoothstep (sigmoid) 3rd order function.
 * \param x normalized argument value
 * \return normalized smoothstep function value
 *
 * ### References:
 * - [Smoothstep - Wikipedia](https://en.wikipedia.org/wiki/Smoothstep)
 */
inline double smoothstep(double x)
{
    return smoothstep(0.0, 1.0, x);
}

/**
 * \brief Smoothstep (sigmoid) 3rd order function.
 * \param xmin minimum argument value
 * \param xmax maximum argument value
 * \param ymin minimum output value
 * \param ymax maximum output value
 * \param x argument value
 * \return smoothstep function value within the given range
 *
 * ### References:
 * - [Smoothstep - Wikipedia](https://en.wikipedia.org/wiki/Smoothstep)
 */
inline double smoothstep(const double& xmin, const double& xmax,
                         const double& ymin, const double& ymax,
                         double x)
{
    return smoothstep(xmin, xmax, x) * (ymax - ymin) + ymin;
}

} // namespace math
} // namespace mc

#endif // MCUTILS_MATH_MATHUTILS_H_
