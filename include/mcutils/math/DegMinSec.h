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
#ifndef MCUTILS_MATH_DEGMINSEC_H_
#define MCUTILS_MATH_DEGMINSEC_H_

#include <string>

#include <units.h>

#include <mcutils/mcutils_api.h>

using namespace units::literals;

namespace mc {

/**
 * \brief Class representing angle in degrees, minutes and seconds.
 *
 * This class provides methods for converting between degrees, minutes and seconds,
 * as well as for validating the values, converting to a string representation,
 * and comparing angles.
 */
class MCUTILS_API DegMinSec
{
public:

    /**
     * \brief Constructor.
     * \param angle [deg] angle
     */
    explicit DegMinSec(units::angle::degree_t angle = 0_deg);

    /** \return true if all items are valid */
    bool isValid() const;

    inline int    deg() const { return _deg; }
    inline int    min() const { return _min; }
    inline double sec() const { return _sec; }

    /**
     * \brief Returns angle expressed in degrees.
     * \return angle expressed in degrees
     */
    inline units::angle::degree_t getAngle() const { return _angle; }

    /**
     * \brief Sets angle value.
     * \param angle [deg] angle
     */
    void setAngle(units::angle::degree_t angle);

    /** \brief Returns string represtation of the angles. */
    std::string toString() const;

    /** \brief Equality operator. */
    bool operator==(const DegMinSec& dms) const;

    /** \brief Inequality operator. */
    bool operator!=(const DegMinSec& dms) const;

private:

    units::angle::degree_t _angle = 0_deg;  ///< [deg] angle

    int    _deg = 0;        ///< degree part
    int    _min = 0;        ///< minute part (always greater than or equal to 0)
    double _sec = 0.0;      ///< second part (always greater than or equal to 0)
};

} // namespace mc

#endif // MCUTILS_MATH_DEGMINSEC_H_
