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
#ifndef MCUTILS_PHYSICS_INERTIA_H_
#define MCUTILS_PHYSICS_INERTIA_H_

#include <cmath>

namespace mc {
namespace physics {

/**
 * \brief First order inertia.
 * \param u desired value
 * \param y current value
 * \param dt [s] time step
 * \param tc [s] time constant
 * \return firt order inertia output
 */
inline double firstOrderInertia(double u, double y, double dt, double tc)
{
    if (tc > 0.0)
    {
        return y + (1.0 - exp(-dt / tc)) * (u - y);
    }
    return u;
}

} // namespace physics
} // namespace mc

#endif // MCUTILS_PHYSICS_INERTIA_H_
