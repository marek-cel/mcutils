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

#include <mcutils/geo/Mercator.h>

using namespace units::literals;
using namespace units::math;

namespace mc {

Mercator::Mercator(const Ellipsoid& e)
    : _e(e)
    , _max_x(calculateX( 180.0_deg ))
    , _max_y(calculateY(  85.0_deg ))
{}

units::angle::radian_t Mercator::calculateLat(units::length::meter_t y,
                                              units::angle::radian_t max_error,
                                              unsigned int max_iterations)
{
    // for lat_ts=0 k0=a
    return calculateT_inv(exp((-y / _e.a())()), max_error(), max_iterations);
}

units::angle::radian_t Mercator::calculateLon(units::length::meter_t x)
{
    // for lat_ts=0 k0=a
    return units::angle::radian_t(static_cast<double>(x / _e.a()));
}

units::length::meter_t Mercator::calculateX(units::angle::radian_t lon)
{
    // for lat_ts=0 k0=a
    return _e.a() * lon();
}

units::length::meter_t Mercator::calculateY(units::angle::radian_t lat)
{
    // for lat_ts=0 k0=a
    return _e.a() * log(calculateT(lat));
}

double Mercator::calculateT(units::angle::radian_t lat)
{
    double e_sinLat = _e.e() * sin(lat);
    return tan(M_PI_4 + 0.5 * lat()) * pow((1.0 - e_sinLat) / (1.0 + e_sinLat), 0.5 * _e.e());
}

units::angle::radian_t Mercator::calculateT_inv(double t, double max_error,
                                                unsigned int max_iterations)
{
    double lat = M_PI_2 - 2.0 * atan(t);
    double ex = 0.5 * _e.e();
    double er = 1.0e16;

    unsigned int iteration = 0;

    while ( er > max_error && iteration < max_iterations )
    {
        double e_sinLat = _e.e() * sin(lat);
        double lat_new = M_PI_2
            - 2.0 * atan(t * pow((1.0 - e_sinLat) / (1.0 + e_sinLat), ex));

        er = fabs(lat_new - lat);
        lat = lat_new;

        iteration++;
    }

    return units::angle::radian_t(lat);
}

} // namespace mc
