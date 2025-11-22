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
#ifndef MCUTILS_MATH_QUATERNION_H_
#define MCUTILS_MATH_QUATERNION_H_

#include <string>

#include <units.h>

#include <mcutils/mcutils_api.h>

#include <mcutils/math/Angles.h>
#include <mcutils/math/Vector.h>

namespace mc {

/**
 * \brief Quaternion class.
 *
 * This class represents a quaternion, which is a mathematical object used to
 * describe rotations in three-dimensional space.
 *
 * Please notice that rotations are considered to be passive (alias) rotations.
 *
 * ### References:
 * - Allerton D.: Principles of Flight Simulation, 2009, p.122
 * - Zipfel P.: Modeling and Simulation of Aerospace Vehicle Dynamics, 2007, p.372
 * - Pamadi B.: Performance Stability Dynamics and Control of Airplanes, 2004, p.346
 * - Sibilski K.: Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.33. [in Polish]
 * - Matulewski J., et. al.: Grafika fizyka metody numeryczne, 2010, p.519. [in Polish]
 * - DeLoura M.: Game Programming Gems Vol. 1, 2000, p.213
 * - Roziecki R.: Bifurkacyjna Analiza Dynamiki Lotu Samolotu z Wektorowaniem Ciagu, 2006, p.22 [in Polish]
 * - [Quaternion - Wikipedia](https://en.wikipedia.org/wiki/Quaternion)
 * - [Quaternions and spatial rotation - Wikipedia](https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation)
 * - [Conversion between quaternions and Euler angles - Wikipedia](https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles)
 * - [Active and passive transformation - Wikipedia](https://en.wikipedia.org/wiki/Active_and_passive_transformation)
 */
class MCUTILS_API Quaternion
{
public:

    /** \brief Constructor. */
    explicit Quaternion(double e0 = 1.0, double ex = 0.0,
                        double ey = 0.0, double ez = 0.0);

    /** \brief Constructor. */
    explicit Quaternion(const Angles& angl);

    /**
     * \brief Constructor.
     * \param angl [rad] angle of rotation
     * \param vect [-] vector of rotation axis
     */
    Quaternion(units::angle::radian_t angl, const Vector3d& vect);

    /** \return TRUE if all items are valid */
    bool isValid() const;

    /** \brief Conjugates quaternion. */
    void conjugate();

    /** \brief Inverts quaternion. */
    void invert();

    /** \brief Normalizes quaternion. */
    void normalize();

    /** \return vector length squared */
    double getLength2() const;

    /** \return vector length */
    double getLength() const;

    /** \brief Returns Bryant angles. */
    Angles getAngles() const;

    /** \brief Returns conjugated quaternion. */
    Quaternion getConjugated() const;

    /**
     * \brief Returns quaternion derivative due to given angular velocity.
     * \param omega [rad/s] angular velocity vector
     * \param lambda free parameter (usually set to a small multiple of the integration time step)
     * \return quaternion derivative
     */
    Quaternion getDerivative(const Vector3_rad_per_s& omega, double lambda = 0.0) const;

    /** \brief Returns inverted quaternion. */
    Quaternion getInverted() const;

    /** \brief Returns normalized quaternion. */
    Quaternion getNormalized() const;

    /** \brief Sets quaternion values. */
    void set(double e0, double ex, double ey, double ez);

    /** \brief Returns string representation of the quaternion. */
    std::string toString() const;

    inline double  e0() const { return _e0; }
    inline double  ex() const { return _ex; }
    inline double  ey() const { return _ey; }
    inline double  ez() const { return _ez; }
    inline double& e0()       { return _e0; }
    inline double& ex()       { return _ex; }
    inline double& ey()       { return _ey; }
    inline double& ez()       { return _ez; }

    /** \brief Addition operator. */
    Quaternion operator+(const Quaternion& quat) const;

    /** \brief Negation operator. */
    Quaternion operator-() const;

    /** \brief Subtraction operator. */
    Quaternion operator-(const Quaternion& quat) const;

    /** \brief Multiplication operator (by number). */
    Quaternion operator*(double val) const;

    /** \brief Multiplication operator (by quaternion). */
    Quaternion operator*(const Quaternion& quat) const;

    /** \brief Division operator (by number). */
    Quaternion operator/(double val) const;

    /** \brief Unary addition operator. */
    Quaternion& operator+=(const Quaternion& quat);

    /** \brief Unary subtraction operator. */
    Quaternion& operator-=(const Quaternion& quat);

    /** \brief Unary multiplication operator (by number). */
    Quaternion& operator*=(double val);

    /** \brief Unary division operator (by number). */
    Quaternion& operator/=(double val);

    /** \brief Equality operator. */
    bool operator==(const Quaternion& quat) const;

    /** \brief Inequality operator. */
    bool operator!=(const Quaternion& quat) const;

private:

    double _e0 = 1.0;   ///< quaternion e0 (w) component
    double _ex = 0.0;   ///< quaternion ex (x) component
    double _ey = 0.0;   ///< quaternion ey (y) component
    double _ez = 0.0;   ///< quaternion ez (z) component
};

/** \brief Multiplication operator (by number). */
inline Quaternion operator*(double val, const Quaternion& quat)
{
    return quat * val;
}

} // namespace mc

#endif // MCUTILS_MATH_QUATERNION_H_
