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
    return check::isValid(_phi)
        && check::isValid(_tht)
        && check::isValid(_psi);
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
