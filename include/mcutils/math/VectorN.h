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
#ifndef MCUTILS_MATH_VECTORN_H_
#define MCUTILS_MATH_VECTORN_H_

#ifndef MCUTILS_MATH_VECTOR_H_
#   error "Do not include this file directly. Include <mcutils/math/Vector.h> instead."
#endif

#include <algorithm>
#include <cassert>
#include <limits>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <mcutils/extra_units.h>
#include <mcutils/misc/Check.h>
#include <mcutils/misc/StringUtils.h>

using namespace units::math;

namespace mc {

/**
 * \brief A template class representing a column vector with fixed size.
 *
 * This class represents a column vector of fixed size. It provides various
 * mathematical operations, including normalization, length calculation, and
 * element-wise operations. The vector elements are stored in a fixed-size
 * array.
 *
 * \tparam TYPE vector elements type
 * \tparam SIZE vector size
 */
template <typename TYPE, unsigned int SIZE>
class VectorN
{
public:

    static constexpr unsigned int kSize = SIZE; ///< vector size

    // LCOV_EXCL_START
    VectorN() = default;
    VectorN(const VectorN&) = default;
    VectorN(VectorN&&) = default;
    virtual ~VectorN() = default;
    VectorN& operator=(const VectorN&) = default;
    VectorN& operator=(VectorN&&) = default;
    // LCOV_EXCL_STOP

    /**
     * \brief Checks if all elements in the vector are valid.
     *
     * This function verifies that none of the elements in the vector are NaN (not a number)
     * or Inf (infinity). If any element is NaN or Inf, the function returns false.
     *
     * \return true if all elements are valid, false otherwise
     */
    bool isValid() const
    {
        return misc::isValid(_elements, kSize);
    }

    /** \return vector length squared */
    auto getLength2() const
    {
        auto length2 = _elements[0] * _elements[0];
        for (unsigned int i = 1; i < kSize; ++i)
        {
            length2 += _elements[i] * _elements[i];
        }
        return length2;
    }

    /** \return vector length */
    TYPE getLength() const
    {
        return sqrt(getLength2());
    }

    /** \brief Returns normalized vector. */
    VectorN<double, SIZE> getNormalized() const
    {
        VectorN<double, kSize> result;
        calculateNormalized(*this, &result);
        return result;
    }

    /**
     * \brief Gets std::vector of vector elements.
     * \return std::vector<TYPE> of vector elements
     */
    std::vector<TYPE> getStdVector() const
    {
        std::vector<TYPE> elements(kSize);
        std::copy(_elements, _elements + kSize, elements.begin());
        return elements;
    }

    /**
     * \brief Sets vector elements from std::vector.
     * \param elements input std::vector of vector elements
     */
    inline void setFromStdVector(const std::vector<TYPE>& elements)
    {
        assert(elements.size() == kSize);
        std::copy(elements.begin(), elements.end(), _elements);
    }

    /**
     * \brief Sets vector elements from a string.
     *
     * Values in the given string should be separated by whitespaces.
     *
     * \param str input string
     */
    void setFromString(const char* str)
    {
        std::vector<TYPE> elements(kSize);

        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] = TYPE{std::numeric_limits<double>::quiet_NaN()};
        }

        std::stringstream ss(misc::stripSpaces(str));
        bool valid = true;
        for (unsigned int i = 0; i < kSize && valid; ++i)
        {
            double temp = std::numeric_limits<double>::quiet_NaN();
            ss >> temp;
            valid &= misc::isValid(temp);
            elements[i] = TYPE{temp};
        }

        if (valid)
        {
            setFromStdVector(elements);
        }
    }

    /**
     * \brief Swaps the values of two specified rows in the vector.
     * \param row1 Index of the first row
     * \param row2 Index of the second row
     */
    void swapRows(unsigned int row1, unsigned int row2)
    {
        if (row1 < kSize && row2 < kSize)
        {
            std::swap(_elements[row1], _elements[row2]);
        }
    }

    /**
     * \brief Returns a string representation of the vector.
     * \return String representation of the vector
     */
    std::string toString() const
    {
        std::stringstream ss;
        for (unsigned int i = 0; i < kSize; ++i)
        {
            if (i != 0) ss << "\t";
            ss << _elements[i];
        }
        return ss.str();
    }

    /** \brief Sets all vector elements to zero. */
    void zeroize()
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] = TYPE{0};
        }
    }

    /** \brief Converts the vector to a dimensionless vector. */
    inline VectorN<double, SIZE> getDimensionless() const
    {
        VectorN<double, kSize> result;
        for (unsigned int i = 0; i < kSize; ++i)
        {
            result(i) = static_cast<double>(_elements[i]);
        }
        return result;
    }

    /**
     * \brief Casting operator.
     *
     * Converts the vector to another type if the units are compatible.
     */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value
        &&
        units::traits::is_convertible_unit_t<TYPE, TYPE2>::value, int>::type = 0
    >
    operator VectorN<TYPE2, SIZE>() const
    {
        VectorN<TYPE2, kSize> result;
        for (unsigned int i = 0; i < kSize; ++i)
        {
            result(i) = _elements[i];
        }
        return result;
    }

    /**
     * \brief Items accessor.
     *
     * Please notice that this operator is NOT bounds-checked.
     *
     * \param index index of the element
     * \return vector element at given index
     */
    inline TYPE operator()(unsigned int index) const
    {
        return _elements[index];
    }

    /**
     * \brief Items accessor.
     *
     * Please notice that this operator is NOT bounds-checked.
     *
     * \param index index of the element
     * \return vector element at given index
     */
    inline TYPE& operator()(unsigned int index)
    {
        return _elements[index];
    }

    /**
     * \brief Addition operator.
     * \param vect vector to be added
     * \return sum of the vectors
     */
    VectorN<TYPE, SIZE> operator+(const VectorN<TYPE, SIZE>& vect) const
    {
        VectorN<TYPE, kSize> result(*this);
        result.add(vect);
        return result;
    }

    /**
     * \brief Negation operator.
     * \return negated vector
     */
    VectorN<TYPE, SIZE> operator-() const
    {
        VectorN<TYPE, kSize> result(*this);
        result.negate();
        return result;
    }

    /**
     * \brief Subtraction operator.
     * \param vect vector to be subtracted
     * \return difference of the vectors
     */
    VectorN<TYPE, SIZE> operator-(const VectorN<TYPE, SIZE>& vect) const
    {
        VectorN<TYPE, kSize> result(*this);
        result.subtract(vect);
        return result;
    }

    // /**
    //  * \brief Multiplication by a scalar operator.
    //  *
    //  * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
    //  * this makes radians a pure number without physical dimension.
    //  * So operators for angular velocity and angular acceleration are defined
    //  * as specializations of this template.
    //  *
    //  * This template is enabled when TYPE and TYPE2 are both units, but not angular velocity
    //  * or angular acceleration, or when TYPE2 is a time unit.
    //  *
    //  * \tparam TYPE2 RHS operand type
    //  * \param value value to be multiplied by
    //  * \return product of the vector multiplied by the value
    //  */
    // template <class TYPE2, typename std::enable_if<
    //     (
    //         !units::traits::is_convertible_unit_t<TYPE, units::angular_velocity::radians_per_second_t>::value
    //         &&
    //         !units::traits::is_convertible_unit_t<TYPE, units::angular_acceleration::radians_per_second_squared_t>::value
    //         &&
    //         !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
    //         &&
    //         !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
    //         ||
    //         units::traits::is_convertible_unit_t<TYPE2, units::time::second_t>::value
    //     )
    //     &&
    //     units::traits::is_unit_t<TYPE>::value
    //     &&
    //     units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    // >
    // VectorN<
    //     units::unit_t<
    //         units::compound_unit<
    //             typename units::traits::unit_t_traits<TYPE>::unit_type,
    //             typename units::traits::unit_t_traits<TYPE2>::unit_type
    //         >
    //     >,
    //     SIZE
    // >
    // operator*(TYPE2 value) const
    // {
    //     VectorN<
    //         units::unit_t<
    //             units::compound_unit<
    //                 typename units::traits::unit_t_traits<TYPE>::unit_type,
    //                 typename units::traits::unit_t_traits<TYPE2>::unit_type
    //             >
    //         >,
    //         SIZE
    //     > result;
    //     multiplyVectorByValue(*this, value, &result);
    //     return result;
    // }

    // /**
    //  * \brief Multiplication by a scalar operator.
    //  *
    //  * This is a specialization for the case when the vector is angular velocity.
    //  *
    //  * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
    //  * this makes radians a pure number without physical dimension.
    //  *
    //  * This specialization is enabled when TYPE is angular velocity and TYPE2 is a unit other than
    //  * angular velocity, angular acceleration or time.
    //  *
    //  * \tparam TYPE2 RHS operand type
    //  * \param value value to be multiplied by
    //  * \return product of the vector multiplied by the value
    //  */
    // template <class TYPE2, typename std::enable_if<
    //     units::traits::is_convertible_unit_t<TYPE, units::angular_velocity::radians_per_second_t>::value
    //     &&
    //     !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
    //     &&
    //     !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
    //     &&
    //     !units::traits::is_convertible_unit_t<TYPE2, units::time::second_t>::value
    //     &&
    //     units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    // >
    // VectorN<
    //     units::unit_t<
    //         units::compound_unit<
    //             typename units::traits::unit_t_traits<TYPE2>::unit_type,
    //             typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
    //         >
    //     >,
    //     SIZE
    // >
    // operator*(TYPE2 value) const
    // {
    //     VectorN<units::angular_velocity::radians_per_second_t,SIZE> temp_rad_per_s = *this;
    //     VectorN<units::auxiliary::per_second_t,SIZE> temp;
    //     for (unsigned int i = 0; i < kSize; ++i)
    //     {
    //         temp(i) = units::auxiliary::per_second_t{ temp_rad_per_s(i)() };
    //     }

    //     VectorN<
    //         units::unit_t<
    //             units::compound_unit<
    //                 typename units::traits::unit_t_traits<TYPE2>::unit_type,
    //                 typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
    //             >
    //         >,
    //         SIZE
    //     > result;
    //     multiplyVectorByValue(temp, value, &result);
    //     return result;
    // }

    // /**
    //  * \brief Multiplication by a scalar operator.
    //  *
    //  * This is a specialization for the case when the value is angular velocity.
    //  *
    //  * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
    //  * this makes radians a pure number without physical dimension.
    //  *
    //  * This specialization is enabled when TYPE is a unit and TYPE2 is angular velocity.
    //  *
    //  * \tparam TYPE2 RHS operand type
    //  * \param value value to be multiplied by
    //  * \return product of the vector multiplied by the value
    //  */
    // template <class TYPE2, typename std::enable_if<
    //     units::traits::is_unit_t<TYPE>::value
    //     &&
    //     units::traits::is_convertible_unit_t<
    //         TYPE2, units::angular_velocity::radians_per_second_t
    //     >::value, int>::type = 0
    // >
    // auto operator*(TYPE2 value) const
    // {
    //     units::angular_velocity::radians_per_second_t temp_rad_per_s = value;
    //     units::auxiliary::per_second_t temp = units::auxiliary::per_second_t{ temp_rad_per_s() };

    //     VectorN<
    //         units::unit_t<
    //             units::compound_unit<
    //                 typename units::traits::unit_t_traits<TYPE>::unit_type,
    //                 typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
    //             >
    //         >,
    //         SIZE
    //     > result;
    //     multiplyVectorByValue(*this, temp, &result);
    //     return result;
    // }

    // /**
    //  * \brief Multiplication by a scalar operator.
    //  *
    //  * This is a specialization for the case when the vector is angular acceleration.
    //  *
    //  * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
    //  * this makes radians a pure number without physical dimension.
    //  *
    //  * This specialization is enabled when TYPE is angular acceleration and TYPE2 is a unit other than
    //  * angular velocity, angular acceleration or time.
    //  *
    //  * \tparam TYPE2 RHS operand type
    //  * \param value value to be multiplied by
    //  * \return product of the vector multiplied by the value
    //  */
    // template <class TYPE2, typename std::enable_if<
    //     units::traits::is_convertible_unit_t<TYPE, units::angular_acceleration::radians_per_second_squared_t>::value
    //     &&
    //     !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
    //     &&
    //     !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
    //     &&
    //     !units::traits::is_convertible_unit_t<TYPE2, units::time::second_t>::value
    //     &&
    //     units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    // >
    // VectorN<
    //     units::unit_t<
    //         units::compound_unit<
    //             typename units::traits::unit_t_traits<TYPE2>::unit_type,
    //             typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
    //         >
    //     >,
    //     SIZE
    // >
    // operator*(TYPE2 value) const
    // {
    //     VectorN<units::angular_acceleration::radians_per_second_squared_t,SIZE> temp_rad_per_s_sq = *this;
    //     VectorN<units::auxiliary::per_second_squared_t,SIZE> temp;
    //     for (unsigned int i = 0; i < kSize; ++i)
    //     {
    //         temp(i) = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq(i)() };
    //     }

    //     VectorN<
    //         units::unit_t<
    //             units::compound_unit<
    //                 typename units::traits::unit_t_traits<TYPE2>::unit_type,
    //                 typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
    //             >
    //         >,
    //         SIZE
    //     > result;
    //     multiplyVectorByValue(temp, value, &result);
    //     return result;
    // }

    // /**
    //  * \brief Multiplication by a scalar operator.
    //  *
    //  * This is a specialization for the case when the value is angular acceleration.
    //  *
    //  * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
    //  * this makes radians a pure number without physical dimension.
    //  *
    //  * This specialization is enabled when TYPE is a unit and TYPE2 is angular acceleration.
    //  *
    //  * \tparam TYPE2 RHS operand type
    //  * \param value value to be multiplied by
    //  * \return product of the vector multiplied by the value
    //  */
    // template <class TYPE2, typename std::enable_if<
    //     units::traits::is_unit_t<TYPE>::value
    //     &&
    //     units::traits::is_convertible_unit_t<
    //         TYPE2, units::angular_acceleration::radians_per_second_squared_t
    //     >::value, int>::type = 0
    // >
    // auto operator*(TYPE2 value) const
    // {
    //     units::angular_acceleration::radians_per_second_squared_t temp_rad_per_s_sq = value;
    //     units::auxiliary::per_second_squared_t temp = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq() };

    //     VectorN<
    //         units::unit_t<
    //             units::compound_unit<
    //                 typename units::traits::unit_t_traits<TYPE>::unit_type,
    //                 typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
    //             >
    //         >,
    //         SIZE
    //     > result;
    //     multiplyVectorByValue(*this, temp, &result);
    //     return result;
    // }

    // /**
    //  * \brief Multiplication by a scalar operator.
    //  *
    //  * This is a specialization for the case when the vector is dimensionless.
    //  */
    // template <class TYPE2, typename std::enable_if<
    //     !units::traits::is_unit_t<TYPE>::value
    //     &&
    //     units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    // >
    // VectorN<TYPE2,SIZE> operator*(TYPE2 value) const
    // {
    //     VectorN<TYPE2,SIZE> result;
    //     multiplyVectorByValue(*this, value, &result);
    //     return result;
    // }

    // /**
    //  * \brief Multiplication by a scalar operator.
    //  *
    //  * This is a specialization for the case when the value is dimensionless.
    //  *
    //  * \tparam TYPE2 RHS operand type
    //  * \param value [-] value to be multiplied by
    //  * \return product of the vector multiplied by the value
    //  */
    // VectorN<TYPE,SIZE> operator*(double value) const
    // {
    //     VectorN<TYPE,SIZE> result;
    //     multiplyVectorByValue(*this, value, &result);
    //     return result;
    // }

    // /**
    //  * \brief Calculates the dot product of two vectors.
    //  *
    //  * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
    //  * this makes radians a pure number without physical dimension.
    //  * So operators for angular velocity and angular acceleration are defined
    //  * as specializations of this template.
    //  *
    //  * This template is enabled when TYPE and TYPE2 are both units, but not angular velocity
    //  * or angular acceleration.
    //  *
    //  * \tparam TYPE2 RHS vector type
    //  * \param vect RHS vector
    //  * \return dot product of two vectors
    //  */
    // template <class TYPE2, typename std::enable_if<
    //     !units::traits::is_convertible_unit_t<TYPE, units::angular_velocity::radians_per_second_t>::value
    //     &&
    //     !units::traits::is_convertible_unit_t<TYPE, units::angular_acceleration::radians_per_second_squared_t>::value
    //     &&
    //     !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
    //     &&
    //     !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
    //     &&
    //     units::traits::is_unit_t<TYPE>::value
    //     &&
    //     units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    // >
    // auto operator*(const VectorN<TYPE2,SIZE>& vect) const
    // {
    //     units::unit_t<
    //         units::compound_unit<
    //             typename units::traits::unit_t_traits<TYPE>::unit_type,
    //             typename units::traits::unit_t_traits<TYPE2>::unit_type
    //         >
    //     > result {0};
    //     calculateDotProduct(*this, vect, &result);
    //     return result;
    // }

    // /**
    //  * \brief Calculates the dot product of two vectors.
    //  *
    //  * This is a specialization for the case when the first vector is angular velocity.
    //  *
    //  * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
    //  * this makes radians a pure number without physical dimension.
    //  *
    //  * This specialization is enabled when TYPE is angular velocity and TYPE2 is a unit other than
    //  * angular velocity or angular acceleration.
    //  *
    //  * \tparam TYPE2 RHS vector type
    //  * \param vect RHS vector
    //  * \return dot product of two vectors
    //  */
    // template <typename TYPE2, typename std::enable_if<
    //     units::traits::is_convertible_unit_t<TYPE, units::angular_velocity::radians_per_second_t>::value
    //     &&
    //     !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
    //     &&
    //     !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
    //     &&
    //     units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    // >
    // auto operator*(const VectorN<TYPE2,SIZE>& vect) const
    // {
    //     VectorN<units::angular_velocity::radians_per_second_t,SIZE> temp_rad_per_s = *this;
    //     VectorN<units::auxiliary::per_second_t,SIZE> temp;
    //     for (unsigned int i = 0; i < kSize; ++i)
    //     {
    //         temp(i) = units::auxiliary::per_second_t{ temp_rad_per_s(i)() };
    //     }

    //     units::unit_t<
    //         units::compound_unit<
    //             typename units::traits::unit_t_traits<TYPE2>::unit_type,
    //             typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
    //         >
    //     > result {0};
    //     calculateDotProduct(temp, vect, &result);
    //     return result;
    // }

    // /**
    //  * \brief Calculates the dot product of two vectors.
    //  *
    //  * This is a specialization for the case when the second vector is angular velocity.
    //  *
    //  * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
    //  * this makes radians a pure number without physical dimension.
    //  *
    //  * This specialization is enabled when TYPE is a unit and TYPE2 is angular velocity.
    //  *
    //  * \tparam TYPE2 RHS vector type (angular velocity, eg. units::angular_velocity::radians_per_second_t)
    //  * \param vect [angular velocity, eg. rad/s] RHS vector
    //  * \return dot product of two vectors
    //  */
    // template <typename TYPE2, typename std::enable_if<
    //     units::traits::is_unit_t<TYPE>::value
    //     &&
    //     units::traits::is_convertible_unit_t<
    //         TYPE2, units::angular_velocity::radians_per_second_t
    //     >::value, int>::type = 0
    // >
    // auto operator*(const VectorN<TYPE2,SIZE>& vect) const
    // {
    //     VectorN<units::angular_velocity::radians_per_second_t,SIZE> temp_rad_per_s = vect;
    //     VectorN<units::auxiliary::per_second_t,SIZE> temp;
    //     for (unsigned int i = 0; i < kSize; ++i)
    //     {
    //         temp(i) = units::auxiliary::per_second_t{ temp_rad_per_s(i)() };
    //     }

    //     units::unit_t<
    //         units::compound_unit<
    //             typename units::traits::unit_t_traits<TYPE>::unit_type,
    //             typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
    //         >
    //     > result {0};
    //     calculateDotProduct(*this, temp, &result);
    //     return result;
    // }

    // /**
    //  * \brief Calculates the dot product of two vectors.
    //  *
    //  * This is a specialization for the case when the first vector is angular acceleration.
    //  *
    //  * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
    //  * this makes radians a pure number without physical dimension.
    //  *
    //  * This specialization is enabled when TYPE is angular acceleration and TYPE2 is a unit other than
    //  * angular velocity or angular acceleration.
    //  *
    //  * \tparam TYPE2 RHS vector type
    //  * \param vect RHS vector
    //  * \return dot product of two vectors
    //  */
    // template <typename TYPE2, typename std::enable_if<
    //     units::traits::is_convertible_unit_t<TYPE, units::angular_acceleration::radians_per_second_squared_t>::value
    //     &&
    //     !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
    //     &&
    //     !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
    //     &&
    //     units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    // >
    // auto operator*(const VectorN<TYPE2,SIZE>& vect) const
    // {
    //     VectorN<units::angular_acceleration::radians_per_second_squared_t,SIZE> temp_rad_per_s_sq = *this;
    //     VectorN<units::auxiliary::per_second_squared_t,SIZE> temp;
    //     for (unsigned int i = 0; i < kSize; ++i)
    //     {
    //         temp(i) = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq(i)() };
    //     }

    //     units::unit_t<
    //         units::compound_unit<
    //             typename units::traits::unit_t_traits<TYPE2>::unit_type,
    //             typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
    //         >
    //     > result {0};
    //     calculateDotProduct(temp, vect, &result);
    //     return result;
    // }

    // /**
    //  * \brief Calculates the dot product of two vectors.
    //  *
    //  * This is a specialization for the case when the second vector is angular acceleration.
    //  *
    //  * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
    //  * this makes radians a pure number without physical dimension.
    //  *
    //  * This specialization is enabled when TYPE is a unit and TYPE2 is angular acceleration.
    //  *
    //  * \tparam TYPE2 RHS vector type
    //  * \param vect [angular acceleration, eg. rad/s^2] RHS vector
    //  * \return dot product of two vectors
    //  */
    // template <typename TYPE2, typename std::enable_if<
    //     units::traits::is_unit_t<TYPE>::value
    //     &&
    //     units::traits::is_convertible_unit_t<
    //         TYPE2, units::angular_acceleration::radians_per_second_squared_t
    //     >::value, int>::type = 0
    // >
    // auto operator*(const VectorN<TYPE2,SIZE>& vect) const
    // {
    //     VectorN<units::angular_acceleration::radians_per_second_squared_t,SIZE> temp_rad_per_s_sq = vect;
    //     VectorN<units::auxiliary::per_second_squared_t,SIZE> temp;
    //     for (unsigned int i = 0; i < kSize; ++i)
    //     {
    //         temp(i) = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq(i)() };
    //     }

    //     units::unit_t<
    //         units::compound_unit<
    //             typename units::traits::unit_t_traits<TYPE>::unit_type,
    //             typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
    //         >
    //     > result {0};
    //     calculateDotProduct(*this, temp, &result);
    //     return result;
    // }

    // /**
    //  * \brief Calculates the dot product of two vectors.
    //  *
    //  * This is a specialization for the case when the first vector is dimensionless.
    //  *
    //  * \tparam TYPE2 RHS vector type
    //  * \param vect RHS vector
    //  * \return dot product of two vectors
    //  */
    // template <typename TYPE2, typename std::enable_if<
    //     !units::traits::is_unit_t<TYPE>::value
    //     &&
    //     units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    // >
    // TYPE2 operator*(const VectorN<TYPE2,SIZE>& vect) const
    // {
    //     TYPE2 result {0};
    //     calculateDotProduct(*this, vect, &result);
    //     return result;
    // }

    // /**
    //  * \brief Calculates the dot product of two vectors.
    //  *
    //  * This is a specialization for the case when the second vector is dimensionless.
    //  *
    //  * \tparam TYPE2 RHS vector type (dimensionless)
    //  * \param vect [-] RHS vector
    //  * \return dot product of two vectors
    //  */
    // template <typename TYPE2, typename std::enable_if<
    //     units::traits::is_unit_t<TYPE>::value
    //     &&
    //     !units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    // >
    // TYPE operator*(const VectorN<TYPE2,SIZE>& vect) const
    // {
    //     TYPE result {0};
    //     calculateDotProduct(*this, vect, &result);
    //     return result;
    // }

    // /**
    //  * \brief Calculates the dot product of two vectors.
    //  *
    //  * This is a specialization for the case when both vectors are dimensionless.
    //  *
    //  * \tparam TYPE2 RHS vector type (dimensionless)
    //  * \param vect [-] RHS vector
    //  * \return dot product of two vectors
    //  */
    // template <typename TYPE2, typename std::enable_if<
    //     !units::traits::is_unit_t<TYPE>::value
    //     &&
    //     !units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    // >
    // double operator*(const VectorN<TYPE2,SIZE>& vect) const
    // {
    //     double result = 0.0;
    //     calculateDotProduct(*this, vect, &result);
    //     return result;
    // }

    // /**
    //  * \brief Division by scalar operator.
    //  *
    //  * \tparam TYPE2 RHS operand type
    //  * \param value value to divide the vector by
    //  * \return result of the division
    //  */
    // template <class TYPE2, typename std::enable_if<
    //     units::traits::is_unit_t<TYPE>::value
    //     &&
    //     units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    // >
    // auto operator/(TYPE2 value) const
    // {
    //     VectorN<
    //         units::unit_t<
    //             units::compound_unit<
    //                 typename units::traits::unit_t_traits<TYPE>::unit_type,
    //                 units::inverse<typename units::traits::unit_t_traits<TYPE2>::unit_type>
    //             >
    //         >,
    //         SIZE
    //     > result;
    //     multiplyVectorByValue(*this, 1.0 / value, &result);
    //     return result;
    // }

    // /**
    //  * \brief Division by scalar operator.
    //  *
    //  * This is a specialization for the case when the vector is a dimensionless.
    //  *
    //  * \param value [-] value to divide the vector by
    //  * \return result of the division
    //  */
    // template <class TYPE2, typename std::enable_if<
    //     !units::traits::is_unit_t<TYPE>::value
    //     &&
    //     units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    // >
    // auto operator/(TYPE2 value) const
    // {
    //     VectorN<
    //         units::unit_t<
    //             units::compound_unit<
    //                 units::inverse<typename units::traits::unit_t_traits<TYPE2>::unit_type>
    //             >
    //         >,
    //         SIZE
    //     > result;
    //     multiplyVectorByValue(*this, 1.0 / value, &result);
    //     return result;
    // }

    /**
     * \brief Division by scalar operator.
     *
     * This is a specialization for the case when the value is a number.
     *
     * \param value [-] value to divide the vector by
     * \return result of the division
     */
    VectorN<TYPE,SIZE> operator/(double value) const
    {
        VectorN<TYPE,SIZE> result;
        multiplyVectorByValue(*this, 1.0 / value, &result);
        return result;
    }

    /**
     * \brief Unary addition operator.
     * \param vect vector to be added
     * \return reference to the updated vector
     */
    VectorN<TYPE, SIZE>& operator+=(const VectorN<TYPE, SIZE>& vect)
    {
        add(vect);
        return *this;
    }

    /**
     * \brief Unary subtraction operator.
     * \param vect vector to be subtracted
     * \return reference to the updated vector
     */
    VectorN<TYPE, SIZE>& operator-=(const VectorN<TYPE, SIZE>& vect)
    {
        subtract(vect);
        return *this;
    }

    // /**
    //  * \brief Unary multiplication operator.
    //  * \param value [-] value to multiply the vector by
    //  * \return reference to the updated vector
    //  */
    // VectorN<TYPE, SIZE>& operator*=(double value)
    // {
    //     *this = (*this) * value;
    //     return *this;
    // }

    /**
     * \brief Unary division operator.
     * \param value [-] value to divide the vector by
     * \return reference to the updated vector
     */
    VectorN<TYPE, SIZE>& operator/=(double value)
    {
        *this = (*this) / value;
        return *this;
    }

    /**
     * \brief Equality operator.
     * \param vect Vector to compare
     * \return true if the vectors are equal, false otherwise
     */
    bool operator==(const VectorN<TYPE, SIZE>& vect) const
    {
        bool result = true;
        for (unsigned int i = 0; i < kSize; ++i)
        {
            result = result && (_elements[i] == vect._elements[i]);
        }
        return result;
    }

    /**
     * \brief Inequality operator.
     * \param vect Vector to compare
     * \return true if the vectors are not equal, false otherwise
     */
    bool operator!=(const VectorN<TYPE, SIZE>& vect) const
    {
        return !(*this == vect);
    }

protected:

    TYPE _elements[kSize] = { TYPE{0} };    ///< vector elements

    /**
     * \brief Adds the vectors.
     * \param vect vector to be added
     */
    void add(const VectorN<TYPE, SIZE>& vect)
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] += vect._elements[i];
        }
    }

    /** \brief Negates (inverts) the vector. */
    void negate()
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] = -_elements[i];
        }
    }

    /**
     * \brief Subtracts the vectors.
     * \param vect vector to be subtracted
     */
    void subtract(const VectorN<TYPE, SIZE>& vect)
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] -= vect._elements[i];
        }
    }

    /**
     * \brief Normalized vector calculation algorithm.
     * \param vect input vector
     * \param result output vector
     */
    void calculateNormalized(const VectorN<TYPE, SIZE>& vect, VectorN<double, SIZE>* result) const
    {
        double length = static_cast<double>(vect.getLength());
        if (length > 0.0)
        {
            double length_inv = 1.0 / length;
            for (unsigned int i = 0; i < kSize; ++i)
            {
                (*result)(i) = static_cast<double>(vect._elements[i]) * length_inv;
            }
        }
    }

    /**
     * \brief Multiplication a vector by a scalar algorithm.
     * \param vect input vector
     * \param value value to multiply the vector by
     * \param result output vector
     */
    template <typename TYPE1, typename TYPE2, typename TYPE3>
    void multiplyVectorByValue(const VectorN<TYPE1, SIZE>& vect, const TYPE2& value, VectorN<TYPE3, SIZE>* result) const
    {
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            (*result)(i) = vect(i) * value;
        }
    }

    /**
     * \brief Dot product calculation algorithm.
     * \param vect1 first vector
     * \param vect2 second vector
     * \param result output result
     */
    template <typename TYPE1, typename TYPE2, typename TYPE3>
    void calculateDotProduct(const VectorN<TYPE1, SIZE>& vect1, const VectorN<TYPE2, SIZE>& vect2, TYPE3* result) const
    {
        *result = TYPE3{0};
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            *result += vect1(i) * vect2(i);
        }
    }
};

/**
 * \brief Multiplication operator.
 *
 * This is an operator for multiplying a scalar by a vector, which is commutative.
 */
template <typename TYPE1, class TYPE2, unsigned int SIZE, typename std::enable_if<
    units::traits::is_unit_t<TYPE1>::value, int>::type = 0
>
auto operator*(TYPE1 value, const VectorN<TYPE2, SIZE>& vect)
{
    return vect * value;
}

/**
 * \brief Multiplication operator.
 *
 * This is a specialization for the case when the scalar is a number.
 */
template<typename TYPE, unsigned int SIZE>
VectorN<TYPE, SIZE> operator*(double value, const VectorN<TYPE, SIZE>& vect)
{
    return vect * value;
}

} // namespace mc

#endif // MCUTILS_MATH_VECTORN_H_
