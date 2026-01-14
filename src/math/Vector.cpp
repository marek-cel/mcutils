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

#include <mcutils/math/Vector.h>

namespace mc {

template class MCUTILS_API VectorN<float, 3>;
template class MCUTILS_API Vector3<float>;

template class MCUTILS_API VectorN<double, 3>;
template class MCUTILS_API Vector3<double>;

template class MCUTILS_API VectorN<float, 4>;
template class MCUTILS_API VectorN<float, 6>;

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