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
#ifndef MCUTILS_PHYSICS_UNITSUTILS_H_
#define MCUTILS_PHYSICS_UNITSUTILS_H_

#include <units.h>

#include <mcutils/mcutils_api.h>

namespace mc {

/**
 * \brief Converts a given value from a specified unit to meters.
 * \param unit_name name of the unit to convert from (e.g., "m", "cm", "mm", etc.)
 * \param value value to convert
 * \return converted value in meters
 */
MCUTILS_API units::length::meter_t convertToMeters(const char* unit_name, double value = 1.0);

/**
 * \brief Converts a given value from a specified unit to radians.
 * \param unit_name name of the unit to convert from (e.g., "rad", "deg", etc.)
 * \param value value to convert
 * \return converted value in radians
 */
MCUTILS_API units::angle::radian_t convertToRadians(const char* unit_name, double value = 1.0);

/**
 * \brief Converts a given value from a specified unit to meters per second.
 * \param unit_name name of the unit to convert from (e.g., "mps", "fps", "kph", "kts", etc.)
 * \param value value to convert
 * \return converted value in meters per second
 */
MCUTILS_API units::velocity::meters_per_second_t convertToMPS(const char* unit_name, double value = 1.0);

/**
 * \brief Converts a given value from a specified unit to kilograms.
 * \param unit_name name of the unit to convert from (e.g., "kg", "g", "lb", etc.)
 * \param value value to convert
 * \return converted value in kilograms
 */
MCUTILS_API units::mass::kilogram_t convertToKilograms(const char* unit_name, double value = 1.0);

} // namespace mc

#endif // MCUTILS_PHYSICS_UNITSUTILS_H_
