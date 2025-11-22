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
#ifndef MCUTILS_GEO_ELLIPSOID_H_
#define MCUTILS_GEO_ELLIPSOID_H_

#include <units.h>

#include <mcutils/mcutils_api.h>

using namespace units::literals;

namespace mc {

/**
 * \brief Ellipsoid parameters class.
 *
 * ### References:
 * - [Ellipsoid - Wikipedia](https://en.wikipedia.org/wiki/Ellipsoid)
 */
class MCUTILS_API Ellipsoid
{
public:

    /**
     * \brief Constructor.
     * \param a [m] equatorial radius
     * \param f [-] ellipsoid flattening
     */
    Ellipsoid(units::length::meter_t a, double f);

    inline units::length::meter_t      a   () const { return _a;   }
    inline double                      f   () const { return _f;   }
    inline units::length::meter_t      b   () const { return _b;   }
    inline units::length::meter_t      r1  () const { return _r1;  }
    inline units::area::square_meter_t a2  () const { return _a2;  }
    inline units::area::square_meter_t b2  () const { return _b2;  }
    inline double                      e2  () const { return _e2;  }
    inline double                      e   () const { return _e;   }
    inline double                      ep2 () const { return _ep2; }
    inline double                      ep  () const { return _ep;  }

protected:

    units::length::meter_t _a = 0_m;            ///< [m] equatorial radius
    double _f = 0.0;                            ///< [-] ellipsoid flattening

    units::length::meter_t _b  = 0_m;           ///< [m] polar radius
    units::length::meter_t _r1 = 0_m;           ///< [m] mean radius
    units::area::square_meter_t _a2 = 0_sq_m;   ///< [m^2] equatorial radius squared
    units::area::square_meter_t _b2 = 0_sq_m;   ///< [m^2] polar radius squared
    double _e2  = 0.0;                          ///< [-] ellipsoid first eccentricity squared
    double _e   = 0.0;                          ///< [-] ellipsoid first eccentricity
    double _ep2 = 0.0;                          ///< [-] ellipsoid second eccentricity squared
    double _ep  = 0.0;                          ///< [-] ellipsoid second eccentricity
};

} // namespace mc

#endif // MCUTILS_GEO_ELLIPSOID_H_
