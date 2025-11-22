/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
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
    return misc::isValid(_angle)
        && misc::isValid(_deg)
        && misc::isValid(_min)
        && misc::isValid(_sec);
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
