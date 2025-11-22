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

#include <mcutils/geo/ECEF.h>

#include <mcutils/math/MathUtils.h>

using namespace units::math;


namespace mc {

//0.0,  1.0,  0.0
//1.0,  0.0,  0.0
//0.0,  0.0, -1.0
const RotMatrix ECEF::_enu2ned( 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0 );
const RotMatrix ECEF::_ned2enu( 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0 );

ECEF::ECEF(const Ellipsoid& ellipsoid)
    : _ellipsoid(ellipsoid)
{
    _pos_geo.lat = 0.0_rad;
    _pos_geo.lon = 0.0_rad;
    _pos_geo.alt = 0.0_m;

    _pos_cart.x() = _ellipsoid.a();
    _pos_cart.y() = 0_m;
    _pos_cart.z() = 0_m;

    updateMatrices();
}

void ECEF::convertGeo2Cart(units::angle::radian_t lat,
                           units::angle::radian_t lon,
                           units::length::meter_t alt,
                           units::length::meter_t* x,
                           units::length::meter_t* y,
                           units::length::meter_t* z) const
{
    double sinLat = sin(lat);
    double cosLat = cos(lat);
    double sinLon = sin(lon);
    double cosLon = cos(lon);

    units::length::meter_t n = _ellipsoid.a() / sqrt(1.0 - _ellipsoid.e2() * sinLat*sinLat);

    *x = (n + alt) * cosLat * cosLon;
    *y = (n + alt) * cosLat * sinLon;
    *z = (n * (_ellipsoid.b2() / _ellipsoid.a2()) + alt) * sinLat;
}

Vector3_m ECEF::convertGeo2Cart(units::angle::radian_t lat,
                                units::angle::radian_t lon,
                                units::length::meter_t alt) const
{
    Vector3_m pos_cart;
    convertGeo2Cart(lat, lon, alt, &pos_cart.x(), &pos_cart.y(), &pos_cart.z());
    return pos_cart;
}

void ECEF::convertCart2Geo(units::length::meter_t x,
                           units::length::meter_t y,
                           units::length::meter_t z,
                           units::angle::radian_t* lat,
                           units::angle::radian_t* lon,
                           units::length::meter_t* alt) const
{
    // units not used due to performance reasons
    double z2 = math::pow<2>(z)();
    double r  = sqrt(math::pow<2>(x)() + math::pow<2>(y)());
    double r2 = r*r;
    double e2 = _ellipsoid.a2()() - _ellipsoid.b2()();
    double f  = 54.0 * _ellipsoid.b2()() * z2;
    double g  = r2 + (1.0 - _ellipsoid.e2())*z2 - _ellipsoid.e2()*e2;
    double c  = _ellipsoid.e2()*_ellipsoid.e2() * f * r2 / math::pow<3>(g);
    double s  = pow(1.0 + c + sqrt(c*c + 2.0*c), 1.0/3.0);
    double p0 = s + 1.0/s + 1.0;
    double p  = f / (3.0 * p0*p0 * g*g);
    double q  = sqrt(1.0 + 2.0*(_ellipsoid.e2()*_ellipsoid.e2())*p);
    double r0 = -(p * _ellipsoid.e2() * r)/(1.0 + q)
                + sqrt(
                    0.5*_ellipsoid.a2()()*(1.0 + 1.0/q)
                    - p*(1.0 - _ellipsoid.e2())*z2/(q + q*q) - 0.5*p*r2
                );
    double uv = r - _ellipsoid.e2()*r0;
    double u  = sqrt(uv*uv + z2);
    double v  = sqrt(uv*uv + (1.0 - _ellipsoid.e2())*z2);
    double z0 = _ellipsoid.b2()() * z() / (_ellipsoid.a()() * v);

    *alt = units::length::meter_t(u * (1.0 - _ellipsoid.b2()() / (_ellipsoid.a()() * v)));
    *lat = units::angle::radian_t(atan((z() + _ellipsoid.ep2()*z0)/r));
    *lon = units::angle::radian_t(atan2(y(), x()));
}

void ECEF::convertCart2GeoFast(units::length::meter_t x,
                               units::length::meter_t y,
                               units::length::meter_t z,
                               units::angle::radian_t* lat,
                               units::angle::radian_t* lon,
                               units::length::meter_t* alt) const
{
    units::length::meter_t p   = sqrt(x*x + y*y);
    units::angle::radian_t tht = atan2(z*_ellipsoid.a(), p*_ellipsoid.b());
    double ed2 = (_ellipsoid.a2() - _ellipsoid.b2()) / _ellipsoid.b2();

    double sinTht = sin(tht());
    double cosTht = cos(tht());

    *lat = atan(
        (z + _ellipsoid.b()*ed2*math::pow<3>(sinTht))
        /
        (p - _ellipsoid.e2()*_ellipsoid.a()*math::pow<3>(cosTht))
    );
    *lon = atan2(y, x);

    double sinLat = sin((*lat)());
    units::length::meter_t n = _ellipsoid.a() / sqrt(1.0 - _ellipsoid.e2()*math::pow<2>(sinLat));

    *alt = p / cos((*lat)()) - n;
}

Geo ECEF::convertCart2Geo(units::length::meter_t x,
                          units::length::meter_t y,
                          units::length::meter_t z) const
{
    Geo pos_geo;
    convertCart2Geo(x, y, z, &pos_geo.lat, &pos_geo.lon, &pos_geo.alt);
    return pos_geo;
}

Geo ECEF::convertCart2GeoFast(units::length::meter_t x,
                              units::length::meter_t y,
                              units::length::meter_t z) const
{
    Geo pos_geo;
    convertCart2GeoFast(x, y, z, &pos_geo.lat, &pos_geo.lon, &pos_geo.alt);
    return pos_geo;
}

Geo ECEF::getGeoOffset(units::angle::radian_t heading,
                       units::length::meter_t offset_x,
                       units::length::meter_t offset_y) const
{
    RotMatrix ned2bas(Angles(0_rad, 0_rad, heading));
    RotMatrix bas2ned = ned2bas.getTransposed();

    Vector3_m r_bas(offset_x, offset_y, 0_m);
    Vector3_m r_ned = bas2ned * r_bas;

    Vector3_m pos_cart = _pos_cart + _ned2ecef * r_ned;

    return convertCart2Geo(pos_cart);
}

void ECEF::setPosition(const Geo& pos_geo)
{
    _pos_geo = pos_geo;
    _pos_cart = convertGeo2Cart(_pos_geo);
    updateMatrices();
}

void ECEF::setPosition(const Vector3_m& pos_cart)
{
    _pos_cart = pos_cart;
    _pos_geo = convertCart2Geo(_pos_cart);
    updateMatrices();
}

void ECEF::updateMatrices()
{
    double cosLat = cos(_pos_geo.lat);
    double cosLon = cos(_pos_geo.lon);
    double sinLat = sin(_pos_geo.lat);
    double sinLon = sin(_pos_geo.lon);

    // NED to ECEF
    _ned2ecef(0,0) = -cosLon*sinLat;
    _ned2ecef(0,1) = -sinLon;
    _ned2ecef(0,2) = -cosLon*cosLat;

    _ned2ecef(1,0) = -sinLon*sinLat;
    _ned2ecef(1,1) =  cosLon;
    _ned2ecef(1,2) = -sinLon*cosLat;

    _ned2ecef(2,0) =  cosLat;
    _ned2ecef(2,1) =  0.0;
    _ned2ecef(2,2) = -sinLat;

    _enu2ecef = _ned2ecef * _enu2ned;

    // ECEF to NED
    _ecef2ned(0,0) = -cosLon * sinLat;
    _ecef2ned(0,1) = -sinLon * sinLat;
    _ecef2ned(0,2) =  cosLat;

    _ecef2ned(1,0) = -sinLon;
    _ecef2ned(1,1) =  cosLon;
    _ecef2ned(1,2) =  0.0;

    _ecef2ned(2,0) = -cosLon * cosLat;
    _ecef2ned(2,1) = -sinLon * cosLat;
    _ecef2ned(2,2) = -sinLat;

    _ecef2enu = _ned2enu * _ecef2ned;
}

} // namespace mc
