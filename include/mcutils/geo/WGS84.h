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
#ifndef MCUTILS_GEO_WGS84_H_
#define MCUTILS_GEO_WGS84_H_

#include <units.h>

#include <mcutils/extra_units.h>
#include <mcutils/geo/Ellipsoid.h>

using namespace units::literals;

namespace mc {

/**
 * \brief US Department of Defense World Geodetic System 1984 (WGS84) ellipsoid
 * and other physical data.
 *
 * ### References:
 * - [Department of Defence World Geodetic System 1984, NIMA-TR-8350.2](https://apps.dtic.mil/sti/citations/ADA280358)
 */
namespace WGS84 {

static const Ellipsoid ellipsoid(6378137.0_m, 1.0 / 298.257223563); ///< datum ellipsoid

static constexpr units::mass::kilogram_t me = 5.9733328e24_kg;      ///< [kg] mass of the Earth (including atmosphere)
static constexpr units::standard_gravitational_parameter::cubic_meters_per_second_squared_t
    gm = 3986004.418e8_cu_m_per_s_sq;                               ///< [m^3/s^2] Earth’s gravitational constant (mass of Earth’s atmosphere included)
static constexpr units::angular_velocity::degrees_per_second_t
    omega = 360_deg / (23_hr + 56_min + 04.091_s);                  ///< [rad/s] angular velocity of the Earth ( 360deg / 23:56:04.091 )
static constexpr units::acceleration::meters_per_second_squared_t
    gamma   = 9.7976432222_mps_sq;                                  ///< [m/s^2] theoretical (normal) gravity mean value
static constexpr units::acceleration::meters_per_second_squared_t
    gamma_e = 9.7803253359_mps_sq;                                  ///< [m/s^2] theoretical (normal) gravity at the equator (on the ellipsoid)
static constexpr units::acceleration::meters_per_second_squared_t
    gamma_p = 9.8321849378_mps_sq;                                  ///< [m/s^2] theoretical (normal) gravity at the pole (on the ellipsoid)
static constexpr double k = 0.00193185265241;                       ///< [-] theoretical (normal) gravity formula constant
static constexpr double m = 0.00344978650684;                       ///< [-] m = omega^2 * a^2 * b / GM

} // namespace DataWGS84

} // namespace mc

#endif // MCUTILS_GEO_WGS84_H_
