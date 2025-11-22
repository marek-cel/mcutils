/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
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
