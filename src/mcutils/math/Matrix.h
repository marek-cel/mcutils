/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/
#ifndef MCUTILS_MATH_MATRIX_H_
#define MCUTILS_MATH_MATRIX_H_

#include <mcutils/mcutils_api.h>
#include <mcutils/extra_units.h>
#include <mcutils/math/MatrixMxN.h>
#include <mcutils/math/MatrixNxN.h>
#include <mcutils/math/Matrix3x3.h>
#include <mcutils/math/RotMatrix.h>

namespace mc {

using Matrix3x3d = Matrix3x3<double>;
extern template class MCUTILS_API MatrixMxN<double, 3, 3>;
extern template class MCUTILS_API MatrixNxN<double, 3>;
extern template class MCUTILS_API Matrix3x3<double>;

using Matrix4x4d = MatrixNxN<double, 4>;

using Matrix6x6d = MatrixNxN<double, 6>;

using Matrix3x3_kg_m_sq = Matrix3x3<units::moment_of_inertia::kilograms_meters_squared_t>;
extern template class MCUTILS_API Matrix3x3<units::moment_of_inertia::kilograms_meters_squared_t>;
extern template class MCUTILS_API MatrixMxN<units::moment_of_inertia::kilograms_meters_squared_t, 3, 3>;
extern template class MCUTILS_API MatrixNxN<units::moment_of_inertia::kilograms_meters_squared_t, 3>;

} // namespace mc

#endif // MCUTILS_MATH_MATRIX_H_
