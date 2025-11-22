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
#ifndef MCUTILS_MATH_ANGLES_H_
#define MCUTILS_MATH_ANGLES_H_

#include <string>

#include <units.h>

#include <mcutils/mcutils_api.h>

using namespace units::literals;

namespace mc {

/**
 * \brief Tait-Bryant angles class.
 *
 * This class represents Tait-Bryant angles used to describe the orientation of
 * a rigid body in three-dimensional space. The angles are defined as rotations
 * about the x, y, and z axes, respectively. Z-Y-X or yaw-pitch-roll convention
 * is used.
 *
 * ### References:
 * - [Euler angles - Wikipedia](https://en.wikipedia.org/wiki/Euler_angles)
 */
class MCUTILS_API Angles
{
public:

    /**
     * \brief Normalizes angle within [min,min+2*pi] range.
     * \param val angle to be normalized
     * \param min minimum value
     * \return normalized angle
     */
    static units::angle::radian_t normalize(units::angle::radian_t val,
                                            units::angle::radian_t min = 0_rad);

    /**
     * \brief Constructor.
     * \param phi angle of rotation about x-axis
     * \param tht angle of rotation about y-axis
     * \param psi angle of rotation about z-axis
     */
    explicit Angles(units::angle::radian_t phi = 0_rad,
                    units::angle::radian_t tht = 0_rad,
                    units::angle::radian_t psi = 0_rad);

    /** \return true if all items are valid */
    bool isValid() const;

    /**
     * \brief Normalizes angles.
     *
     * Limits phi to [-pi,pi] theta to [-pi/2,pi/2] and psi to [0,2*pi].
     */
    void normalize();

    /**
     * \brief Sets angles values.
     * \param phi angle of rotation about x-axis
     * \param tht angle of rotation about y-axis
     * \param psi angle of rotation about z-axis
     */
    void set(units::angle::radian_t phi,
             units::angle::radian_t tht,
             units::angle::radian_t psi);

    /** \brief Returns string represtation of the angles. */
    std::string toString() const;

    inline units::angle::radian_t  phi() const { return _phi; }
    inline units::angle::radian_t  tht() const { return _tht; }
    inline units::angle::radian_t  psi() const { return _psi; }
    inline units::angle::radian_t& phi()       { return _phi; }
    inline units::angle::radian_t& tht()       { return _tht; }
    inline units::angle::radian_t& psi()       { return _psi; }

    /** \brief Equality operator. */
    bool operator==(const Angles& angl) const;

    /** \brief Inequality operator. */
    bool operator!=(const Angles& angl) const;

private:

    units::angle::radian_t _phi = 0_rad;    ///< angle of rotation about x-axis
    units::angle::radian_t _tht = 0_rad;    ///< angle of rotation about y-axis
    units::angle::radian_t _psi = 0_rad;    ///< angle of rotation about z-axis
};

} // namespace mc

#endif // MCUTILS_MATH_ANGLES_H_
