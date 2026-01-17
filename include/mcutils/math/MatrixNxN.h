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
#ifndef MCUTILS_MATH_MATRIXNXN_H_
#define MCUTILS_MATH_MATRIXNXN_H_

#ifndef MCUTILS_MATH_MATRIX_H_
#   error "Do not include this file directly. Include <mcutils/math/Matrix.h> instead."
#endif

#include <mcutils/math/MatrixMxN.h>

namespace mc {

/**
 * \brief A template class representing a square matrix with fixed dimensions.
 *
 * This class provides a variety of matrix operations, including addition, subtraction,
 * scalar multiplication, matrix multiplication, transposition, and more. It supports
 * both dimensionless and unit-based types, with specializations for angular velocity
 * and angular acceleration. The matrix elements are stored in a row-major order.
 *
 * \tparam TYPE matrix element type
 * \tparam SIZE number of rows and columns
 */
template <typename TYPE, unsigned int SIZE>
class MatrixNxN : public MatrixMxN<TYPE, SIZE, SIZE>
{
public:

    /** \brief Creates identity matrix. */
    static MatrixNxN<TYPE,SIZE> getIdentityMatrix()
    {
        MatrixNxN<TYPE, SIZE> result;
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            result(i,i) = TYPE{1.0};
        }
        return result;
    }

    /** \brief Returns transposed matrix. */
    MatrixNxN<TYPE,SIZE> getTransposed() const
    {
        MatrixNxN<TYPE,SIZE> result;
        transposeMatrix(*this, &result);
        return result;
    }

    /** \brief Transposes matrix. */
    void transpose()
    {
        *this = getTransposed();
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
    operator MatrixNxN<NEW_TYPE,SIZE>() const
    {
        MatrixNxN<NEW_TYPE,SIZE> result;
        for (unsigned int r = 0; r < this->kRows; ++r)
        {
            for (unsigned int c = 0; c < this->kCols; ++c)
            {
                result(r, c) = static_cast<NEW_TYPE>(this->_elements[r * this->kCols + c]);
            }
        }
        return result;
    }

    /**
     * \brief Addition operator.
     * \param mat matrix to be added
     * \return sum of the matrices
     */
    MatrixNxN<TYPE, SIZE> operator+(const MatrixNxN<TYPE, SIZE>& mat) const
    {
        MatrixNxN<TYPE, SIZE> result;
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
    auto operator+(const MatrixNxN<RHS_TYPE, SIZE>& mat) const
    {
        MatrixNxN<std::common_type_t<TYPE, RHS_TYPE>, SIZE> result;
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
    auto operator+(const MatrixNxN<RHS_TYPE, SIZE>& mat) const
    {
        MatrixNxN<TYPE, SIZE> result;
        addMatrices(*this, mat, &result);
        return result;
    }

    /** 
     * \brief Negation operator.
     * \return negated matrix
     */
    MatrixNxN<TYPE, SIZE> operator-() const
    {
        MatrixNxN<TYPE,SIZE> result(*this);
        result.negate();
        return result;
    }

    /** 
     * \brief Subtraction operator.
     * \param mat matrix to be subtracted
     * \return difference of the matrices
     */
    MatrixNxN<TYPE, SIZE> operator-(const MatrixNxN<TYPE, SIZE>& mat) const
    {
        MatrixNxN<TYPE, SIZE> result;
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
    auto operator-(const MatrixNxN<TYPE, SIZE>& mat) const
    {
        MatrixNxN<std::common_type_t<TYPE, RHS_TYPE>, SIZE> result;
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
    auto operator-(const MatrixNxN<TYPE, SIZE>& mat) const
    {
        MatrixNxN<TYPE, SIZE> result;
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
        MatrixNxN<std::common_type_t<TYPE, RHS_TYPE>, SIZE> result;
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
            MatrixNxN<TYPE, SIZE> result;
            multiplyMatrixByScalar(*this, val, &result);
            return result;
        }
        else
        {
            MatrixNxN<RHS_TYPE, SIZE> result;
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
        MatrixNxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                >
            >,
            SIZE
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
            MatrixNxN<
                typename units::detail::strip_angle_dimension<TYPE>::stripped_type, 
                SIZE
            > temp;
            for (unsigned int i = 0; i < this->kSize; ++i)
            {
                temp(i) = units::detail::strip_angle_dimension<TYPE>::strip((*this)(i));
            }

            MatrixNxN<
                units::unit_t<
                    units::compound_unit<
                        typename units::detail::strip_angle_dimension<TYPE>::stripped_unit,
                        typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                    >
                >,
                SIZE
            > result;
            multiplyMatrixByScalar(temp, val, &result);
            return result;
		}
		else
		{
            typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_type temp = 
                units::detail::strip_angle_dimension<RHS_TYPE>::strip(val);

            MatrixNxN<
                units::unit_t<
                    units::compound_unit<
                        typename units::traits::unit_t_traits<TYPE>::unit_type,
                        typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_unit
                    >
                >,
                SIZE
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
    auto operator*(const VectorN<RHS_TYPE, SIZE>& vect) const
    {
        VectorN<std::common_type_t<TYPE, RHS_TYPE>, SIZE> result;
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
    auto operator*(const VectorN<RHS_TYPE, SIZE>& vect) const
    {
        if constexpr (units::traits::is_unit_t<TYPE>::value)
        {
            VectorN<TYPE, SIZE> result;
            multiplyMatrixByVector(*this, vect, &result);
            return result;
        }
        else
        {
            VectorN<RHS_TYPE, SIZE> result;
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
    auto operator*(const VectorN<RHS_TYPE, SIZE>& vect) const
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
    auto operator*(const VectorN<RHS_TYPE, SIZE>& vect) const
    {
        if constexpr (units::traits::has_angle_dimension_t<TYPE>::value)
        {
            MatrixNxN<typename units::detail::strip_angle_dimension<TYPE>::stripped_type, SIZE> temp;
            for (unsigned int i = 0; i < this->kSize; ++i)
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
                SIZE
            > result;
            multiplyMatrixByVector(temp, vect, &result);
            return result;
        }
        else
        {
            VectorN<typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_type, SIZE> temp;
            for (unsigned int i = 0; i < SIZE; ++i)
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
                SIZE
            > result;
            multiplyMatrixByVector(*this, temp, &result);
            return result;
        }
    }

    /**
     * \brief Multiplication by a matrix operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \param mat matrix to be multiplied by
     * \return product of the matrices
     */
    template <typename RHS_TYPE>
    requires (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    auto operator*(const MatrixNxN<RHS_TYPE, SIZE>& mat) const
    {
        MatrixNxN<std::common_type_t<TYPE, RHS_TYPE>, SIZE> result;
        multiplyMatrixByMatrix(*this, mat, &result);
        return result;
    }

    /**
     * \brief Multiplication by a matrix operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \param mat matrix to be multiplied by
     * \return product of the matrices
     */
    template <typename RHS_TYPE>
    requires (
        (units::traits::is_unit_t<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
        (std::is_arithmetic<TYPE>::value && units::traits::is_unit_t<RHS_TYPE>::value)
    )
    auto operator*(const MatrixNxN<RHS_TYPE, SIZE>& mat) const
    {
        if constexpr (units::traits::is_unit_t<TYPE>::value)
        {
            MatrixNxN<TYPE, SIZE> result;
            multiplyMatrixByMatrix(*this, mat, &result);
            return result;
        } 
        else 
        {
            MatrixNxN<RHS_TYPE, SIZE> result;
            multiplyMatrixByMatrix(*this, mat, &result);
            return result;
        }
    }

    /**
     * \brief Multiplication by a matrix operator.
     * \tparam RHS_TYPE type of the right-hand side matrix elements
     * \param mat matrix to be multiplied by
     * \return product of the matrices
     */
    template <typename RHS_TYPE>
    requires (
        units::traits::is_unit_t<TYPE>::value && 
        units::traits::is_unit_t<RHS_TYPE>::value &&
        units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value == false
    )
    auto operator*(const MatrixNxN<RHS_TYPE, SIZE>& mat) const
    {
        MatrixNxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                >
            >,
            SIZE
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
     * \param mat matrix to be multiplied by
     * \return product of the matrices
     */
    template <typename RHS_TYPE>
    requires (units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value)
    auto operator*(const MatrixNxN<RHS_TYPE, SIZE>& mat) const
    {
        if constexpr (units::traits::has_angle_dimension_t<TYPE>::value)
        {
            MatrixNxN<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type, SIZE> temp;
            for (unsigned int i = 0; i < this->kSize; ++i)
            {
                temp(i) = units::detail::strip_angle_dimension<TYPE>::strip((*this)(i));
            }

            MatrixNxN<
                units::unit_t<
                    units::compound_unit<
                        typename units::detail::strip_angle_dimension<TYPE>::stripped_unit,
                        typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                    >
                >,
                SIZE
            > result;
            multiplyMatrixByMatrix(temp, mat, &result);
            return result;
        }
        else
        {
            MatrixNxN<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type, SIZE> temp;
            for (unsigned int i = 0; i < this->kSize; ++i)
            {
                temp(i) = units::detail::strip_angle_dimension<TYPE>::strip(mat(i));
            }

            MatrixNxN<
                units::unit_t<
                    units::compound_unit<
                        typename units::traits::unit_t_traits<TYPE>::unit_type,
                        typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_unit
                    >
                >,
                SIZE
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
        MatrixNxN<std::common_type_t<TYPE, RHS_TYPE>, SIZE> result;
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
            MatrixNxN<TYPE, SIZE> result;
            multiplyMatrixByScalar(*this, 1.0 / val, &result);
            return result;
        }
        else
        {
            MatrixNxN<
                units::unit_t<
                    units::inverse<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type>
                >,
                SIZE
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
        MatrixNxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    units::inverse<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type>
                >
            >,
            SIZE
        > result;
        multiplyMatrixByScalar(*this, 1.0 / val, &result);
        return result;
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
    MatrixNxN<TYPE, SIZE>& operator+=(const MatrixNxN<RHS_TYPE, SIZE>& mat)
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
    MatrixNxN<TYPE, SIZE>& operator-=(const MatrixNxN<RHS_TYPE, SIZE>& mat)
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
    MatrixNxN<TYPE, SIZE>& operator*=(RHS_TYPE val)
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
    MatrixNxN<TYPE, SIZE>& operator/=(RHS_TYPE val)
    {
        *this = (*this) / val;
        return *this;
    }
};

/** 
 * \brief Multiplication operator. 
 * \tparam LHS_TYPE type of the left-hand side value
 * \tparam RHS_TYPE type of the right-hand side matrix elements
 * \tparam SIZE number of rows and columns
 * \param val value to be multiplied by
 * \param mat matrix to be multiplied
 * \return product of the value multiplied by the matrix
 */
template <typename LHS_TYPE, class RHS_TYPE, unsigned int SIZE>
requires (
    std::is_arithmetic<LHS_TYPE>::value ||
    units::traits::is_unit_t<LHS_TYPE>::value
)
auto operator*(LHS_TYPE val, const MatrixNxN<RHS_TYPE, SIZE>& mat)
{
    return mat * val;
}

} // namespace mc

#endif // MCUTILS_MATH_MATRIXNXN_H_
