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
#ifndef MCUTILS_GEO_ECEF_H_
#define MCUTILS_GEO_ECEF_H_

#include <utility>

#include <units.h>

#include <mcutils/mcutils_api.h>

#include <mcutils/geo/Ellipsoid.h>
#include <mcutils/geo/Geo.h>

#include <mcutils/math/Angles.h>
#include <mcutils/math/Quaternion.h>
#include <mcutils/math/RotMatrix.h>
#include <mcutils/math/Vector.h>

namespace mc {

/**
 * \brief Earth-centered, Earth-fixed (ECEF) coordinate system class.
 *
 * This class is used to store and calculate location expressed in
 * Earth-centered, Earth-fixed coordinate system. It also provides functions
 * to calculate rotation matricies between ECEF and local North-East-Down (NED)
 * as well as between ECEF and local East-North-Up (ENU) axis systems.<br/>
 *
 * The z-axis coincident with the spin axis and positive North, x-axis laying
 * an equatorial plane and positive through 0 longitude and 0 latitude,
 * and y-axis completing right-handed system.<br/>
 *
 * ### References:
 * - Burtch R.: A Comparison of Methods Used in Rectangular to Geodetic Coordinate Transformations, 2006
 * - Bowring B.: Transformation from spatial to geocentric coordinates, 1976
 * - Zhu J.: Conversion of Earth-centered Earth-fixed coordinates to geodetic coordinates, 1994
 */
class MCUTILS_API ECEF
{
public:

    static const RotMatrix _enu2ned;    ///< matrix of rotation from ENU to NED
    static const RotMatrix _ned2enu;    ///< matrix of rotation from NED to ENU

    /**
     * \brief Constructor.
     * \param ellipsoid datum ellipsoid
     */
    explicit ECEF(const Ellipsoid& ellipsoid);

    /**
     * \brief Converts geodetic coordinates into cartesian coordinates.
     * \param lat [rad] geodetic latitude
     * \param lon [rad] geodetic longitude
     * \param alt [m] altitude above mean sea level
     * \param x [m] resulting cartesian x-coordinate pointer
     * \param y [m] resulting cartesian y-coordinate pointer
     * \param z [m] resulting cartesian z-coordinate pointer
     */
    void convertGeo2Cart(units::angle::radian_t lat,
                         units::angle::radian_t lon,
                         units::length::meter_t alt,
                         units::length::meter_t* x,
                         units::length::meter_t* y,
                         units::length::meter_t* z) const;

    /**
     * \brief Converts geodetic coordinates into cartesian coordinates.
     * \param lat [rad] geodetic latitude
     * \param lon [rad] geodetic longitude
     * \param alt [m] altitude above mean sea level
     * \return [m] resulting cartesian coordinates vector
     */
    Vector3_m convertGeo2Cart(units::angle::radian_t lat,
                              units::angle::radian_t lon,
                              units::length::meter_t alt) const;

    /**
     * \brief Converts geodetic coordinates into cartesian coordinates.
     * \param pos_geo [m] geodetic coordinates
     * \return [m] resulting cartesian coordinates vector
     */
    inline Vector3_m convertGeo2Cart(const Geo& pos_geo) const
    {
        return convertGeo2Cart(pos_geo.lat, pos_geo.lon, pos_geo.alt);
    }

    /**
     * \brief Converts cartesian coordinates into geodetic coordinates.
     * \param x [m] cartesian x-coordinate
     * \param y [m] cartesian y-coordinate
     * \param z [m] cartesian z-coordinate
     * \param lat [rad] resulting geodetic latitude pointer
     * \param lon [rad] resulting geodetic longitude pointer
     * \param alt [m] resulting altitude above mean sea level pointer
     */
    void convertCart2Geo(units::length::meter_t x,
                         units::length::meter_t y,
                         units::length::meter_t z,
                         units::angle::radian_t* lat,
                         units::angle::radian_t* lon,
                         units::length::meter_t* alt) const;

    /**
     * \brief Converts cartesian coordinates into geodetic coordinates.
     *
     * This method is fast but less precise, it provides 1cm accuracy for height less than 1000km
     *
     * \param x [m] cartesian x-coordinate
     * \param y [m] cartesian y-coordinate
     * \param z [m] cartesian z-coordinate
     * \param lat [rad] resulting geodetic latitude pointer
     * \param lon [rad] resulting geodetic longitude pointer
     * \param alt [m] resulting altitude above mean sea level pointer
     */
    void convertCart2GeoFast(units::length::meter_t x,
                             units::length::meter_t y,
                             units::length::meter_t z,
                             units::angle::radian_t* lat,
                             units::angle::radian_t* lon,
                             units::length::meter_t* alt) const;

    /**
     * \brief Converts cartesian coordinates into geodetic coordinates.
     * \param x [m] cartesian x-coordinate
     * \param y [m] cartesian y-coordinate
     * \param z [m] cartesian z-coordinate
     * \return resulting geodetic coordinates
     */
    Geo convertCart2Geo(units::length::meter_t x,
                        units::length::meter_t y,
                        units::length::meter_t z) const;

    /**
     * \brief Converts cartesian coordinates into geodetic coordinates.
     *
     * This method is fast but less precise, it provides 1cm accuracy for height less than 1000km
     *
     * \param x [m] cartesian x-coordinate
     * \param y [m] cartesian y-coordinate
     * \param z [m] cartesian z-coordinate
     * \return resulting geodetic coordinates
     */
    Geo convertCart2GeoFast(units::length::meter_t x,
                            units::length::meter_t y,
                            units::length::meter_t z) const;

    /**
     * \brief Converts cartesian coordinates into geodetic coordinates.
     * \param pos_cart [m] cartesian coordinates vector
     * \return resulting geodetic coordinates
     */
    inline Geo convertCart2Geo(const Vector3_m& pos_cart) const
    {
        return convertCart2Geo(pos_cart.x(), pos_cart.y(), pos_cart.z());
    }

    /**
     * \brief Converts cartesian coordinates into geodetic coordinates.
     *
     * This method is fast but less precise, it provides 1cm accuracy for height less than 1000km
     *
     * \param pos_cart [m] cartesian coordinates vector
     * \return resulting geodetic coordinates
     */
    inline Geo convertCart2GeoFast(const Vector3_m& pos_cart) const
    {
        return convertCart2GeoFast(pos_cart.x(), pos_cart.y(), pos_cart.z());
    }

    /**
     * \brief Calculates coordinates moved by the given offset.
     * \param heading [rad] heading
     * \param offset_x [m] longitudinal offset
     * \param offset_y [m] lateral offset
     * \return resulting geodetic coordinates
     */
    Geo getGeoOffset(units::angle::radian_t heading,
                     units::length::meter_t offset_x,
                     units::length::meter_t offset_y) const;

    /**
     * \brief Converts attitude angles expressed in ENU.
     * \param angles_ecef attitude angles expressed in ECEF
     * \return attitude angles expressed in ENU
     */
    inline Angles convertAttitudeECEF2ENU(const Angles& angles_ecef) const
    {
        return convertAttitudeECEF2ENU(Quaternion(angles_ecef)).getAngles();
    }

    /**
     * \brief Converts attitude angles expressed in NED.
     * \param angles_ecef attitude angles expressed in ECEF
     * \return attitude angles expressed in NED
     */
    inline Angles convertAttitudeECEF2NED(const Angles& angles_ecef) const
    {
        return convertAttitudeECEF2NED(Quaternion(angles_ecef)).getAngles();
    }

    /**
     * \brief Converts attitude angles expressed in ECEF.
     * \param angles_enu attitude angles expressed in ENU
     * \return attitude angles expressed in ECEF
     */
    inline Angles convertAttitudeENU2ECEF(const Angles& angles_enu) const
    {
        return convertAttitudeENU2ECEF(Quaternion(angles_enu)).getAngles();
    }

    /**
     * \brief Converts attitude angles expressed in ECEF.
     * \param angles_ned attitude angles expressed in NED
     * \return attitude angles expressed in ECEF
     */
    inline Angles convertAttitudeNED2ECEF(const Angles& angles_ned) const
    {
        return convertAttitudeNED2ECEF(Quaternion(angles_ned)).getAngles();
    }

    /**
     * \brief Converts attitude quaternion expressed in ENU.
     * \param att_ecef attitude quaternion expressed in ECEF
     * \return attitude quaternion expressed in ENU
     */
    inline Quaternion convertAttitudeECEF2ENU(const Quaternion& att_ecef) const
    {
        return _enu2ecef.getQuaternion() * att_ecef;
    }

    /**
     * \brief Converts attitude quaternion expressed in NED.
     * \param att_ecef attitude quaternion expressed in ECEF
     * \return attitude quaternion expressed in NED
     */
    inline Quaternion convertAttitudeECEF2NED(const Quaternion& att_ecef) const
    {
        return _ned2ecef.getQuaternion() * att_ecef;
    }

    /**
     * \brief Converts attitude quaternion expressed in ECEF.
     * \param att_enu attitude quaternion expressed in NED
     * \return attitude quaternion expressed in ECEF
     */
    inline Quaternion convertAttitudeENU2ECEF(const Quaternion& att_enu) const
    {
        return _ecef2enu.getQuaternion() * att_enu;
    }

    /**
     * \brief Converts attitude quaternion expressed in ECEF.
     * \param att_ned attitude quaternion expressed in NED
     * \return attitude quaternion expressed in ECEF
     */
    inline Quaternion convertAttitudeNED2ECEF(const Quaternion& att_ned) const
    {
        return _ecef2ned.getQuaternion() * att_ned;
    }

    /**
     * \brief Sets position from geodetic coordinates
     * \param pos_geo position expressed in geodetic coordinates
     */
    void setPosition(const Geo& pos_geo);

    /**
     * \brief Sets position from cartesian coordinates
     * \param pos_geo position expressed in geodetic coordinates
     */
    void setPosition(const Vector3_m& pos_cart);

    inline const Geo& pos_geo() const { return _pos_geo; }

    inline const Vector3_m& pos_cart() const { return _pos_cart; }

    inline const RotMatrix& enu2ned() const { return _enu2ned; }
    inline const RotMatrix& ned2enu() const { return _ned2enu; }

    inline const RotMatrix& enu2ecef() const { return _enu2ecef; }
    inline const RotMatrix& ned2ecef() const { return _ned2ecef; }
    inline const RotMatrix& ecef2enu() const { return _ecef2enu; }
    inline const RotMatrix& ecef2ned() const { return _ecef2ned; }

protected:

    Ellipsoid _ellipsoid;       ///< datum ellipsoid

    Geo       _pos_geo;         ///< geodetic coordinates (latitude, longitude, altitude)
    Vector3_m _pos_cart;        ///< [m] cartesian coordinates vector (x, y, z)

    RotMatrix _enu2ecef;        ///< rotation matrix from ENU to ECEF
    RotMatrix _ned2ecef;        ///< rotation matrix from NED to ECEF
    RotMatrix _ecef2enu;        ///< rotation matrix from ECEF to ENU
    RotMatrix _ecef2ned;        ///< rotation matrix from ECEF to NED

    /**
     * \brief Updates rotation matrices due to position.
     * This function updates rotation matrices due to current ECEF coordinates.
     */
    void updateMatrices();
};

} // namespace mc

#endif // MCUTILS_GEO_ECEF_H_
