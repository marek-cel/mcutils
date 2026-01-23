/****************************************************************************//*
 * Copyright (C) 2026 Marek M. Cel
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
#ifndef MCUTILS_PHYSICS_INERTIATENSORS_H_
#define MCUTILS_PHYSICS_INERTIATENSORS_H_

#include <mcutils/physics/PhysicsUtils.h>

namespace mc {
namespace physics {

/**
 * \brief Calculates inertia tensor of a solid sphere.
 * \param mass [kg] mass
 * \param radius [m] radius
 * \return inertia tensor [kg*m^2]
 * 
 * ### References:
 * - Awrejcewicz J.: Classical Mechanics: Kinematics and Statics, 2012, p.155
 */
Matrix3x3_kg_m_sq calculateInrtiaTensorOfSolidSphere(
    units::mass::kilogram_t mass,
    units::length::meter_t radius
)
{
    Matrix3x3_kg_m_sq result;
    result.xx() = (2.0 / 5.0) * mass * radius * radius;
    result.yy() = result.xx();
    result.zz() = result.xx();
    return result;
}

} // namespace physics
} // namespace mc

#endif // MCUTILS_PHYSICS_INERTIATENSORS_H_