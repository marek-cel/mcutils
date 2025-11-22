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
#ifndef MCUTILS_GEO_MARS2015_H_
#define MCUTILS_GEO_MARS2015_H_

#include <units.h>

#include <mcutils/geo/Ellipsoid.h>

using namespace units::literals;

namespace mc {

/**
 * \brief Martian Coordinate System ellipsoid according to the IAU WGCCRE
 *
 * Martian Coordinate System (MCS) and other physical data.
 *
 * Martian prime merdian goes through the Airy-0 crater.
 *
 * ### References:
 * - Report of the IAU Working Group on Cartographic Coordinates and Rotational Elements: 2015
 * - Mars Geodesy/Cartography Working Group Recommendations on Mars Cartographic Constants and Coordinate Systems, 2011
 * - [Mars - Wikipedia](https://en.wikipedia.org/wiki/Mars)
 * - [Airy-0 - Wikipedia](https://en.wikipedia.org/wiki/Airy-0)
 */
namespace Mars2015 {

static const Ellipsoid ellipsoid(3396190.0_m, 1.0 / 169.894447223612);  ///< datum ellipsoid

static constexpr units::angular_velocity::degrees_per_second_t
    omega = 360_deg / (24_hr + 37_min + 22.7_s);                        ///< [rad/s] angular velocity of the Mars ( 360deg / 24:37:22.7 )
static constexpr units::acceleration::meters_per_second_squared_t
    gamma = 3.72076_mps_sq;                                             ///< [m/s^2] theoretical (normal) gravity mean value
static constexpr units::mass::kilogram_t mm  = 6.4171e23_kg;            ///< [kg] mass of the Mars

} // namespace Mars2015
} // namespace mc

#endif // MCUTILS_GEO_MARS2015_H_
