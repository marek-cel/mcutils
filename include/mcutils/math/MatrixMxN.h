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
     * \brief Converting constructor.
     * 
     * This template is enabled when TYPE and TYPE2 are convertible units.
     * 
     * \tparam TYPE2 type of the other matrix elements
     * \param mat other matrix
     */
    template <typename TYPE2>
    requires (
        std::is_arithmetic<TYPE>::value == false && 
        std::is_arithmetic<TYPE2>::value == false &&
        std::is_same<TYPE, TYPE2>::value == false &&
        units::traits::is_convertible_unit_t<TYPE, TYPE2>::value
    )
    MatrixMxN(const MatrixMxN<TYPE2, ROWS, COLS>& mat)
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] = mat(i);
        }
    }

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
        return mc::isValid(_elements, kSize);
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
                valid &= mc::isValid(temp);
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
     * \tparam NEW_TYPE type of the new matrix elements
     * \return converted matrix
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
     * \param matrix matrix to be added
     * \return sum of the matrices
     */
    MatrixMxN<TYPE, ROWS, COLS> operator+(const MatrixMxN<TYPE, ROWS, COLS>& mat) const
    {
        MatrixMxN<TYPE, kRows, kCols> result;
        addMatrices(*this, mat, &result);
        return result;
    }

    /**
     * \brief Addition operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \param mat matrix to be added
     * \return sum of the matrices
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value  && 
        std::is_arithmetic<RHS_TYPE>::value && 
        std::is_same<TYPE, RHS_TYPE>::value == false
    )
    auto operator+(const MatrixMxN<RHS_TYPE, ROWS, COLS>& mat) const
    {
        MatrixMxN<std::common_type_t<TYPE, RHS_TYPE>, kRows, kCols> result;
        addMatrices(*this, mat, &result);
        return result;
    }

    /**
     * \brief Addition operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \param mat matrix to be added
     * \return sum of the matrices
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value == false && 
        std::is_arithmetic<RHS_TYPE>::value == false &&
        std::is_same<TYPE, RHS_TYPE>::value == false &&
        units::traits::is_convertible_unit_t<TYPE, RHS_TYPE>::value
    )
    auto operator+(const MatrixMxN<RHS_TYPE, ROWS, COLS>& mat) const
    {
        MatrixMxN<TYPE, kRows, kCols> result;
        addMatrices(*this, mat, &result);
        return result;
    }

    /** 
     * \brief Negation operator.
     * \return negated matrix
     */
    MatrixMxN<TYPE, ROWS, COLS> operator-() const
    {
        MatrixMxN<TYPE, kRows, kCols> result(*this);
        result.negate();
        return result;
    }

    /** 
     * \brief Subtraction operator.
     * \param mat matrix to be subtracted
     * \return difference of the matrices
     */
    MatrixMxN<TYPE, ROWS, COLS> operator-(const MatrixMxN<TYPE, ROWS, COLS>& mat) const
    {
        MatrixMxN<TYPE, kRows, kCols> result;
        subtractMatrices(*this, mat, &result);
        return result;
    }

    /** 
     * \brief Subtraction operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \param mat matrix to be subtracted
     * \return difference of the matrices
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value  && 
        std::is_arithmetic<RHS_TYPE>::value && 
        std::is_same<TYPE, RHS_TYPE>::value == false
    )
    auto operator-(const MatrixMxN<TYPE, ROWS, COLS>& mat) const
    {
        MatrixMxN<std::common_type_t<TYPE, RHS_TYPE>, kRows, kCols> result;
        subtractMatrices(*this, mat, &result);
        return result;
    }

    /** 
     * \brief Subtraction operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \param mat matrix to be subtracted
     * \return difference of the matrices
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value == false && 
        std::is_arithmetic<RHS_TYPE>::value == false &&
        std::is_same<TYPE, RHS_TYPE>::value == false &&
        units::traits::is_convertible_unit_t<TYPE, RHS_TYPE>::value
    )
    auto operator-(const MatrixMxN<TYPE, ROWS, COLS>& mat) const
    {
        MatrixMxN<TYPE, kRows, kCols> result;
        subtractMatrices(*this, mat, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     * \tparam TYPE_RHS right-hand side operand type
     * \param val value to be multiplied by
     * \return product of the matrix multiplied by the value
     */
    template <typename RHS_TYPE>
    requires (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    auto operator*(const RHS_TYPE& val) const
    {
        MatrixMxN<std::common_type_t<TYPE, RHS_TYPE>,ROWS, COLS> result;
        multiplyMatrixByScalar(*this, val, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     * \tparam RHS_TYPE right-hand side operand type
     * \param val value to be multiplied by
     * \return product of the matrix multiplied by the value
     */
    template <typename RHS_TYPE>
    requires (
        (std::is_arithmetic<TYPE>::value && units::traits::is_unit_t<RHS_TYPE>::value) ||
        (units::traits::is_unit_t<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    )
    auto operator*(const RHS_TYPE& val) const
    {
        if constexpr (units::traits::is_unit_t<TYPE>::value)
        {
            MatrixMxN<TYPE, ROWS, COLS> result;
            multiplyMatrixByScalar(*this, val, &result);
            return result;
        }
        else
        {
            MatrixMxN<RHS_TYPE, ROWS, COLS> result;
            multiplyMatrixByScalar(*this, val, &result);
            return result;
        }
    }

    /**
     * \brief Multiplication by a scalar operator.
     * \tparam RHS_TYPE right-hand side operand type
     * \param val value to be multiplied by
     * \return product of the matrix multiplied by the value
     */
    template <typename RHS_TYPE>
    requires (
        units::traits::is_unit_t<TYPE>::value && 
        units::traits::is_unit_t<RHS_TYPE>::value &&
        units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value == false
    )
    auto operator*(const RHS_TYPE& val) const
    {
        MatrixMxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                >
            >,
            ROWS, COLS
        > result;
        multiplyMatrixByScalar(*this, val, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     * 
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     * 
     * \tparam RHS_TYPE right-hand side operand type
     * \param val value to be multiplied by
     * \return product of the matrix multiplied by the value
     */
    template <typename RHS_TYPE>
    requires (units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value)
    auto operator*(const RHS_TYPE& val) const
    {
		if constexpr (units::traits::has_angle_dimension_t<TYPE>::value)
		{
            MatrixMxN<
                typename units::detail::strip_angle_dimension<TYPE>::stripped_type, 
                ROWS, COLS
            > temp;
            for (unsigned int i = 0; i < kSize; ++i)
            {
                temp(i) = units::detail::strip_angle_dimension<TYPE>::strip((*this)(i));
            }

            MatrixMxN<
                units::unit_t<
                    units::compound_unit<
                        typename units::detail::strip_angle_dimension<TYPE>::stripped_unit,
                        typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                    >
                >,
                ROWS, COLS
            > result;
            multiplyMatrixByScalar(temp, val, &result);
            return result;
		}
		else
		{
            typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_type temp = 
                units::detail::strip_angle_dimension<RHS_TYPE>::strip(val);

            MatrixMxN<
                units::unit_t<
                    units::compound_unit<
                        typename units::traits::unit_t_traits<TYPE>::unit_type,
                        typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_unit
                    >
                >,
                ROWS, COLS
            > result;
            multiplyMatrixByScalar(*this, temp, &result);
            return result;
		}
    }

    /**
     * \brief Multiplication by a vector operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param vect vector to be multiplied by
     * \return product of the matrix multiplied by the vector
     */
    template <typename RHS_TYPE>
    requires (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    auto operator*(const VectorN<RHS_TYPE, ROWS>& vect) const
    {
        VectorN<std::common_type_t<TYPE, RHS_TYPE>, ROWS> result;
        multiplyMatrixByVector(*this, vect, &result);
        return result;
    }

    /**
     * \brief Multiplication by a vector operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param vect vector to be multiplied by
     * \return product of the matrix multiplied by the vector
     */
    template <typename RHS_TYPE>
    requires (
        (units::traits::is_unit_t<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
        (std::is_arithmetic<TYPE>::value && units::traits::is_unit_t<RHS_TYPE>::value)
    )
    auto operator*(const VectorN<RHS_TYPE, ROWS>& vect) const
    {
        if constexpr (units::traits::is_unit_t<TYPE>::value)
        {
            VectorN<TYPE, ROWS> result;
            multiplyMatrixByVector(*this, vect, &result);
            return result;
        }
        else
        {
            VectorN<RHS_TYPE, ROWS> result;
            multiplyMatrixByVector(*this, vect, &result);
            return result;
        }
    }

    /**
     * \brief Multiplication by a vector operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param vect vector to be multiplied by
     * \return product of the matrix multiplied by the vector
     */
    template <typename RHS_TYPE>
    requires (
        units::traits::is_unit_t<TYPE>::value && 
        units::traits::is_unit_t<RHS_TYPE>::value &&
        units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value == false
    )
    auto operator*(const VectorN<RHS_TYPE, ROWS>& vect) const
    {
        VectorN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                >
            >,
            ROWS
        > result;
        multiplyMatrixByVector(*this, vect, &result);
        return result;
    }

    /**
     * \brief Multiplication by a vector operator.
     * 
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     * 
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param vect vector to be multiplied by
     * \return product of the matrix multiplied by the vector
     */
    template <typename RHS_TYPE>
    requires (units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value)
    auto operator*(const VectorN<RHS_TYPE, ROWS>& vect) const
    {
        if constexpr (units::traits::has_angle_dimension_t<TYPE>::value)
        {
            MatrixMxN<typename units::detail::strip_angle_dimension<TYPE>::stripped_type, ROWS, COLS> temp;
            for (unsigned int i = 0; i < kSize; ++i)
            {
                temp(i) = units::detail::strip_angle_dimension<TYPE>::strip((*this)(i));
            }

            VectorN<
                units::unit_t<
                    units::compound_unit<
                        typename units::detail::strip_angle_dimension<TYPE>::stripped_unit,
                        typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                    >
                >,
                ROWS
            > result;
            multiplyMatrixByVector(temp, vect, &result);
            return result;
        }
        else
        {
            VectorN<typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_type, ROWS> temp;
            for (unsigned int i = 0; i < ROWS; ++i)
            {
                temp(i) = units::detail::strip_angle_dimension<RHS_TYPE>::strip(vect(i));
            }

            VectorN<
                units::unit_t<
                    units::compound_unit<
                        typename units::traits::unit_t_traits<TYPE>::unit_type,
                        typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_unit
                    >
                >,
                ROWS
            > result;
            multiplyMatrixByVector(*this, temp, &result);
            return result;
        }
    }

    /**
     * \brief Multiplication by a matrix operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \tparam P number of columns of the right-hand side matrix
     * \param mat matrix to be multiplied by
     * \return product of the matrices
     */
    template <typename RHS_TYPE, unsigned int P>
    requires (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    auto operator*(const MatrixMxN<RHS_TYPE, COLS, P>& mat) const
    {
        MatrixMxN<std::common_type_t<TYPE, RHS_TYPE>, ROWS, P> result;
        multiplyMatrixByMatrix(*this, mat, &result);
        return result;
    }

    /**
     * \brief Multiplication by a matrix operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \tparam P number of columns of the right-hand side matrix
     * \param mat matrix to be multiplied by
     * \return product of the matrices
     */
    template <typename RHS_TYPE, unsigned int P>
    requires (
        (units::traits::is_unit_t<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
        (std::is_arithmetic<TYPE>::value && units::traits::is_unit_t<RHS_TYPE>::value)
    )
    auto operator*(const MatrixMxN<RHS_TYPE, COLS, P>& mat) const
    {
        if constexpr (units::traits::is_unit_t<TYPE>::value)
        {
            MatrixMxN<TYPE, ROWS, P> result;
            multiplyMatrixByMatrix(*this, mat, &result);
            return result;
        } 
        else 
        {
            MatrixMxN<RHS_TYPE, ROWS, P> result;
            multiplyMatrixByMatrix(*this, mat, &result);
            return result;
        }
    }

    /**
     * \brief Multiplication by a matrix operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \tparam P number of columns of the right-hand side matrix
     * \param mat matrix to be multiplied by
     * \return product of the matrices
     */
    template <typename RHS_TYPE, unsigned int P>
    requires (
        units::traits::is_unit_t<TYPE>::value && 
        units::traits::is_unit_t<RHS_TYPE>::value &&
        units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value == false
    )
    auto operator*(const MatrixMxN<RHS_TYPE, COLS, P>& mat) const
    {
        MatrixMxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                >
            >,
            ROWS, P
        > result;
        multiplyMatrixByMatrix(*this, mat, &result);
        return result;
    }

    /**
     * \brief Multiplication by a matrix operator.
     * 
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     * 
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \tparam P number of columns of the right-hand side matrix
     * \param mat matrix to be multiplied by
     * \return product of the matrices
     */
    template <typename RHS_TYPE, unsigned int P>
    requires (units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value)
    auto operator*(const MatrixMxN<RHS_TYPE, COLS, P>& mat) const
    {
        if constexpr (units::traits::has_angle_dimension_t<TYPE>::value)
        {
            MatrixMxN<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type, ROWS, P> temp;
            for (unsigned int i = 0; i < kSize; ++i)
            {
                temp(i) = units::detail::strip_angle_dimension<TYPE>::strip((*this)(i));
            }

            MatrixMxN<
                units::unit_t<
                    units::compound_unit<
                        typename units::detail::strip_angle_dimension<TYPE>::stripped_unit,
                        typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                    >
                >,
                ROWS, P
            > result;
            multiplyMatrixByMatrix(temp, mat, &result);
            return result;
        }
        else
        {
            MatrixMxN<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type, ROWS, P> temp;
            for (unsigned int i = 0; i < kSize; ++i)
            {
                temp(i) = units::detail::strip_angle_dimension<TYPE>::strip(mat(i));
            }

            MatrixMxN<
                units::unit_t<
                    units::compound_unit<
                        typename units::traits::unit_t_traits<TYPE>::unit_type,
                        typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_unit
                    >
                >,
                ROWS, P
            > result;
            multiplyMatrixByMatrix(*this, temp, &result);
            return result;
        }
    }

    /**
     * \brief Division by a scalar operator.
     * \tparam RHS_TYPE type of the right-hand side value
     * \param val value to be divided by
     * \return matrix divided by the value
     */
    template <typename RHS_TYPE>
    requires (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    auto operator/(const RHS_TYPE& val) const
    {
        MatrixMxN<std::common_type_t<TYPE, RHS_TYPE>, ROWS, COLS> result;
        multiplyMatrixByScalar(*this, 1.0 / val, &result);
        return result;
    }

    /**
     * \brief Division by a scalar operator.
     * \tparam RHS_TYPE type of the right-hand side value
     * \param val value to be divided by
     * \return matrix divided by the value
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
            MatrixMxN<TYPE, ROWS, COLS> result;
            multiplyMatrixByScalar(*this, 1.0 / val, &result);
            return result;
        }
        else
        {
            MatrixMxN<
                units::unit_t<
                    units::inverse<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type>
                >,
                ROWS, COLS
            > result;
            multiplyMatrixByScalar(*this, 1.0 / val, &result);
            return result;
        }
    }

    /**
     * \brief Division by a scalar operator.
     * \tparam RHS_TYPE type of the right-hand side value
     * \param val value to be divided by
     * \return matrix divided by the value
     */
    template <typename RHS_TYPE>
    requires (units::traits::is_unit_t<TYPE>::value && units::traits::is_unit_t<RHS_TYPE>::value)
    auto operator/(const RHS_TYPE& val) const
    {
        MatrixMxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    units::inverse<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type>
                >
            >,
            ROWS, COLS
        > result;
        multiplyMatrixByScalar(*this, 1.0 / val, &result);
        return result;
    }

    /**
     * \brief Assignment operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \param mat right-hand side matrix
     * \return reference to this matrix
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value && 
        std::is_arithmetic<RHS_TYPE>::value &&
        std::is_same<TYPE, RHS_TYPE>::value == false
    )
    MatrixMxN<TYPE, ROWS, COLS>& operator=(const MatrixMxN<RHS_TYPE, ROWS, COLS>& mat)
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] = static_cast<TYPE>(mat(i));
        }

        return *this;
    }

    /**
     * \brief Assignment operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \param mat right-hand side matrix
     * \return reference to this matrix
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value == false &&
        std::is_arithmetic<RHS_TYPE>::value == false &&
        std::is_same<TYPE, RHS_TYPE>::value == false &&
        units::traits::is_convertible_unit_t<TYPE, RHS_TYPE>::value
    )
    MatrixMxN<TYPE, ROWS, COLS>& operator=(const MatrixMxN<RHS_TYPE, ROWS, COLS>& mat)
    {
        for (unsigned int i = 0; i < kSize; ++i)
        {
            _elements[i] = mat(i);
        }

        return *this;
    }

    /** 
     * \brief Unary addition operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \param mat right-hand side matrix
     * \return reference to this matrix
     */
    template <typename RHS_TYPE>
    requires (
        (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
        units::traits::is_convertible_unit_t<TYPE, RHS_TYPE>::value
    )
    MatrixMxN<TYPE, ROWS, COLS>& operator+=(const MatrixMxN<RHS_TYPE, ROWS, COLS>& mat)
    {
        addMatrices(*this, mat, this);
        return *this;
    }

    /** 
     * \brief Unary subtraction operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \param mat right-hand side matrix
     * \return reference to this matrix
     */
    template <typename RHS_TYPE>
    requires (
        (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
        units::traits::is_convertible_unit_t<TYPE, RHS_TYPE>::value
    )
    MatrixMxN<TYPE, ROWS, COLS>& operator-=(const MatrixMxN<RHS_TYPE, ROWS, COLS>& mat)
    {
        subtractMatrices(*this, mat, this);
        return *this;
    }

    /** 
     * \brief Unary multiplication operator (by number). 
     * \tparam RHS_TYPE type of the right-hand side value
     * \param val value to multiply by
     * \return reference to this matrix
     */
    template <typename RHS_TYPE>
    requires std::is_arithmetic<RHS_TYPE>::value
    MatrixMxN<TYPE, ROWS, COLS>& operator*=(RHS_TYPE val)
    {
        *this = (*this) * val;
        return *this;
    }

    /** 
     * \brief Unary division operator (by number). 
     * \tparam RHS_TYPE type of the right-hand side value
     * \param val value to divide by
     * \return reference to this matrix
     */
    template <typename RHS_TYPE>
    requires std::is_arithmetic<RHS_TYPE>::value
    MatrixMxN<TYPE, ROWS, COLS>& operator/=(RHS_TYPE val)
    {
        *this = (*this) / val;
        return *this;
    }

    /** 
     * \brief Equality operator. 
     * \param mat matrix to compare with
     * \return true if the matrices are equal, false otherwise
     */
    bool operator==(const MatrixMxN<TYPE, ROWS, COLS>& mat) const
    {
        bool result = true;
        for (unsigned int i = 0; i < kSize; ++i)
        {
            result = result && (_elements[i] == mat._elements[i]);
        }
        return result;
    }

    /** 
     * \brief Inequality operator. 
     * \param mat matrix to compare with
     * \return true if the matrices are not equal, false otherwise
     */
    bool operator!=(const MatrixMxN<TYPE, ROWS, COLS>& mat) const
    {
        return !(*this == mat);
    }

protected:

    TYPE _elements[kSize] = { TYPE{0} };    ///< matrix elements
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
 * \param result output result matrix
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
 * \param result output result matrix
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

/** 
 * \brief Multiplication a matrix by a value.
 * \tparam LHS_TYPE type of the left-hand side matrix elements
 * \tparam RHS_TYPE type of the right-hand side matrix elements
 * \tparam RESULT_TYPE type of the result matrix elements
 * \tparam ROWS number of matrix rows
 * \tparam COLS number of matrix columns
 * \param matrix matrix
 * \param val value to multiply the matrix by
 * \param result output result matrix
 */
template <typename LHS_TYPE, typename RHS_TYPE, typename RESULT_TYPE, unsigned int ROWS, unsigned int COLS>
void multiplyMatrixByScalar(
    const MatrixMxN<LHS_TYPE, ROWS, COLS>& mat, 
    const RHS_TYPE& val,
    MatrixMxN<RESULT_TYPE, ROWS, COLS>* result
)
{
    for (unsigned int r = 0; r < ROWS; ++r)
    {
        for (unsigned int c = 0; c < COLS; ++c)
        {
            (*result)(r, c) = mat(r, c) * val;
        }
    }
}

/** 
 * \brief Multiplication a matrix by a vector algorithm. 
 * \tparam LHS_TYPE type of the left-hand side matrix elements
 * \tparam RHS_TYPE type of the right-hand side matrix elements
 * \tparam RESULT_TYPE type of the result matrix elements
 * \tparam ROWS number of matrix rows
 * \tparam COLS number of matrix columns
 */
template <typename LHS_TYPE, typename RHS_TYPE, typename RESULT_TYPE, unsigned int ROWS, unsigned int COLS>
void multiplyMatrixByVector(
    const MatrixMxN<LHS_TYPE, ROWS, COLS>& mat, 
    const VectorN<RHS_TYPE, ROWS>& vect,
    VectorN<RESULT_TYPE, ROWS>* result
)
{
    for (unsigned int r = 0; r < ROWS; ++r)
    {
        for (unsigned int c = 0; c < COLS; ++c)
        {
            (*result)(r) += mat(r,c) * vect(c);
        }
    }
}

/** 
 * \brief Multiplication a matrix by a matrix algorithm.
 * \tparam LHS_TYPE type of the left-hand side matrix elements
 * \tparam RHS_TYPE type of the right-hand side matrix elements
 * \tparam RESULT_TYPE type of the result matrix elements
 * \tparam M number of rows in the left-hand side matrix
 * \tparam N number of columns in the left-hand side matrix (and rows in the right-hand side matrix)
 * \tparam P number of columns in the right-hand side matrix
 */
template <typename LHS_TYPE, typename RHS_TYPE, typename RESULT_TYPE, unsigned int M, unsigned int N, unsigned int P>
void multiplyMatrixByMatrix(
    const MatrixMxN<LHS_TYPE, M, N>& lhs,
    const MatrixMxN<RHS_TYPE, N, P>& rhs,
    MatrixMxN<RESULT_TYPE,M,P>* result)
{
    for (unsigned int i = 0; i < M; ++i)
    {
        for (unsigned int j = 0; j < P; ++j)
        {
            (*result)(i, j) = RESULT_TYPE{0};
            for (unsigned int k = 0; k < N; ++k)
            {
                (*result)(i, j) += lhs(i, k) * rhs(k, j);
            }
        }
    }
}

/** 
 * \brief Matrix transposition algorithm. 
 * \tparam TYPE type of the matrix elements
 * \tparam ROWS number of matrix rows
 * \tparam COLS number of matrix columns
 * \param matrix input matrix
 * \param result output transposed matrix
 */
template <typename TYPE, unsigned int ROWS, unsigned int COLS>
void transposeMatrix(const MatrixMxN<TYPE, ROWS, COLS> matrix, MatrixMxN<TYPE, COLS, ROWS>* result)
{
    for (unsigned int r = 0; r < ROWS; ++r)
    {
        for (unsigned int c = 0; c < COLS; ++c)
        {
            (*result)(c, r) = matrix(r, c);
        }
    }
}

/** 
 * \brief Multiplication operator. 
 * \tparam LHS_TYPE type of the left-hand side value
 * \tparam RHS_TYPE type of the right-hand side matrix elements
 * \tparam ROWS number of matrix rows
 * \tparam COLS number of matrix columns
 * \param val value to be multiplied by
 * \param mat matrix to be multiplied
 * \return product of the value multiplied by the matrix
 */
template <typename LHS_TYPE, class RHS_TYPE, unsigned int ROWS, unsigned int COLS>
requires (
    std::is_arithmetic<LHS_TYPE>::value ||
    units::traits::is_unit_t<LHS_TYPE>::value
)
auto operator*(LHS_TYPE val, const MatrixMxN<RHS_TYPE, ROWS, COLS>& mat)
{
    return mat * val;
}

} // namespace mc

#endif // MCUTILS_MATH_MATRIXMXN_H_