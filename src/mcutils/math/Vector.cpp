/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/

#include <mcutils/math/Vector.h>

namespace mc {

template class MCUTILS_API VectorN<double, 3>;
template class MCUTILS_API Vector3<double>;

template class MCUTILS_API VectorN<double, 4>;
template class MCUTILS_API VectorN<double, 6>;

template class MCUTILS_API VectorN<units::length::meter_t, 3>;
template class MCUTILS_API Vector3<units::length::meter_t>;

template class MCUTILS_API VectorN<units::velocity::meters_per_second_t, 3>;
template class MCUTILS_API Vector3<units::velocity::meters_per_second_t>;

template class MCUTILS_API VectorN<units::acceleration::meters_per_second_squared_t, 3>;
template class MCUTILS_API Vector3<units::acceleration::meters_per_second_squared_t>;

template class MCUTILS_API VectorN<units::angular_velocity::radians_per_second_t, 3>;
template class MCUTILS_API Vector3<units::angular_velocity::radians_per_second_t>;

template class MCUTILS_API VectorN<units::angular_velocity::degrees_per_second_t, 3>;
template class MCUTILS_API Vector3<units::angular_velocity::degrees_per_second_t>;

template class MCUTILS_API VectorN<units::angular_acceleration::radians_per_second_squared_t, 3>;
template class MCUTILS_API Vector3<units::angular_acceleration::radians_per_second_squared_t>;

template class MCUTILS_API VectorN<units::angular_acceleration::degrees_per_second_squared_t, 3>;
template class MCUTILS_API Vector3<units::angular_acceleration::degrees_per_second_squared_t>;

template class MCUTILS_API VectorN<units::force::newton_t, 3>;
template class MCUTILS_API Vector3<units::force::newton_t>;

template class MCUTILS_API VectorN<units::torque::newton_meter_t, 3>;
template class MCUTILS_API Vector3<units::torque::newton_meter_t>;

} // namespace mc