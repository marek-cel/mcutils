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
#ifndef MCUTILS_MATH_MATRIXMXN_H_
#define MCUTILS_MATH_MATRIXMXN_H_

#ifndef MCUTILS_MATH_MATRIX_H_
#   error "Do not include this file directly. Include <mcutils/math/Matrix.h> instead."
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
#include <mcutils/math/Vector.h>
#include <mcutils/misc/Check.h>
#include <mcutils/misc/StringUtils.h>

using namespace units::math;

namespace mc {

/**
 * \brief A template class representing a rectangular matrix with fixed dimensions.
 *
 * This class provides a variety of matrix operations, including addition, subtraction,
 * scalar multiplication, matrix multiplication, transposition, and more. It supports
 * both dimensionless and unit-based types, with specializations for angular velocity
 * and angular acceleration. The matrix elements are stored in a row-major order.
 *
 * \tparam TYPE matrix element type
 * \tparam ROWS matrix rows count
 * \tparam COLS matrix columns count
 */
template <typename TYPE, unsigned int ROWS, unsigned int COLS>
class MatrixMxN
{
public:

    static constexpr unsigned int kRows = ROWS;        ///< number of rows
    static constexpr unsigned int kCols = COLS;        ///< number of columns
    static constexpr unsigned int kSize = ROWS * COLS; ///< matrix size

    // LCOV_EXCL_START
    MatrixMxN() = default;
    MatrixMxN(const MatrixMxN&) = default;
    MatrixMxN(MatrixMxN&&) = default;
    virtual ~MatrixMxN() = default;
    MatrixMxN& operator=(const MatrixMxN&) = default;
    MatrixMxN& operator=(MatrixMxN&&) = default;
    // LCOV_EXCL_STOP

    /**
     * \brief Fills all matrix elements with the given value.
     * \param val given value to fill all matrix elements
     */
    void fill(TYPE val)
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] = val;
        }
    }

    /** \return "true" if all elements are valid */
    bool isValid() const
    {
        return misc::isValid(_elements, kSize);
    }


    /** \brief Gets transposed matrix. */
    MatrixMxN<TYPE, COLS, ROWS> getTransposed() const
    {
        MatrixMxN<TYPE, COLS, ROWS> result;
        transposeMatrix(*this, &result);
        return result;
    }

    /**
     * \brief Gets a std::array of matrix elements.
     * 
     * Elements index should match following scheme:
     * i = i_row * n_col + i_col
     * where:
     * i - array index,
     * i_row - row index,
     * i_col - column index,
     * n_col - number of columns
     * 
     * \return std::array<TYPE, ROWS * COLS> of matrix elements
     */
    std::array<TYPE, ROWS * COLS> getStdArray() const
    {
        std::array<TYPE, kSize> elements;
        std::copy(_elements, _elements + kSize, elements.begin());
        return elements;
    }

    /**
     * \brief Gets a std::vector of matrix elements.
     *
     * Elements index should match following scheme:
     * i = i_row * n_col + i_col
     * where:
     * i - array index,
     * i_row - row index,
     * i_col - column index,
     * n_col - number of columns
     *
     * \return vector of matrix elements
     */
    std::vector<TYPE> getStdVector() const
    {
        std::vector<TYPE> elements(kSize);
        std::copy(_elements, _elements + kSize, elements.begin());
        return elements;
    }

    /**
     * \brief Sets matrix elements from a std::array.
     *
     * Elements index should match following scheme:
     * i = i_row * n_col + i_col
     * where:
     * i - array index,
     * i_row - row index,
     * i_col - column index,
     * n_col - number of columns
     *
     * \param elements input std::array of matrix elements
     */
    inline void setFromStdArray(const std::array<TYPE, kSize>& elements)
    {
        std::copy(elements.begin(), elements.end(), _elements);
    }

    /**
     * \brief Sets matrix elements from a std::vector.
     *
     * Elements index should match following scheme:
     * i = i_row * n_col + i_col
     * where:
     * i - array index,
     * i_row - row index,
     * i_col - column index,
     * n_col - number of columns
     *
     * \param elements input std::vector of matrix elements
     */
    inline void setFromStdVector(const std::vector<TYPE>& elements)
    {
        assert(elements.size() == kSize);
        std::copy(elements.begin(), elements.end(), _elements);
    }

    /**
     * \brief Sets matrix elements from string.
     *
     * Values in the given string should be separated with whitespaces.
     *
     * \param str given string
     */
    void setFromString(const char* str)
    {
        if (kSize > 0)
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

            if ( valid ) setFromStdVector(elements);
        }
    }

    /** \brief Swaps matrix rows. */
    void swapRows(unsigned int row1, unsigned int row2)
    {
        if (row1 < kRows && row2 < kRows)
        {
            for (unsigned int c = 0; c < kCols; ++c)
            {
                std::swap(_elements[row1 * kCols + c], _elements[row2 * kCols + c]);
            }
        }
    }

    /** \brief Returns string representation of the matrix. */
    std::string toString() const
    {
        std::stringstream ss;

        for (unsigned int r = 0; r < kRows; ++r)
        {
            for (unsigned int c = 0; c < kCols; ++c)
            {
                if (r > 0 && c == 0)
                    ss << "\n";
                else if (r > 0 || c > 0)
                    ss << "\t";

                ss << _elements[r * kCols + c];
            }
        }

        return ss.str();
    }

    /** \brief Negates matrix. */
    void negate()
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] = -_elements[i];
        }
    }

    /** \brief Sets all matrix elements to zero. */
    void zeroize()
    {
        fill(TYPE{0});
    }

    /**
     * \brief Casting operator.
     *  Converts the matrix to another type.
     */
    template <class NEW_TYPE>
    requires (
        std::is_same<TYPE, NEW_TYPE>::value == false &&
        (std::is_arithmetic<NEW_TYPE>::value || units::traits::is_convertible_unit_t<NEW_TYPE, TYPE>::value)
    )
    operator MatrixMxN<NEW_TYPE, ROWS, COLS>() const
    {
        MatrixMxN<NEW_TYPE, kRows, kCols> result;
        for (unsigned int r = 0; r < kRows; ++r)
        {
            for (unsigned int c = 0; c < kCols; ++c)
            {
                result(r, c) = static_cast<NEW_TYPE>(_elements[r * kCols + c]);;
            }
        }
        return result;
    }

    /**
     * \brief Elements accessor.
     *
     * Please notice that this operator is NOT bound-checked.
     *
     * \param row element row number
     * \param col element column number
     * \return element value
     */
    inline TYPE operator()(unsigned int row, unsigned int col) const
    {
        return _elements[row * kCols + col];
    }

    /**
     * \brief Items accessor.
     * 
     * Please notice that this operator is NOT bounds-checked.
     * 
     * \param index element index
     * \return matrix element at given index
     */
    inline TYPE operator()(unsigned int index) const
    {
        return _elements[index];
    }

    /**
     * \brief Elements accessor.
     *
     * Please notice that this operator is NOT bound-checked.
     *
     * \param row element row number
     * \param col element column number
     */
    inline TYPE& operator()(unsigned int row, unsigned int col)
    {
        return _elements[row * kCols + col];
    }

    /**
     * \brief Items accessor.
     * 
     * Please notice that this operator is NOT bounds-checked.
     * 
     * \param index element index
     * \return matrix element at given index
     */
    inline TYPE& operator()(unsigned int index)
    {
        return _elements[index];
    }

    /**
     * \brief Addition operator.
     * \param matrix right-hand side matrix
     * \return sum of the matrices
     */
    MatrixMxN<TYPE, ROWS, COLS> operator+(const MatrixMxN<TYPE, ROWS, COLS>& matrix) const
    {
        MatrixMxN<TYPE, kRows, kCols> result(*this);
        result.add(matrix);
        return result;
    }

    /**
     * \brief Addition operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \param matrix right-hand side matrix
     * \return sum of the matrices
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value  && 
        std::is_arithmetic<RHS_TYPE>::value && 
        std::is_same<TYPE, RHS_TYPE>::value == false
    )
    MatrixMxN<TYPE, ROWS, COLS> operator+(const MatrixMxN<RHS_TYPE, ROWS, COLS>& matrix) const
    {
        // MatrixMxN<TYPE, kRows, kCols> result(*this);
        // result.add(matrix);
        // return result;
    }

    /** \brief Negation operator. */
    MatrixMxN<TYPE, ROWS, COLS> operator-() const
    {
        MatrixMxN<TYPE, kRows, kCols> result(*this);
        result.negate();
        return result;
    }

    /** \brief Subtraction operator. */
    MatrixMxN<TYPE, ROWS, COLS> operator-(const MatrixMxN<TYPE, ROWS, COLS>& matrix) const
    {
        MatrixMxN<TYPE, kRows, kCols> result(*this);
        result.subtract(matrix);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     * So operators for angular velocity and angular acceleration are defined
     * as specializations of this template.
     *
     * This template is enabled when TYPE and TYPE2 are both units, but TYPE2 is not
     * angular velocity or angular acceleration.
     */
    template <class TYPE2, typename std::enable_if<
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator*(TYPE2 val) const
    {
        MatrixMxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<TYPE2>::unit_type
                >
            >,
            ROWS, COLS
        > result;
        multiplyMatrixByValue(*this, val, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     *
     * This is a specialization for the case when the value is angular velocity.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This specialization is enabled when TYPE is a unit and TYPE2 is angular velocity.
     *
     * Example: calculating angular momentum from inertia and angular velocity.
     * L = I * omega
     *
     * \tparam TYPE2 RHS operand type
     * \param val value to be multiplied by
     * \return product of the matrix multiplied by the value
     */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_convertible_unit_t<
            TYPE2, units::angular_velocity::radians_per_second_t
        >::value, int>::type = 0
    >
    auto operator*(TYPE2 val) const
    {
        units::angular_velocity::radians_per_second_t temp_rad_per_s = val;
        units::inverted::per_second_t temp = units::inverted::per_second_t{ temp_rad_per_s() };

        MatrixMxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::inverted::per_second_t>::unit_type
                >
            >,
            ROWS, COLS
        > result;
        multiplyMatrixByValue(*this, temp, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     *
     * This is a specialization for the case when the value is angular acceleration.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This specialization is enabled when TYPE is a unit and TYPE2 is angular acceleration.
     *
     * Example: calculating torque from inertia and angular acceleration.
     * T = I * alpha
     *
     * \tparam TYPE2 RHS operand type
     * \param value value to be multiplied by
     * \return product of the matrix multiplied by the value
     */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_convertible_unit_t<
            TYPE2, units::angular_acceleration::radians_per_second_squared_t
        >::value, int>::type = 0
    >
    auto operator*(TYPE2 value) const
    {
        units::angular_acceleration::radians_per_second_squared_t temp_rad_per_s_sq = value;
        units::inverted::per_second_squared_t temp = units::inverted::per_second_squared_t{ temp_rad_per_s_sq() };

        MatrixMxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::inverted::per_second_squared_t>::unit_type
                >
            >,
            ROWS, COLS
        > result;
        multiplyMatrixByValue(*this, temp, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     *
     * This is a specialization for the case when the matrix is dimensionless.
     */
    template <class TYPE2, typename std::enable_if<
        !units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    MatrixMxN<TYPE2, ROWS, COLS> operator*(TYPE2 value) const
    {
        MatrixMxN<TYPE2, ROWS, COLS> result;
        multiplyMatrixByValue(*this, value, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     *
     * This is a specialization for the case when the value is dimensionless.
     */
    MatrixMxN<TYPE, ROWS, COLS> operator*(double val) const
    {
        MatrixMxN<TYPE, ROWS, COLS> result;
        multiplyMatrixByValue(*this, val, &result);
        return result;
    }

    /**
     * \brief Multiplication operator by a vector.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     * So operators for angular velocity and angular acceleration are defined
     * as specializations of this template.
     * This template is enabled when TYPE and TYPE2 are both units, but TYPE2 is not
     * angular velocity or angular acceleration.
     */
    template <class TYPE2, typename std::enable_if<
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator*(const VectorN<TYPE2, ROWS>& vect) const
    {
        VectorN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<TYPE2>::unit_type
                >
            >,
            ROWS
        > result;
        multiplyMatrixByVector(*this, vect, &result);
        return result;
    }

    /**
     * \brief Multiplication operator by a vector.
     *
     * This is a specialization for the case when the value is angular velocity.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This specialization is enabled when TYPE is a unit and TYPE2 is angular velocity.
     *
     * Example: calculating angular momentum from inertia and angular velocity.
     * L = I * omega
     *
     * \tparam TYPE2 RHS operand type
     * \param value value to be multiplied by
     * \return product of the matrix multiplied by the value
     */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_convertible_unit_t<
            TYPE2, units::angular_velocity::radians_per_second_t
        >::value, int>::type = 0
    >
    auto operator*(const VectorN<TYPE2, ROWS>& vect) const
    {
        VectorN<units::angular_velocity::radians_per_second_t, ROWS> temp_rad_per_s = vect;
        VectorN<units::inverted::per_second_t, ROWS> temp;
        for (unsigned int i = 0; i < ROWS; ++i)
        {
            temp(i) = units::inverted::per_second_t{ temp_rad_per_s(i)() };
        }

        VectorN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::inverted::per_second_t>::unit_type
                >
            >,
            ROWS
        > result;
        multiplyMatrixByVector(*this, temp, &result);
        return result;
    }

    /**
     * \brief Multiplication operator by a vector.
     *
     * This is a specialization for the case when the value is angular acceleration.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This specialization is enabled when TYPE is a unit and TYPE2 is angular acceleration.
     *
     * Example: calculating torque from inertia and angular acceleration.
     * T = I * alpha
     *
     * \tparam TYPE2 RHS operand type
     * \param value value to be multiplied by
     * \return product of the matrix multiplied by the value
     */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_convertible_unit_t<
            TYPE2, units::angular_acceleration::radians_per_second_squared_t
        >::value, int>::type = 0
    >
    auto operator*(const VectorN<TYPE2, ROWS>& vect) const
    {
        VectorN<units::angular_acceleration::radians_per_second_squared_t, ROWS> temp_rad_per_s = vect;
        VectorN<units::inverted::per_second_squared_t, ROWS> temp;
        for (unsigned int i = 0; i < ROWS; ++i)
        {
            temp(i) = units::inverted::per_second_squared_t{ temp_rad_per_s(i)() };
        }

        VectorN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::inverted::per_second_squared_t>::unit_type
                >
            >,
            ROWS
        > result;
        multiplyMatrixByVector(*this, temp, &result);
        return result;
    }

    /**
     * \brief Multiplication operator by a vector.
     *
     * This is a specialization for the case when the vector is dimensionless.
     */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        !units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    VectorN<TYPE,ROWS> operator*(const VectorN<TYPE2, ROWS>& vect)
    {
        VectorN<TYPE,ROWS> result;
        multiplyMatrixByVector(*this, vect, &result);
        return result;
    }

    /**
     * \brief Multiplication operator by a vector.
     *
     * This is a specialization for the case when the matrix is dimensionless.
     */
    template <class TYPE2, typename std::enable_if<
        !units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    VectorN<TYPE2,ROWS> operator*(const VectorN<TYPE2, ROWS>& vect)
    {
        VectorN<TYPE2,ROWS> result;
        multiplyMatrixByVector(*this, vect, &result);
        return result;
    }

    /**
     * \brief Multiplication operator by a vector.
     *
     * This is a specialization for the case when both matrix and vector are dimensionless.
     */
    template <class TYPE2, typename std::enable_if<
        !units::traits::is_unit_t<TYPE>::value
        &&
        !units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    VectorN<double,ROWS> operator*(const VectorN<TYPE2, ROWS>& vect)
    {
        VectorN<double,ROWS> result;
        multiplyMatrixByVector(*this, vect, &result);
        return result;
    }

    /** \brief Multiplies by a matrix by a matrix. */
    template <class TYPE2, unsigned int P, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator*(const MatrixMxN<TYPE2, COLS, P>& matrix)
    {
        MatrixMxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<TYPE2>::unit_type
                >
            >,
            ROWS, P
        > result;
        multiplyMatrixByMatrix(*this, matrix, &result);
        return result;
    }

    /**
     * \brief Multiplies by a matrix by a matrix.
     *
     * This is a specialization for the case when the first matrix is dimensionless.
     */
    template <class TYPE2, unsigned int P, typename std::enable_if<
        !units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    MatrixMxN<TYPE2,ROWS,P> operator*(const MatrixMxN<TYPE2, COLS, P>& matrix)
    {
        MatrixMxN<TYPE2,ROWS,P> result;
        multiplyMatrixByMatrix(*this, matrix, &result);
        return result;
    }

    /**
     * \brief Multiplies by a matrix by a matrix.
     *
     * This is a specialization for the case when the second matrix is dimensionless.
     */
    template <class TYPE2, unsigned int P, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        !units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    MatrixMxN<TYPE,ROWS,P> operator*(const MatrixMxN<TYPE2, COLS, P>& matrix)
    {
        MatrixMxN<TYPE,ROWS,P> result;
        multiplyMatrixByMatrix(*this, matrix, &result);
        return result;
    }

    /**
     * \brief Multiplies by a matrix by a matrix.
     *
     * This is a specialization for the case when both matrices are dimensionless.
     */
    template <class TYPE2, unsigned int P, typename std::enable_if<
        !units::traits::is_unit_t<TYPE>::value
        &&
        !units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    MatrixMxN<double,ROWS,P> operator*(const MatrixMxN<TYPE2, COLS, P>& matrix)
    {
        MatrixMxN<double,ROWS,P> result;
        multiplyMatrixByMatrix(*this, matrix, &result);
        return result;
    }

    /**
     * \brief Division by scalar operator.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     * So operators for angular velocity and angular acceleration are defined
     * as specializations of this template.
     *
     * This template is enabled when TYPE and TYPE2 are both units, but TYPE2 is not angular velocity
     * or angular acceleration.
     *
     * \tparam TYPE2 RHS operand type
     * \param value value to divide the matrix by
     * \return result of the division
     */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator/(TYPE2 value) const
    {
        MatrixMxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    units::inverse<typename units::traits::unit_t_traits<TYPE2>::unit_type>
                >
            >,
            ROWS, COLS
        > result;
        multiplyMatrixByValue(*this, 1.0 / value, &result);
        return result;
    }

    /**
     * \brief Division operator.
     *
     * This is a specialization for the case when the matrix is dimensionless.
     */
    template <class TYPE2, typename std::enable_if<
        !units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator/(TYPE2 value) const
    {
        MatrixMxN<
            units::unit_t<
                units::compound_unit<
                    units::inverse<typename units::traits::unit_t_traits<TYPE2>::unit_type>
                >
            >,
            ROWS, COLS
        > result;
        multiplyMatrixByValue(*this, 1.0 / value, &result);
        return result;
    }

    /**
     * \brief Division operator.
     *
     * This is a specialization for the case when the value is dimensionless.
     */
    MatrixMxN<TYPE, ROWS, COLS> operator/(double value) const
    {
        MatrixMxN<TYPE, ROWS, COLS> result;
        multiplyMatrixByValue(*this, 1.0 / value, &result);
        return result;
    }

    /** \brief Unary addition operator. */
    MatrixMxN<TYPE, ROWS, COLS>& operator+=(const MatrixMxN<TYPE, ROWS, COLS>& matrix)
    {
        add(matrix);
        return *this;
    }

    /** \brief Unary subtraction operator. */
    MatrixMxN<TYPE, ROWS, COLS>& operator-=(const MatrixMxN<TYPE, ROWS, COLS>& matrix)
    {
        subtract(matrix);
        return *this;
    }

    /** \brief Unary multiplication operator (by number). */
    MatrixMxN<TYPE, ROWS, COLS>& operator*=(double value)
    {
        *this = (*this) * value;
        return *this;
    }

    /** \brief Unary division operator (by number). */
    MatrixMxN<TYPE, ROWS, COLS>& operator/=(double value)
    {
        *this = (*this) / value;
        return *this;
    }

    /** \brief Equality operator. */
    bool operator==(const MatrixMxN<TYPE, ROWS, COLS>& matrix) const
    {
        bool result = true;
        for (unsigned int i = 0; i < kSize; ++i)
        {
            result = result && (_elements[i] == matrix._elements[i]);
        }
        return result;
    }

    /** \brief Inequality operator. */
    bool operator!=(const MatrixMxN<TYPE, ROWS, COLS>& matrix) const
    {
        return !(*this == matrix);
    }

protected:

    TYPE _elements[kSize] = { TYPE{0} };    ///< matrix elements

    /** \brief Multiplication a matrix by a value algorithm. */
    template <typename TYPE1, typename TYPE2, typename TYPE3>
    void multiplyMatrixByValue(const MatrixMxN<TYPE1, ROWS, COLS>& matrix, const TYPE2& value,
                               MatrixMxN<TYPE3, ROWS, COLS>* result) const
    {
        for (unsigned int r = 0; r < ROWS; ++r)
        {
            for (unsigned int c = 0; c < COLS; ++c)
            {
                (*result)(r, c) = matrix(r, c) * value;
            }
        }
    }

    /** \brief Multiplication a matrix by a matrix algorithm. */
    template <typename TYPE1, typename TYPE2, typename TYPE3, unsigned int M, unsigned int N, unsigned int P>
    void multiplyMatrixByMatrix(const MatrixMxN<TYPE1, M, N>& m1, const MatrixMxN<TYPE2, N, P>& m2,
                                MatrixMxN<TYPE3,M,P>* result) const
    {
        for (unsigned int i = 0; i < M; ++i)
        {
            for (unsigned int j = 0; j < P; ++j)
            {
                (*result)(i, j) = TYPE3{0};
                for (unsigned int k = 0; k < N; ++k)
                {
                    (*result)(i, j) += m1(i, k) * m2(k, j);
                }
            }
        }
    }

    /** \brief Multiplication a matrix by a vector algorithm. */
    template <typename TYPE1, typename TYPE2, typename TYPE3>
    void multiplyMatrixByVector(const MatrixMxN<TYPE1, ROWS, COLS>& matrix, const VectorN<TYPE2, ROWS>& vect,
                                VectorN<TYPE3, ROWS>* result) const
    {
        for (unsigned int r = 0; r < ROWS; ++r)
        {
            for (unsigned int c = 0; c < COLS; ++c)
            {
                (*result)(r) += matrix(r,c) * vect(c);
            }
        }
    }

    /** \brief Matrix transposition algorithm. */
    void transposeMatrix(const MatrixMxN<TYPE, ROWS, COLS> matrix, MatrixMxN<TYPE, COLS, ROWS>* result) const
    {
        for (unsigned int r = 0; r < kRows; ++r)
        {
            for (unsigned int c = 0; c < kCols; ++c)
            {
                (*result)(c, r) = matrix(r, c);
            }
        }
    }
};

/** 
 * \brief Adds two matrices.
 * \tparam LHS_TYPE type of the left-hand side matrix elements
 * \tparam RHS_TYPE type of the right-hand side matrix elements
 * \tparam RESULT_TYPE type of the result matrix elements
 * \tparam ROWS number of matrix rows
 * \tparam COLS number of matrix columns
 * \param lhs left-hand side matrix
 * \param rhs right-hand side matrix
 * \param result pointer to the result matrix
 */
template <typename LHS_TYPE, typename RHS_TYPE, typename RESULT_TYPE, unsigned int ROWS, unsigned int COLS>
requires (
    (std::is_arithmetic<LHS_TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
    units::traits::is_convertible_unit_t<LHS_TYPE, RHS_TYPE>::value
)
void addMatrices(
    const MatrixMxN<LHS_TYPE, ROWS, COLS>& lhs,
    const MatrixMxN<RHS_TYPE, ROWS, COLS>& rhs,
    MatrixMxN<RESULT_TYPE, ROWS, COLS>* result
)
{
    for (unsigned int i = 0; i < ROWS * COLS; ++i)
    {
        (*result)(i) = lhs(i) + rhs(i);
    }
}

/** 
 * \brief Subtracts two matrices.
 * \tparam LHS_TYPE type of the left-hand side matrix elements
 * \tparam RHS_TYPE type of the right-hand side matrix elements
 * \tparam RESULT_TYPE type of the result matrix elements
 * \tparam ROWS number of matrix rows
 * \tparam COLS number of matrix columns
 * \param lhs left-hand side matrix
 * \param rhs right-hand side matrix
 * \param result pointer to the result matrix
 */
template <typename LHS_TYPE, typename RHS_TYPE, typename RESULT_TYPE, unsigned int ROWS, unsigned int COLS>
requires (
    (std::is_arithmetic<LHS_TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
    units::traits::is_convertible_unit_t<LHS_TYPE, RHS_TYPE>::value
)
void subtractMatrices(
    const MatrixMxN<LHS_TYPE, ROWS, COLS>& lhs,
    const MatrixMxN<RHS_TYPE, ROWS, COLS>& rhs,
    MatrixMxN<RESULT_TYPE, ROWS, COLS>* result
)
{
    for (unsigned int i = 0; i < ROWS * COLS; ++i)
    {
        (*result)(i) = lhs(i) - rhs(i);
    }
}

/** \brief Multiplication operator. */
template <typename TYPE1, class TYPE2, unsigned int ROWS, unsigned int COLS, typename std::enable_if<
    units::traits::is_unit_t<TYPE1>::value, int>::type = 0
>
auto operator*(TYPE1 value, const MatrixMxN<TYPE2,ROWS,COLS>& matrix)
{
    return matrix * value;
}

/**
 * \brief Multiplication operator.
 *
 * This is a specialization for the case when the value is a number.
 */
template<typename TYPE, unsigned int ROWS, unsigned int COLS>
MatrixMxN<TYPE,ROWS,COLS> operator*(double value, const MatrixMxN<TYPE,ROWS,COLS>& matrix)
{
    return matrix * value;
}

} // namespace mc

#endif // MCUTILS_MATH_MATRIXMXN_H_