/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/
#ifndef MCUTILS_MATH_STATSUTILS_H_
#define MCUTILS_MATH_STATSUTILS_H_

#include <cmath>

#include <mcutils/math/MathUtils.h>

namespace mc {
namespace math {

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
inline double standardDeviation(double sum, double sum_sq, int n)
{
    double coef = 1.0 / (static_cast<double>(n) - 1.0);
    double s2 = sum_sq * coef - math::pow<2>(sum) * coef / static_cast<double>(n);
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
inline double standardDeviation(const std::vector<double>& x)
{
    double sum = 0.0;
    double sum_sq = 0.0;
    for (const auto& xx : x)
    {
        sum += xx;
        sum_sq += xx * xx;
    }
    return standardDeviation(sum, sum_sq, x.size());
}

} // namespace math
} // namespace mc

#endif // MCUTILS_MATH_STATSUTILS_H_
