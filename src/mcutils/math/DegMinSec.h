/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
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
