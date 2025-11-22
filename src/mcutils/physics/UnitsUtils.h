/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/
#ifndef MCUTILS_PHYSICS_UNITSUTILS_H_
#define MCUTILS_PHYSICS_UNITSUTILS_H_

#include <units.h>

#include <mcutils/mcutils_api.h>

namespace mc {
namespace physics {

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

} // namespace physics
} // namespace mc

#endif // MCUTILS_PHYSICS_UNITSUTILS_H_
