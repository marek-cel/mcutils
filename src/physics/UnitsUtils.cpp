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

#include <mcutils/physics/UnitsUtils.h>

#include <mcutils/units.h>
#include <mcutils/misc/StringUtils.h>

using namespace units::literals;

namespace mc {

units::length::meter_t convertToMeters(const char* unit_name, double value)
{
    if ( 0 == str::compareStrings(unit_name, "m") )
        return value * 1_m;
    else if ( 0 == str::compareStrings(unit_name, "cm") )
        return value * 1_cm;
    else if ( 0 == str::compareStrings(unit_name, "mm") )
        return value * 1_mm;
    else if ( 0 == str::compareStrings(unit_name, "ft") )
        return value * 1_ft;
    else if ( 0 == str::compareStrings(unit_name, "in") )
        return value * 1_in;
    else if ( 0 == str::compareStrings(unit_name, "km") )
        return value * 1_km;
    else if ( 0 == str::compareStrings(unit_name, "mi") )
        return value * 1_mi;
    else if ( 0 == str::compareStrings(unit_name, "nmi") )
        return value * 1_nmi;

    return 1_m * std::numeric_limits<double>::quiet_NaN();
}

units::angle::radian_t convertToRadians(const char* unit_name, double value)
{
    if ( 0 == str::compareStrings(unit_name, "rad") )
        return value * 1_rad;
    else if ( 0 == str::compareStrings(unit_name, "deg") )
        return value * 1_deg;

    return 1_rad * std::numeric_limits<double>::quiet_NaN();
}

units::velocity::meters_per_second_t convertToMPS(const char* unit_name, double value)
{
    if ( 0 == str::compareStrings(unit_name, "mps") )
        return value * 1_mps;
    else if ( 0 == str::compareStrings(unit_name, "fps") )
        return value * 1_fps;
    else if ( 0 == str::compareStrings(unit_name, "kph") )
        return value * 1_kph;
    else if ( 0 == str::compareStrings(unit_name, "kts") )
        return value * 1_kts;
    else if ( 0 == str::compareStrings(unit_name, "mph") )
        return value * 1_mph;
    else if ( 0 == str::compareStrings(unit_name, "fpm") )
        return value * 1_fpm;

    return 1_mps * std::numeric_limits<double>::quiet_NaN();
}

units::mass::kilogram_t convertToKilograms(const char* unit_name, double value)
{
    if ( 0 == str::compareStrings(unit_name, "kg") )
        return value * 1_kg;
    else if ( 0 == str::compareStrings(unit_name, "g") )
        return value * 1_g;
    else if ( 0 == str::compareStrings(unit_name, "lb") )
        return value * 1_lb;
    else if ( 0 == str::compareStrings(unit_name, "slug") )
        return value * 1_slug;
    else if ( 0 == str::compareStrings(unit_name, "t") )
        return value * 1_t;

    return 1_kg * std::numeric_limits<double>::quiet_NaN();
}

} // namespace mc
