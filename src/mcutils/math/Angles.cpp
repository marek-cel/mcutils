/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/

#include <mcutils/math/Angles.h>

#include <iomanip>
#include <sstream>

#include <mcutils/misc/Check.h>

namespace mc {

units::angle::radian_t Angles::normalize(units::angle::radian_t val,
                                         units::angle::radian_t min)
{
    units::angle::radian_t tmp = val;
    units::angle::radian_t max = min + 360_deg;

    while (tmp < min) tmp += 360_deg;
    while (tmp > max) tmp -= 360_deg;

    return tmp;
}

Angles::Angles(units::angle::radian_t phi,
               units::angle::radian_t tht,
               units::angle::radian_t psi)
{
    set(phi, tht, psi);
}

bool Angles::isValid() const
{
    return misc::isValid(_phi)
        && misc::isValid(_tht)
        && misc::isValid(_psi);
}

void Angles::normalize()
{
    while (_tht >  90_deg)
    {
        _phi += 180_deg;
        _tht =  90_deg - ( _tht - 90_deg );
        _psi += 180_deg;
    }

    while (_tht < -90_deg)
    {
        _phi += 180_deg;
        _tht = -90_deg - ( _tht + 90_deg );
        _psi += 180_deg;
    }

    while (_phi >  180_deg) _phi -= 360_deg;
    while (_phi < -180_deg) _phi += 360_deg;

    while (_psi >= 360_deg) _psi -= 360_deg;
    while (_psi <    0_deg) _psi += 360_deg;
}

void Angles::set(units::angle::radian_t phi,
                 units::angle::radian_t tht,
                 units::angle::radian_t psi)
{
    _phi = phi;
    _tht = tht;
    _psi = psi;
}

std::string Angles::toString() const
{
    std::stringstream ss;

    ss.setf(std::ios_base::showpoint);
    ss.setf(std::ios_base::fixed);

    ss << std::setprecision(2) << units::angle::degree_t(_phi)() << " deg";
    ss << "\t";
    ss << std::setprecision(2) << units::angle::degree_t(_tht)() << " deg";
    ss << "\t";
    ss << std::setprecision(2) << units::angle::degree_t(_psi)() << " deg";

    return ss.str();
}

bool Angles::operator==(const Angles& angl) const
{
    return (_phi == angl._phi)
        && (_tht == angl._tht)
        && (_psi == angl._psi);
}

bool Angles::operator!=(const Angles& angl) const
{
    return !(*this == angl);
}

} // namespace mc
