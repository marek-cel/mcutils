/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/

#include <mcutils/physics/UnitsUtils.h>

#include <mcutils/extra_units.h>
#include <mcutils/misc/StringUtils.h>

using namespace units::literals;

namespace mc {
namespace physics {

units::length::meter_t convertToMeters(const char* unit_name, double value)
{
    if ( 0 == misc::compareStrings(unit_name, "m") )
        return value * 1_m;
    else if ( 0 == misc::compareStrings(unit_name, "cm") )
        return value * 1_cm;
    else if ( 0 == misc::compareStrings(unit_name, "mm") )
        return value * 1_mm;
    else if ( 0 == misc::compareStrings(unit_name, "ft") )
        return value * 1_ft;
    else if ( 0 == misc::compareStrings(unit_name, "in") )
        return value * 1_in;
    else if ( 0 == misc::compareStrings(unit_name, "km") )
        return value * 1_km;
    else if ( 0 == misc::compareStrings(unit_name, "mi") )
        return value * 1_mi;
    else if ( 0 == misc::compareStrings(unit_name, "nmi") )
        return value * 1_nmi;

    return 1_m * std::numeric_limits<double>::quiet_NaN();
}

units::angle::radian_t convertToRadians(const char* unit_name, double value)
{
    if ( 0 == misc::compareStrings(unit_name, "rad") )
        return value * 1_rad;
    else if ( 0 == misc::compareStrings(unit_name, "deg") )
        return value * 1_deg;

    return 1_rad * std::numeric_limits<double>::quiet_NaN();
}

units::velocity::meters_per_second_t convertToMPS(const char* unit_name, double value)
{
    if ( 0 == misc::compareStrings(unit_name, "mps") )
        return value * 1_mps;
    else if ( 0 == misc::compareStrings(unit_name, "fps") )
        return value * 1_fps;
    else if ( 0 == misc::compareStrings(unit_name, "kph") )
        return value * 1_kph;
    else if ( 0 == misc::compareStrings(unit_name, "kts") )
        return value * 1_kts;
    else if ( 0 == misc::compareStrings(unit_name, "mph") )
        return value * 1_mph;
    else if ( 0 == misc::compareStrings(unit_name, "fpm") )
        return value * 1_fpm;

    return 1_mps * std::numeric_limits<double>::quiet_NaN();
}

units::mass::kilogram_t convertToKilograms(const char* unit_name, double value)
{
    if ( 0 == misc::compareStrings(unit_name, "kg") )
        return value * 1_kg;
    else if ( 0 == misc::compareStrings(unit_name, "g") )
        return value * 1_g;
    else if ( 0 == misc::compareStrings(unit_name, "lb") )
        return value * 1_lb;
    else if ( 0 == misc::compareStrings(unit_name, "slug") )
        return value * 1_slug;
    else if ( 0 == misc::compareStrings(unit_name, "t") )
        return value * 1_t;

    return 1_kg * std::numeric_limits<double>::quiet_NaN();
}

} // namespace physics
} // namespace mc
