/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/
#ifndef MCUTILS_MATH_VECTOR_H_
#define MCUTILS_MATH_VECTOR_H_

#include <mcutils/mcutils_api.h>

#include <mcutils/extra_units.h>
#include <mcutils/math/VectorN.h>
#include <mcutils/math/Vector3.h>

namespace mc {

// dimensionless

using Vector3d = Vector3<double>;
extern template class MCUTILS_API VectorN<double, 3>;
extern template class MCUTILS_API Vector3<double>;

using Vector4d = VectorN<double, 4>;
extern template class MCUTILS_API VectorN<double, 4>;

using Vector6d = VectorN<double, 6>;
extern template class MCUTILS_API VectorN<double, 6>;

// length

using Vector3_m = Vector3<units::length::meter_t>;
extern template class MCUTILS_API VectorN<units::length::meter_t, 3>;
extern template class MCUTILS_API Vector3<units::length::meter_t>;

// velocity

using Vector3_mps = Vector3<units::velocity::meters_per_second_t>;
extern template class MCUTILS_API VectorN<units::velocity::meters_per_second_t, 3>;
extern template class MCUTILS_API Vector3<units::velocity::meters_per_second_t>;

// acceleration

using Vector3_mps_sq = Vector3<units::acceleration::meters_per_second_squared_t>;
extern template class MCUTILS_API VectorN<units::acceleration::meters_per_second_squared_t, 3>;
extern template class MCUTILS_API Vector3<units::acceleration::meters_per_second_squared_t>;

// angular velocity

using Vector3_rad_per_s = Vector3<units::angular_velocity::radians_per_second_t>;
extern template class MCUTILS_API VectorN<units::angular_velocity::radians_per_second_t, 3>;
extern template class MCUTILS_API Vector3<units::angular_velocity::radians_per_second_t>;

using Vector3_deg_per_s = Vector3<units::angular_velocity::degrees_per_second_t>;
extern template class MCUTILS_API VectorN<units::angular_velocity::degrees_per_second_t, 3>;
extern template class MCUTILS_API Vector3<units::angular_velocity::degrees_per_second_t>;

// angular acceleration

using Vector3_rad_per_s_sq = Vector3<units::angular_acceleration::radians_per_second_squared_t>;
extern template class MCUTILS_API VectorN<units::angular_acceleration::radians_per_second_squared_t, 3>;
extern template class MCUTILS_API Vector3<units::angular_acceleration::radians_per_second_squared_t>;

using Vector3_deg_per_s_sq = Vector3<units::angular_acceleration::degrees_per_second_squared_t>;
extern template class MCUTILS_API VectorN<units::angular_acceleration::degrees_per_second_squared_t, 3>;
extern template class MCUTILS_API Vector3<units::angular_acceleration::degrees_per_second_squared_t>;

// force

using Vector3_N = Vector3<units::force::newton_t>;
extern template class MCUTILS_API VectorN<units::force::newton_t, 3>;
extern template class MCUTILS_API Vector3<units::force::newton_t>;

// torque
using Vector3_Nm = Vector3<units::torque::newton_meter_t>;
extern template class MCUTILS_API VectorN<units::torque::newton_meter_t, 3>;
extern template class MCUTILS_API Vector3<units::torque::newton_meter_t>;

} // namespace mc

#endif // MCUTILS_MATH_VECTOR_H_
