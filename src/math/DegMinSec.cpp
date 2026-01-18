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

#include <mcutils/math/DegMinSec.h>

#include <iomanip>
#include <sstream>

#include <mcutils/misc/Check.h>

namespace mc {

DegMinSec::DegMinSec(units::angle::degree_t angle)
{
    setAngle(angle);
}

bool DegMinSec::isValid() const
{
    return mc::isValid(_angle)
        && mc::isValid(_deg)
        && mc::isValid(_min)
        && mc::isValid(_sec);
}

void DegMinSec::setAngle(units::angle::degree_t angle)
{
    _angle = angle;

    double deg_abs = fabs(angle());

    _deg = static_cast<int>(floor(deg_abs));
    _min = static_cast<int>(floor((deg_abs - _deg) * 60));
    _sec = (deg_abs - _deg - _min / 60.0) * 3600.0;

    if (angle < 0_deg) _deg *= -1;
}

std::string DegMinSec::toString() const
{
    std::stringstream ss;

    ss.setf(std::ios_base::showpoint);
    ss.setf(std::ios_base::fixed);

    ss << _deg << " deg ";
    ss << _min << " min ";
    ss << std::setprecision(2) << _sec << " sec";

    return ss.str();
}

bool DegMinSec::operator==(const DegMinSec& dms) const
{
    return _deg == dms._deg
        && _min == dms._min
        && _sec == dms._sec;
}

bool DegMinSec::operator!=(const DegMinSec& dms) const
{
    return _deg != dms._deg
        || _min != dms._min
        || _sec != dms._sec;
}

} // namespace mc
