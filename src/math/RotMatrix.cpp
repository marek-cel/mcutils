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

#include <mcutils/math/RotMatrix.h>

using namespace units::math;

namespace mc {

RotMatrix RotMatrix::getIdentityMatrix()
{
    return RotMatrix(1.0, 0.0, 0.0,
                     0.0, 1.0, 0.0,
                     0.0, 0.0, 1.0);
}

RotMatrix::RotMatrix(double xx, double xy, double xz,
                     double yx, double yy, double yz,
                     double zx, double zy, double zz)
    : Matrix3x3<double>(xx, xy, xz, yx, yy, yz, zx, zy, zz)
{}

RotMatrix::RotMatrix(const Angles& angl)
{
    double sin_phi = sin(angl.phi());
    double cos_phi = cos(angl.phi());

    double sin_tht = sin(angl.tht());
    double cos_tht = cos(angl.tht());

    double sin_psi = sin(angl.psi());
    double cos_psi = cos(angl.psi());

    double sin_phi_sin_tht = sin_phi * sin_tht;
    double cos_phi_sin_tht = cos_phi * sin_tht;

    xx() =  cos_tht * cos_psi;
    xy() =  cos_tht * sin_psi;
    xz() = -sin_tht;

    yx() = -(cos_phi * sin_psi) + (sin_phi_sin_tht * cos_psi);
    yy() =  (cos_phi * cos_psi) + (sin_phi_sin_tht * sin_psi);
    yz() =  (sin_phi * cos_tht);

    zx() =  (sin_phi * sin_psi) + (cos_phi_sin_tht * cos_psi);
    zy() = -(sin_phi * cos_psi) + (cos_phi_sin_tht * sin_psi);
    zz() =  (cos_phi * cos_tht);
}

RotMatrix::RotMatrix(const Quaternion& quat)
{
    double e0 = quat.e0();
    double ex = quat.ex();
    double ey = quat.ey();
    double ez = quat.ez();

    double e02 = e0*e0;
    double ex2 = ex*ex;
    double ey2 = ey*ey;
    double ez2 = ez*ez;

    xx() = e02 + ex2 - ey2 - ez2;
    xy() = 2.0 * (e0*ez + ex*ey);
    xz() = 2.0 * (ex*ez - e0*ey);

    yx() = 2.0 * (ex*ey - e0*ez);
    yy() = e02 - ex2 + ey2 - ez2;
    yz() = 2.0 * (e0*ex + ey*ez);

    zx() = 2.0 * (e0*ey + ex*ez);
    zy() = 2.0 * (ey*ez - e0*ex);
    zz() = e02 - ex2 - ey2 + ez2;
}

Angles RotMatrix::getAngles() const
{
    Angles result;

    double sin_tht = -xz();
    double cos_tht = sqrt(1.0 - std::min(1.0, sin_tht*sin_tht));

    result.tht() = units::angle::radian_t(atan2(sin_tht, cos_tht));

    if (cos_tht > 0.0)
    {
        result.phi() = units::angle::radian_t(atan2(yz(), zz()));
        result.psi() = units::angle::radian_t(atan2(xy(), xx()));
    }
    else
    {
        result.phi() = units::angle::radian_t(atan2(yx(), zx()));
        result.psi() = 0.0_rad;
    }

    result.normalize();

    return result;
}

/** \brief Returns quaternion of rotation matrix. */
Quaternion RotMatrix::getQuaternion() const
{
    Quaternion result;

    // traces
    double tr[4];

    tr[0] = 1.0 + xx() + yy() + zz();
    tr[1] = 1.0 + xx() - yy() - zz();
    tr[2] = 1.0 - xx() + yy() - zz();
    tr[3] = 1.0 - xx() - yy() + zz();

    int index = 0;
    for (int i = 1; i < 4; ++i) index = (tr[i] > tr[index]) ? i : index;

    if (index == 0)
    {
        result.e0() = tr[0];
        result.ex() = yz() - zy();
        result.ey() = zx() - xz();
        result.ez() = xy() - yx();
    }
    else if (index == 1)
    {
        result.e0() = yz() - zy();
        result.ex() = tr[1];
        result.ey() = xy() + yx();
        result.ez() = zx() + xz();
    }
    else if (index == 2)
    {
        result.e0() = zx() - xz();
        result.ex() = xy() + yx();
        result.ey() = tr[2];
        result.ez() = yz() + zy();
    }
    else
    {
        result.e0() = xy() - yx();
        result.ex() = zx() + xz();
        result.ey() = yz() + zy();
        result.ez() = tr[3];
    }

    result *= sqrt(0.25 / tr[index]);

    result.normalize();

    return result;
}

RotMatrix RotMatrix::getTransposed() const
{
    RotMatrix result(*this);
    result.transpose();
    return result;
}

RotMatrix RotMatrix::operator+(const RotMatrix& mat) const
{
    RotMatrix result;
    addMatrices(*this, mat, &result);
    return result;
}

RotMatrix RotMatrix::operator-() const
{
    RotMatrix result(*this);
    result.negate();
    return result;
}

RotMatrix RotMatrix::operator-(const RotMatrix& mat) const
{
    RotMatrix result;
    subtractMatrices(*this, mat, &result);
    return result;
}

RotMatrix RotMatrix::operator*(double val) const
{
    RotMatrix result;
    multiplyMatrixByScalar(*this, val, &result);
    return result;
}

RotMatrix RotMatrix::operator*(const RotMatrix& mat) const
{
    RotMatrix result;
    multiplyMatrixByMatrix(*this, mat, &result);
    return result;
}

RotMatrix RotMatrix::operator/(double val) const
{
    RotMatrix result;
    multiplyMatrixByScalar(*this, 1.0 / val, &result);
    return result;
}

RotMatrix& RotMatrix::operator+=(const RotMatrix& mat)
{
    addMatrices(*this, mat, this);
    return *this;
}

RotMatrix& RotMatrix::operator-=(const RotMatrix& mat)
{
    subtractMatrices(*this, mat, this);
    return *this;
}

RotMatrix& RotMatrix::operator*=(double val)
{
    *this = (*this) * val;
    return *this;
}

RotMatrix& RotMatrix::operator/=(double val)
{
    *this = (*this) / val;
    return *this;
}

} // namespace mc
