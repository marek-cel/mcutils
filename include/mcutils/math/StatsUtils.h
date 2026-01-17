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
#ifndef MCUTILS_MATH_STATSUTILS_H_
#define MCUTILS_MATH_STATSUTILS_H_

#include <cmath>
#include <vector>

#include <mcutils/math/MathUtils.h>

namespace mc {

/**
 * \brief Estimates standard deviation based on a sample.
 *
 * ### References:
 * - [Standard deviation - Wikipedia](https://en.wikipedia.org/wiki/Standard_deviation)
 * - [Algorithms for calculating variance - Wikipedia](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance)
 *
 * \param sum sum of samples values
 * \param sum_sq sum of samples values squared
 * \param n number of samples
 * \return standard deviation
 */
template <typename T, typename T_SQ>
inline T standardDeviation(T sum, T_SQ sum_sq, int n)
{
    double coef = 1.0 / (static_cast<double>(n) - 1.0);
    auto s2 = sum_sq * coef - npow<2>(sum) * coef / static_cast<double>(n);
    return sqrt(s2);
}

/**
 * \brief Estimates standard deviation based on a sample.
 *
 * ### References:
 * - [Standard deviation - Wikipedia](https://en.wikipedia.org/wiki/Standard_deviation)
 * - [Algorithms for calculating variance - Wikipedia](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance)
 *
 * \param x samples
 * \return standard deviation
 */
template <typename T>
inline T standardDeviation(const std::vector<T>& x)
{
    T sum = T{0};
    auto sum_sq{0};
    for (const auto& xx : x)
    {
        sum += xx;
        sum_sq += xx * xx;
    }
    return standardDeviation(sum, sum_sq, x.size());
}

} // namespace mc

#endif // MCUTILS_MATH_STATSUTILS_H_
