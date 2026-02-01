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
#include <array>
#include <cassert>
#include <limits>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <mcutils/units.h>
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
    VectorN(const VectorN<TYPE,SIZE>&) = default;
    VectorN(VectorN<TYPE,SIZE>&&) = default;
    virtual ~VectorN() = default;
    VectorN<TYPE,SIZE>& operator=(const VectorN<TYPE,SIZE>&) = default;
    VectorN<TYPE,SIZE>& operator=(VectorN<TYPE,SIZE>&&) = default;
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
        return check::isValid(_elements, SIZE);
    }

    /**
     * \brief Calculates and returns the squared length of the vector. 
     * \return vector length squared 
     */
    auto getLengthSquared() const
    {
        auto length2 = _elements[0] * _elements[0];
        for (unsigned int i = 1; i < SIZE; ++i)
        {
            length2 += _elements[i] * _elements[i];
        }
        return length2;
    }

    /**
     * \brief Calculates and returns the length of the vector. 
     * \return vector length 
     */
    TYPE getLength() const
    {
        return sqrt(getLengthSquared());
    }

    /** 
     * \brief Returns normalized vector. 
     * \return normalized vector
     */
    VectorN<double, SIZE> getNormalized() const
    {
        VectorN<double, SIZE> result;
        calculateNormalized(*this, &result);
        return result;
    }

    /**
     * \brief Returns angle-dimension-stripped version of the vector.
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension. So in operations like
     * v [m/s] = omega [ras/s] x r [m], radians are treated as dimensionless.
     * \return angle-dimension-stripped vector
     */
    template <typename U = TYPE>
    requires (
        units::traits::is_unit_t<TYPE>::value &&
        units::traits::has_angle_dimension_t<TYPE>::value
    )
    auto getAngleStripped() const
    {
        VectorN<typename units::detail::strip_angle_dimension<TYPE>::stripped_type, SIZE> result;
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            result(i) = units::detail::strip_angle_dimension<TYPE>::strip(_elements[i]);
        }
        return result;
    }

    /**
     * \brief Gets std::array of vector elements.
     * \return std::array<TYPE, SIZE> of vector elements
     */
    std::array<TYPE, SIZE> getStdArray() const
    {
        std::array<TYPE, SIZE> elements;
        std::copy(_elements, _elements + SIZE, elements.begin());
        return elements;
    }

    /**
     * \brief Gets std::vector of vector elements.
     * \return std::vector<TYPE> of vector elements
     */
    std::vector<TYPE> getStdVector() const
    {
        std::vector<TYPE> elements(SIZE);
        std::copy(_elements, _elements + SIZE, elements.begin());
        return elements;
    }

    /**
     * \brief Sets vector elements from std::array.
     * \param elements input std::array of vector elements
     */
    inline void setFromStdArray(const std::array<TYPE, SIZE>& elements)
    {
        std::copy(elements.begin(), elements.end(), _elements);
    }

    /**
     * \brief Sets vector elements from std::vector.
     * \param elements input std::vector of vector elements
     */
    inline void setFromStdVector(const std::vector<TYPE>& elements)
    {
        assert(elements.size() == SIZE);
        std::copy(elements.begin(), elements.end(), _elements);
    }

    /**
     * \brief Sets vector elements from a string.
     * Values in the given string should be separated by whitespaces.
     * \param str input string
     */
    void setFromString(const char* str)
    {
        std::vector<TYPE> elements(SIZE);

        for (unsigned int i = 0; i < SIZE; ++i)
        {
            _elements[i] = TYPE{std::numeric_limits<double>::quiet_NaN()};
        }

        std::stringstream ss(str::stripSpaces(str));
        bool valid = true;
        for (unsigned int i = 0; i < SIZE && valid; ++i)
        {
            float temp = std::numeric_limits<float>::quiet_NaN();
            ss >> temp;
            valid &= check::isValid(temp);
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
        if (row1 < SIZE && row2 < SIZE)
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
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            if (i != 0) ss << "\t";
            ss << _elements[i];
        }
        return ss.str();
    }

    /** 
     * \brief Negates (inverts) the vector. 
     */
    void negate()
    {
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            _elements[i] = -_elements[i];
        }
    }

    /** 
     * \brief Sets all vector elements to zero. 
     */
    void zeroize()
    {
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            _elements[i] = TYPE{0};
        }
    }

    /**
     * \brief Casting operator.
     * Converts the vector to another type.
     * \tparam NEW_TYPE new vector element type
     * \return converted vector
     */
    template <typename NEW_TYPE>
    requires (
        std::is_same<TYPE, NEW_TYPE>::value == false &&
        (std::is_arithmetic<NEW_TYPE>::value || units::traits::is_convertible_unit_t<NEW_TYPE, TYPE>::value)
    )
    operator VectorN<NEW_TYPE, SIZE>() const
    {
        VectorN<NEW_TYPE, SIZE> result;
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            result(i) = static_cast<NEW_TYPE>(_elements[i]);
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
        VectorN<TYPE, SIZE> result;
        addVectors(*this, vect, &result);
        return result;
    }

    /**
     * \brief Addition operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param vect vector to be added
     * \return sum of the vectors
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value  && 
        std::is_arithmetic<RHS_TYPE>::value && 
        std::is_same<TYPE, RHS_TYPE>::value == false
    )
    auto operator+(const VectorN<RHS_TYPE, SIZE>& vect) const
    {
        VectorN<std::common_type_t<TYPE, RHS_TYPE>, SIZE> result;
        addVectors(*this, vect, &result);
        return result;
    }

    /**
     * \brief Addition operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param vect vector to be added
     * \return sum of the vectors
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value == false && 
        std::is_arithmetic<RHS_TYPE>::value == false &&
        std::is_same<TYPE, RHS_TYPE>::value == false &&
        units::traits::is_convertible_unit_t<TYPE, RHS_TYPE>::value
    )
    VectorN<TYPE, SIZE> operator+(const VectorN<RHS_TYPE, SIZE>& vect) const
    {
        VectorN<TYPE, SIZE> result;
        addVectors(*this, vect, &result);
        return result;
    }

    /**
     * \brief Negation operator.
     * \return negated vector
     */
    VectorN<TYPE, SIZE> operator-() const
    {
        VectorN<TYPE, SIZE> result(*this);
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
        VectorN<TYPE, SIZE> result;
        substractVectors(*this, vect, &result);
        return result;
    }

    /**
     * \brief Substraction operator.
     * \param vect vector to be subtracted
     * \return difference of the vectors
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value  && 
        std::is_arithmetic<RHS_TYPE>::value && 
        std::is_same<TYPE, RHS_TYPE>::value == false
    )
    auto operator-(const VectorN<RHS_TYPE, SIZE>& vect) const
    {
        VectorN<std::common_type_t<TYPE, RHS_TYPE>, SIZE> result;
        substractVectors(*this, vect, &result);
        return result;
    }


    /**
     * \brief Substraction operator.
     * \param vect vector to be subtracted
     * \return difference of the vectors
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value == false && 
        std::is_arithmetic<RHS_TYPE>::value == false &&
        std::is_same<TYPE, RHS_TYPE>::value == false &&
        units::traits::is_convertible_unit_t<TYPE, RHS_TYPE>::value
    )
    VectorN<TYPE, SIZE> operator-(const VectorN<RHS_TYPE, SIZE>& vect) const
    {
        VectorN<TYPE, SIZE> result;
        substractVectors(*this, vect, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     * \tparam TYPE_RHS right-hand side operand type
     * \param val value to be multiplied by
     * \return product of the vector multiplied by the value
     */
    template <typename RHS_TYPE>
    requires (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    auto operator*(const RHS_TYPE& val) const
    {
        VectorN<std::common_type_t<TYPE, RHS_TYPE>, SIZE> result;
        multiplyVectorByScalar(*this, val, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     * \tparam TYPE_RHS right-hand side operand type
     * \param val value to be multiplied by
     * \return product of the vector multiplied by the value
     */
    template <typename RHS_TYPE>
    requires (
        (units::traits::is_unit_t<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
        (std::is_arithmetic<TYPE>::value && units::traits::is_unit_t<RHS_TYPE>::value)
    )
    auto operator*(const RHS_TYPE& val) const
    {
        if constexpr (units::traits::is_unit_t<TYPE>::value)
        {
            VectorN<TYPE, SIZE> result;
            multiplyVectorByScalar(*this, val, &result);
            return result;
        }
        else
        {
            VectorN<RHS_TYPE, SIZE> result;
            multiplyVectorByScalar(*this, val, &result);
            return result;
        }

    }

    /**
     * \brief Multiplication by a scalar operator.
     * \tparam TYPE_RHS right-hand side operand type
     * \param val value to be multiplied by
     * \return product of the vector multiplied by the value
     */
    template <typename RHS_TYPE>
    requires (
        units::traits::is_unit_t<TYPE>::value && 
        units::traits::is_unit_t<RHS_TYPE>::value &&
        units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value == false
    )
    auto operator*(const RHS_TYPE& val) const
    {
        VectorN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                >
            >,
            SIZE
        > result;
        multiplyVectorByScalar(*this, val, &result);
        return result;
    }

    /**
     * \brief Dot product operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param vect right-hand side vector
     * \return dot product of the vectors
     */
    template <typename RHS_TYPE>
    requires (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    auto operator*(const VectorN<RHS_TYPE,SIZE>& vect) const
    {
        std::common_type_t<TYPE, RHS_TYPE> result;
        calculateDotProduct(*this, vect, &result);
        return result;
    }

    /**
     * \brief Dot product operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param vect right-hand side vector
     * \return dot product of the vectors
     */
    template <typename RHS_TYPE>
    requires (
        (units::traits::is_unit_t<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
        (std::is_arithmetic<TYPE>::value && units::traits::is_unit_t<RHS_TYPE>::value)
    )
    auto operator*(const VectorN<RHS_TYPE,SIZE>& vect) const
    {
        if constexpr (units::traits::is_unit_t<TYPE>::value)
        {
            TYPE result;
            calculateDotProduct(*this, vect, &result);
            return result;
        }
        else
        {
            RHS_TYPE result;
            calculateDotProduct(*this, vect, &result);
            return result;
        }
    }

    /**
     * \brief Dot product operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param vect right-hand side vector
     * \return dot product of the vectors
     */
    template <typename RHS_TYPE>
    requires (
        units::traits::is_unit_t<TYPE>::value && 
        units::traits::is_unit_t<RHS_TYPE>::value &&
        units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value == false
    )
    auto operator*(const VectorN<RHS_TYPE,SIZE>& vect) const
    {
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<TYPE>::unit_type,
                typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
            >
        > result;
        calculateDotProduct(*this, vect, &result);
        return result;
    }

    /**
     * \brief Division by a scalar operator.
     * \tparam RHS_TYPE type of the right-hand side value
     * \param val value to be divided by
     * \return vector divided by the value
     */
    template <typename RHS_TYPE>
    requires (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    auto operator/(const RHS_TYPE& val) const
    {
        VectorN<std::common_type_t<TYPE, RHS_TYPE>, SIZE> result;
        multiplyVectorByScalar(*this, 1.0 / val, &result);
        return result;
    }

    /**
     * \brief Division by a scalar operator.
     * \tparam RHS_TYPE type of the right-hand side value
     * \param val value to be divided by
     * \return vector divided by the value
     */
    template <typename RHS_TYPE>
    requires (
        (std::is_arithmetic<TYPE>::value && units::traits::is_unit_t<RHS_TYPE>::value) ||
        (units::traits::is_unit_t<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    )
    auto operator/(const RHS_TYPE& val) const
    {
        if constexpr (units::traits::is_unit_t<TYPE>::value)
        {
            VectorN<TYPE, SIZE> result;
            multiplyVectorByScalar(*this, 1.0 / val, &result);
            return result;
        }
        else
        {
            VectorN<
                units::unit_t<
                    units::inverse<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type>
                >,
                SIZE
            > result;
            multiplyVectorByScalar(*this, 1.0 / val, &result);
            return result;
        }
    }

    /**
     * \brief Division by a scalar operator.
     * \tparam RHS_TYPE type of the right-hand side value
     * \param val value to be divided by
     * \return vector divided by the value
     */
    template <typename RHS_TYPE>
    requires (units::traits::is_unit_t<TYPE>::value && units::traits::is_unit_t<RHS_TYPE>::value)
    auto operator/(const RHS_TYPE& val) const
    {
        VectorN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    units::inverse<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type>
                >
            >,
            SIZE
        > result;
        multiplyVectorByScalar(*this, 1.0 / val, &result);
        return result;
    }

    /**
     * \brief Assignment operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param vect right-hand side vector
     * \return reference to the updated vector
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value && 
        std::is_arithmetic<RHS_TYPE>::value &&
        std::is_same<TYPE, RHS_TYPE>::value == false
    )
    VectorN<TYPE,SIZE>& operator=(const VectorN<RHS_TYPE, SIZE>& vect)
    {
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            _elements[i] = static_cast<TYPE>(vect(i));
        }

        return *this;
    }

    /**
     * \brief Assignment operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param vect right-hand side vector
     * \return reference to the updated vector
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value == false &&
        std::is_arithmetic<RHS_TYPE>::value == false &&
        std::is_same<TYPE, RHS_TYPE>::value == false &&
        units::traits::is_convertible_unit_t<TYPE, RHS_TYPE>::value
    )
    VectorN& operator=(const VectorN<RHS_TYPE, SIZE>& vect)
    {
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            _elements[i] = vect(i);
        }

        return *this;
    }

    /**
     * \brief Unary addition operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param vect vector to be added
     * \return reference to the updated vector
     */
    template <typename RHS_TYPE>
    requires (
        (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
        units::traits::is_convertible_unit_t<TYPE, RHS_TYPE>::value
    )
    VectorN<TYPE, SIZE>& operator+=(const VectorN<RHS_TYPE, SIZE>& vect)
    {
        addVectors(*this, vect, this);
        return *this;
    }

    /**
     * \brief Unary subtraction operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param vect vector to be subtracted
     * \return reference to the updated vector
     */
    template <typename RHS_TYPE>
    requires (
        (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
        units::traits::is_convertible_unit_t<TYPE, RHS_TYPE>::value
    )
    VectorN<TYPE, SIZE>& operator-=(const VectorN<RHS_TYPE, SIZE>& vect)
    {
        substractVectors(*this, vect, this);
        return *this;
    }

    /**
     * \brief Unary multiplication operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param val value to be multiplied by
     * \return reference to the updated vector
     */
    template <typename RHS_TYPE>
    requires std::is_arithmetic<RHS_TYPE>::value
    VectorN<TYPE, SIZE>& operator*=(RHS_TYPE val)
    {
        *this = (*this) * val;
        return *this;
    }

    /**
     * \brief Unary division operator.
     * \param val value to be divided by
     * \return reference to the updated vector
     */
    template <typename RHS_TYPE>
    requires std::is_arithmetic<RHS_TYPE>::value
    VectorN<TYPE, SIZE>& operator/=(RHS_TYPE val)
    {
        *this = (*this) / val;
        return *this;
    }

    /**
     * \brief Equality operator.
     * \param vect vector to be compared with
     * \return true if the vectors are equal, false otherwise
     */
    bool operator==(const VectorN<TYPE, SIZE>& vect) const
    {
        bool result = true;
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            result = result && (_elements[i] == vect._elements[i]);
        }
        return result;
    }

    /**
     * \brief Inequality operator.
     * \param vect vector to be compared with
     * \return true if the vectors are not equal, false otherwise
     */
    bool operator!=(const VectorN<TYPE, SIZE>& vect) const
    {
        return !(*this == vect);
    }

protected:

    TYPE _elements[SIZE] = { TYPE{0} }; ///< vector elements
};

/**
 * \brief Adds two vectors.
 * \tparam LHS_TYPE type of the left-hand side vector elements
 * \tparam RHS_TYPE type of the right-hand side vector elements
 * \tparam RESULT_TYPE type of the result vector elements
 * \param lhs left-hand-side vector
 * \param rhs right-hand-side vector
 * \param result output vector
 */
template <typename LHS_TYPE, typename RHS_TYPE, typename RESULT_TYPE, unsigned int SIZE>
requires (
    (std::is_arithmetic<LHS_TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
    units::traits::is_convertible_unit_t<LHS_TYPE, RHS_TYPE>::value
)
void addVectors(
    const VectorN<LHS_TYPE, SIZE>& lhs, 
    const VectorN<RHS_TYPE, SIZE>& rhs, 
    VectorN<RESULT_TYPE, SIZE>* result
)
{
    for (unsigned int i = 0; i < SIZE; ++i)
    {
        (*result)(i) = lhs(i) + rhs(i);
    }
}

/**
 * \brief Subtracts two vectors.
 * \tparam LHS_TYPE type of the left-hand side vector elements
 * \tparam RHS_TYPE type of the right-hand side vector elements
 * \tparam RESULT_TYPE type of the result vector elements
 * \param lhs left-hand-side vector
 * \param rhs right-hand-side vector
 * \param result output result vector
 */
template <typename LHS_TYPE, typename RHS_TYPE, typename RESULT_TYPE, unsigned int SIZE>
requires (
    (std::is_arithmetic<LHS_TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
    units::traits::is_convertible_unit_t<LHS_TYPE, RHS_TYPE>::value
)
void substractVectors(
    const VectorN<LHS_TYPE, SIZE>& lhs, 
    const VectorN<RHS_TYPE, SIZE>& rhs, 
    VectorN<RESULT_TYPE, SIZE>* result
)
{
    for (unsigned int i = 0; i < SIZE; ++i)
    {
        (*result)(i) = lhs(i) - rhs(i);
    }
}

/**
 * \brief Multiplies a vector by a scalar.
 * \tparam VECTOR_TYPE type of the vector elements
 * \tparam SCALAR_TYPE type of the scalar
 * \tparam RESULT_TYPE type of the result vector elements
 * \param vect vector
 * \param val scalar to multiply by
 * \param result output result vector
 */
template <typename VECTOR_TYPE, typename SCALAR_TYPE, typename RESULT_TYPE, unsigned int SIZE>
void multiplyVectorByScalar(
    const VectorN<VECTOR_TYPE, SIZE>& vect, 
    const SCALAR_TYPE& val, 
    VectorN<RESULT_TYPE, SIZE>* result
)
{
    for (unsigned int i = 0; i < SIZE; ++i)
    {
        (*result)(i) = vect(i) * val;
    }
}

/**
 * \brief Dot product calculation algorithm.
 * \tparam LHS_TYPE type of the left-hand side vector elements
 * \tparam RHS_TYPE type of the right-hand side vector elements
 * \tparam RESULT_TYPE type of the result
 * \param lhs left-hand-side vector
 * \param rhs right-hand-side vector
 * \param result output result
 */
template <typename LHS_TYPE, typename RHS_TYPE, typename RESULT_TYPE, unsigned int SIZE>
void calculateDotProduct(
    const VectorN<LHS_TYPE, SIZE>& lhs, 
    const VectorN<RHS_TYPE, SIZE>& rhs, 
    RESULT_TYPE* result
)
{
    *result = RESULT_TYPE{0};
    for (unsigned int i = 0; i < SIZE; ++i)
    {
        *result += lhs(i) * rhs(i);
    }
}

/**
 * \brief Normalized vector calculation algorithm.
 * \tparam TYPE type of the vector elements
 * \tparam SIZE size of the vector
 * \param vect input vector
 * \param result output vector
 */
template <typename TYPE, unsigned int SIZE>
void calculateNormalized(const VectorN<TYPE, SIZE>& vect, VectorN<double, SIZE>* result)
{
    double length = static_cast<double>(vect.getLength());
    if (length > 0.0)
    {
        double length_inv = 1.0 / length;
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            (*result)(i) = static_cast<double>(vect(i)) * length_inv;
        }
    }
}

/**
 * \brief Multiplication operator.
 *
 * This is an operator for multiplying a scalar by a vector, which is commutative.
 * 
 * \tparam LHS_TYPE type of the left-hand side scalar
 * \tparam RHS_TYPE type of the right-hand side vector elements
 * \tparam SIZE size of the vector
 * \param val value to be multiplied by
 * \param vect vector to be multiplied
 * \return product of the vector multiplied by the value
 */
template <typename LHS_TYPE, typename RHS_TYPE, unsigned int SIZE>
requires (
    std::is_arithmetic<LHS_TYPE>::value ||
    units::traits::is_unit_t<LHS_TYPE>::value
)
auto operator*(LHS_TYPE val, const VectorN<RHS_TYPE, SIZE>& vect)
{
    return vect * val;
}

} // namespace mc

#endif // MCUTILS_MATH_VECTORN_H_
