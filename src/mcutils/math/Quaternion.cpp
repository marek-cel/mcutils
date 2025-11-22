/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/

#include <mcutils/math/Quaternion.h>

#include <sstream>

#include <mcutils/misc/Check.h>

using namespace units::math;

namespace mc {

Quaternion::Quaternion(double e0, double ex, double ey, double ez)
{
    set(e0, ex, ey, ez);
}

Quaternion::Quaternion(const Angles& angl)
{
    units::angle::radian_t phi_2 = angl.phi() / 2.0;
    units::angle::radian_t tht_2 = angl.tht() / 2.0;
    units::angle::radian_t psi_2 = angl.psi() / 2.0;

    double sin_phi_2 = sin(phi_2);
    double cos_phi_2 = cos(phi_2);

    double sin_tht_2 = sin(tht_2);
    double cos_tht_2 = cos(tht_2);

    double sin_psi_2 = sin(psi_2);
    double cos_psi_2 = cos(psi_2);

    double cos_phi_2_cos_psi_2 = cos_phi_2 * cos_psi_2;
    double cos_phi_2_sin_psi_2 = cos_phi_2 * sin_psi_2;
    double sin_phi_2_sin_psi_2 = sin_phi_2 * sin_psi_2;
    double sin_phi_2_cos_psi_2 = sin_phi_2 * cos_psi_2;

    _e0 = (cos_phi_2_cos_psi_2 * cos_tht_2) + (sin_phi_2_sin_psi_2 * sin_tht_2);
    _ex = (sin_phi_2_cos_psi_2 * cos_tht_2) - (cos_phi_2_sin_psi_2 * sin_tht_2);
    _ey = (cos_phi_2_cos_psi_2 * sin_tht_2) + (sin_phi_2_sin_psi_2 * cos_tht_2);
    _ez = (cos_phi_2_sin_psi_2 * cos_tht_2) - (sin_phi_2_cos_psi_2 * sin_tht_2);

    normalize();
}

Quaternion::Quaternion(units::angle::radian_t angl, const Vector3d& vect)
{
    double len_inv = 1.0 / vect.getLength();

    double cos_angl_2 = cos(0.5 * angl);
    double sin_angl_2 = sin(0.5 * angl);

    _e0 = cos_angl_2;
    _ex = sin_angl_2 * vect.x() * len_inv;
    _ey = sin_angl_2 * vect.y() * len_inv;
    _ez = sin_angl_2 * vect.z() * len_inv;
}

bool Quaternion::isValid() const
{
    return misc::isValid(_e0)
        && misc::isValid(_ex)
        && misc::isValid(_ey)
        && misc::isValid(_ez);
}

void Quaternion::conjugate()
{
    _ex = -_ex;
    _ey = -_ey;
    _ez = -_ez;
}

void Quaternion::invert()
{
    conjugate();
    normalize();
}

void Quaternion::normalize()
{
    double length = getLength();
    if (length > 0.0)
    {
        _e0 = _e0 / length;
        _ex = _ex / length;
        _ey = _ey / length;
        _ez = _ez / length;
    }
}

double Quaternion::getLength2() const
{
    return _e0*_e0 + _ex*_ex + _ey*_ey + _ez*_ez;
}

double Quaternion::getLength() const
{
    return sqrt(getLength2());
}

Angles Quaternion::getAngles() const
{
    Angles result;

    double sin_tht_2 = _e0*_ey - _ex*_ez;
    if(sin_tht_2 >= 0.5)
    {
        result.phi() =  2.0 * units::angle::radian_t(asin(_ex / cos(M_PI_4)));
        result.tht() =  0.5_rad * M_PI;
        result.psi() =  0.0_rad;
    }
    else if (sin_tht_2 <= -0.5)
    {
        result.phi() =  2.0 * units::angle::radian_t(asin(_ex / cos(M_PI_4)));
        result.tht() = -0.5_rad * M_PI;
        result.psi() =  0.0_rad;
    }
    else
    {
        result.phi() = units::angle::radian_t(atan2(2.0*(_e0*_ex + _ey*_ez), 1.0 - 2.0*(_ex*_ex + _ey*_ey)));
        result.tht() = units::angle::radian_t(asin(2.0*sin_tht_2));
        result.psi() = units::angle::radian_t(atan2(2.0*(_e0*_ez + _ex*_ey), 1.0 - 2.0*(_ey*_ey + _ez*_ez)));
    }
    result.normalize();

    return result;
}

Quaternion Quaternion::getConjugated() const
{
    Quaternion result(*this);
    result.conjugate();
    return result;
}

Quaternion Quaternion::getDerivative(const Vector3_rad_per_s& omega, double lambda) const
{
    Quaternion result;

    // Pamadi - Performance Stability Dynamics and Control of Airplanes, 2004, p.348
    // Sibilski - Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.34
    // Roziecki - Bifurkacyjna Analiza Dynamiki Lotu Samolotu z Wektorowaniem Ciagu, 2006, p.24
    // | e0_dot |          |  0  P  Q  R | | e0 |   | -0.5 * ( ez*R + ey*Q + ex*P ) |
    // | ex_dot |          | -P  0 -R  Q | | ex |   | -0.5 * ( ez*Q - ey*R - e0*P ) |
    // | ey_dot | = -0.5 * | -Q  R  0 -P | | ey | = | -0.5 * ( ex*R - e0*Q - ez*P ) |
    // | ez_dot |          | -R -Q  P  0 | | ez |   | -0.5 * ( ey*P - e0*R - ex*Q ) |

    result._e0 = -0.5 * (_ez * omega.r()()
                       + _ey * omega.q()()
                       + _ex * omega.p()());

    result._ex = -0.5 * (_ez * omega.q()()
                       - _ey * omega.r()()
                       - _e0 * omega.p()());

    result._ey = -0.5 * (_ex * omega.r()()
                       - _e0 * omega.q()()
                       - _ez * omega.p()());

    result._ez = -0.5 * (_ey * omega.p()()
                       - _e0 * omega.r()()
                       - _ex * omega.q()());

    // Pamadi - Performance Stability Dynamics and Control of Airplanes, 2004, p.348
    // Sibilski - Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.34
    // Roziecki - Bifurkacyjna Analiza Dynamiki Lotu Samolotu z Wektorowaniem Ciagu, 2006, p.24
    if (lambda > 0.0)
    {
        double epsilon = 1.0 - getLength2();
        double lambda_epsilon = lambda * epsilon;

        result._e0 += lambda_epsilon * _e0;
        result._ex += lambda_epsilon * _ex;
        result._ey += lambda_epsilon * _ey;
        result._ez += lambda_epsilon * _ez;
    }

    return result;
}

Quaternion Quaternion::getInverted() const
{
    Quaternion result(*this);
    result.invert();
    return result;
}

Quaternion Quaternion::getNormalized() const
{
    Quaternion result(*this);
    result.normalize();
    return result;
}

void Quaternion::set(double e0, double ex, double ey, double ez)
{
    _e0 = e0;
    _ex = ex;
    _ey = ey;
    _ez = ez;
}

std::string Quaternion::toString() const
{
    std::stringstream ss;
    ss << _e0 <<  "\t" << _ex <<  "\t" << _ey <<  "\t" << _ez;
    return ss.str();
}

Quaternion Quaternion::operator+(const Quaternion& quat) const
{
    Quaternion result;

    result._e0 = _e0 + quat._e0;
    result._ex = _ex + quat._ex;
    result._ey = _ey + quat._ey;
    result._ez = _ez + quat._ez;

    return result;
}

Quaternion Quaternion::operator-() const
{
    Quaternion result;

    result._e0 = -_e0;
    result._ex = -_ex;
    result._ey = -_ey;
    result._ez = -_ez;

    return result;
}

Quaternion Quaternion::operator-(const Quaternion& quat) const
{
    Quaternion result;

    result._e0 = _e0 - quat._e0;
    result._ex = _ex - quat._ex;
    result._ey = _ey - quat._ey;
    result._ez = _ez - quat._ez;

    return result;
}

Quaternion Quaternion::operator*(double val) const
{
    Quaternion result;

    result._e0 = _e0 * val;
    result._ex = _ex * val;
    result._ey = _ey * val;
    result._ez = _ez * val;

    return result;
}

Quaternion Quaternion::operator*(const Quaternion& quat) const
{
    Quaternion result;

    result._e0 = _e0 * quat._e0
               - _ex * quat._ex
               - _ey * quat._ey
               - _ez * quat._ez;

    result._ex = _e0 * quat._ex
               + _ex * quat._e0
               + _ey * quat._ez
               - _ez * quat._ey;

    result._ey = _e0 * quat._ey
               - _ex * quat._ez
               + _ey * quat._e0
               + _ez * quat._ex;

    result._ez = _e0 * quat._ez
               + _ex * quat._ey
               - _ey * quat._ex
               + _ez * quat._e0;

    return result;
}

Quaternion Quaternion::operator/(double val) const
{
    Quaternion result;

    result._e0 = _e0 / val;
    result._ex = _ex / val;
    result._ey = _ey / val;
    result._ez = _ez / val;

    return result;
}

Quaternion& Quaternion::operator+=(const Quaternion& quat)
{
    _e0 += quat._e0;
    _ex += quat._ex;
    _ey += quat._ey;
    _ez += quat._ez;

    return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& quat)
{
    _e0 -= quat._e0;
    _ex -= quat._ex;
    _ey -= quat._ey;
    _ez -= quat._ez;

    return *this;
}

Quaternion& Quaternion::operator*=(double val)
{
    _e0 *= val;
    _ex *= val;
    _ey *= val;
    _ez *= val;

    return *this;
}

Quaternion& Quaternion::operator/=(double val)
{
    _e0 /= val;
    _ex /= val;
    _ey /= val;
    _ez /= val;

    return *this;
}

bool Quaternion::operator==(const Quaternion& quat) const
{
    return (_e0 == quat._e0)
        && (_ex == quat._ex)
        && (_ey == quat._ey)
        && (_ez == quat._ez);
}

bool Quaternion::operator!=(const Quaternion& quat) const
{
    return !(*this == quat);
}

} // namespace mc
