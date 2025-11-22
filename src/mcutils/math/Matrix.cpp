/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/

#include <mcutils/math/Matrix.h>

namespace mc {

template class MCUTILS_API MatrixMxN<double, 3, 3>;
template class MCUTILS_API MatrixNxN<double, 3>;
template class MCUTILS_API Matrix3x3<double>;

template class MCUTILS_API Matrix3x3<units::moment_of_inertia::kilograms_meters_squared_t>;
template class MCUTILS_API MatrixMxN<units::moment_of_inertia::kilograms_meters_squared_t, 3, 3>;
template class MCUTILS_API MatrixNxN<units::moment_of_inertia::kilograms_meters_squared_t, 3>;

} // namespace mc