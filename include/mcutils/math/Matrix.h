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
#ifndef MCUTILS_MATH_MATRIX_H_
#define MCUTILS_MATH_MATRIX_H_

#include <mcutils/mcutils_api.h>
#include <mcutils/extra_units.h>
#include <mcutils/math/MatrixMxN.h>
// #include <mcutils/math/MatrixNxN.h>
// #include <mcutils/math/Matrix3x3.h>
// #include <mcutils/math/RotMatrix.h>

namespace mc {

// using Matrix3x3d = Matrix3x3<double>;
// extern template class MCUTILS_API MatrixMxN<double, 3, 3>;
// extern template class MCUTILS_API MatrixNxN<double, 3>;
// extern template class MCUTILS_API Matrix3x3<double>;

// using Matrix4x4d = MatrixNxN<double, 4>;

// using Matrix6x6d = MatrixNxN<double, 6>;

// using Matrix3x3_kg_m_sq = Matrix3x3<units::moment_of_inertia::kilograms_meters_squared_t>;
// extern template class MCUTILS_API Matrix3x3<units::moment_of_inertia::kilograms_meters_squared_t>;
// extern template class MCUTILS_API MatrixMxN<units::moment_of_inertia::kilograms_meters_squared_t, 3, 3>;
// extern template class MCUTILS_API MatrixNxN<units::moment_of_inertia::kilograms_meters_squared_t, 3>;

} // namespace mc

#endif // MCUTILS_MATH_MATRIX_H_
