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
#   error "Do not include this file directly. Include <mcsim/utils/math/Matrix.h> instead."
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
        this->transposeMatrix(*this, &result);
        return result;
    }

    /** \brief Transposes matrix. */
    void transpose()
    {
        *this = getTransposed();
    }

    /** \brief Converts the matrix to a dimensionless matrix. */
    inline MatrixNxN<double, SIZE> getDimensionless() const
    {
        MatrixNxN<double, SIZE> result;
        for (unsigned int r = 0; r < this->kRows; ++r)
        {
            for (unsigned int c = 0; c < this->kCols; ++c)
            {
                result(r, c) = static_cast<double>(this->_elements[r * this->kCols + c]);
            }
        }
        return result;
    }

    /** \brief Casting operator. */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value
        &&
        units::traits::is_convertible_unit_t<TYPE, TYPE2>::value, int>::type = 0
    >
    operator MatrixNxN<TYPE2,SIZE>() const
    {
        MatrixNxN<TYPE2,SIZE> result;
        for (unsigned int r = 0; r < this->kRows; ++r)
        {
            for (unsigned int c = 0; c < this->kCols; ++c)
            {
                result(r, c) = this->_elements[r * this->kCols + c];
            }
        }
        return result;
    }

    /** \brief Addition operator. */
    MatrixNxN<TYPE,SIZE> operator+(const MatrixNxN<TYPE,SIZE>& matrix) const
    {
        MatrixNxN<TYPE,SIZE> result(*this);
        result.add(matrix);
        return result;
    }

    /** \brief Negation operator. */
    MatrixNxN<TYPE,SIZE> operator-() const
    {
        MatrixNxN<TYPE,SIZE> result(*this);
        result.negate();
        return result;
    }

    /** \brief Subtraction operator. */
    MatrixNxN<TYPE,SIZE> operator-(const MatrixNxN<TYPE,SIZE>& matrix) const
    {
        MatrixNxN<TYPE,SIZE> result(*this);
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
    auto operator*(TYPE2 value) const
    {
        MatrixNxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<TYPE2>::unit_type
                >
            >,
            SIZE
        > result;
        this->multiplyMatrixByValue(*this, value, &result);
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
    auto operator*(TYPE2 value) const
    {
        units::angular_velocity::radians_per_second_t temp_rad_per_s = value;
        units::auxiliary::per_second_t temp = units::auxiliary::per_second_t{ temp_rad_per_s() };

        MatrixNxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
                >
            >,
            SIZE
        > result;
        this->multiplyMatrixByValue(*this, temp, &result);
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
        units::auxiliary::per_second_squared_t temp = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq() };

        MatrixNxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
                >
            >,
            SIZE
        > result;
        this->multiplyMatrixByValue(*this, temp, &result);
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
    MatrixNxN<TYPE2, SIZE> operator*(TYPE2 value) const
    {
        MatrixNxN<TYPE2, SIZE> result;
        this->multiplyMatrixByValue(*this, value, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     *
     * This is a specialization for the case when the value is dimensionless.
     */
    MatrixNxN<TYPE, SIZE> operator*(double value) const
    {
        MatrixNxN<TYPE, SIZE> result;
        this->multiplyMatrixByValue(*this, value, &result);
        return result;
    }

    /**
     * \brief Multiplication operator by a vector.
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
    auto operator*(const VectorN<TYPE2, SIZE>& vect) const
    {
        VectorN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<TYPE2>::unit_type
                >
            >,
            SIZE
        > result;
        this->multiplyMatrixByVector(*this, vect, &result);
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
    auto operator*(const VectorN<TYPE2, SIZE>& vect) const
    {
        VectorN<units::angular_velocity::radians_per_second_t, SIZE> temp_rad_per_s = vect;
        VectorN<units::auxiliary::per_second_t, SIZE> temp;
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            temp(i) = units::auxiliary::per_second_t{ temp_rad_per_s(i)() };
        }

        VectorN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
                >
            >,
            SIZE
        > result;
        this->multiplyMatrixByVector(*this, temp, &result);
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
    auto operator*(const VectorN<TYPE2, SIZE>& vect) const
    {
        VectorN<units::angular_acceleration::radians_per_second_squared_t, SIZE> temp_rad_per_s = vect;
        VectorN<units::auxiliary::per_second_squared_t, SIZE> temp;
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            temp(i) = units::auxiliary::per_second_squared_t{ temp_rad_per_s(i)() };
        }

        VectorN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
                >
            >,
            SIZE
        > result;
        this->multiplyMatrixByVector(*this, temp, &result);
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
    VectorN<TYPE,SIZE> operator*(const VectorN<TYPE2, SIZE>& vect)
    {
        VectorN<TYPE,SIZE> result;
        this->multiplyMatrixByVector(*this, vect, &result);
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
    VectorN<TYPE2,SIZE> operator*(const VectorN<TYPE2, SIZE>& vect)
    {
        VectorN<TYPE2,SIZE> result;
        this->multiplyMatrixByVector(*this, vect, &result);
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
    VectorN<double,SIZE> operator*(const VectorN<TYPE2, SIZE>& vect)
    {
        VectorN<double,SIZE> result;
        this->multiplyMatrixByVector(*this, vect, &result);
        return result;
    }

    /** \brief Multiplies by a matrix by a matrix. */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator*(const MatrixNxN<TYPE2, SIZE>& matrix)
    {
        MatrixNxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<TYPE2>::unit_type
                >
            >,
            SIZE
        > result;
        this->multiplyMatrixByMatrix(*this, matrix, &result);
        return result;
    }

    /**
     * \brief Multiplies by a matrix by a matrix.
     *
     * This is a specialization for the case when the first matrix is dimensionless.
     */
    template <class TYPE2, typename std::enable_if<
        !units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    MatrixNxN<TYPE2,SIZE> operator*(const MatrixNxN<TYPE2, SIZE>& matrix)
    {
        MatrixNxN<TYPE2,SIZE> result;
        this->multiplyMatrixByMatrix(*this, matrix, &result);
        return result;
    }

    /**
     * \brief Multiplies by a matrix by a matrix.
     *
     * This is a specialization for the case when the second matrix is dimensionless.
     */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        !units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    MatrixNxN<TYPE,SIZE> operator*(const MatrixNxN<TYPE2, SIZE>& matrix)
    {
        MatrixNxN<TYPE,SIZE> result;
        this->multiplyMatrixByMatrix(*this, matrix, &result);
        return result;
    }

    /**
     * \brief Multiplies by a matrix by a matrix.
     *
     * This is a specialization for the case when both matrices are dimensionless.
     */
    template <class TYPE2, typename std::enable_if<
        !units::traits::is_unit_t<TYPE>::value
        &&
        !units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    MatrixNxN<double,SIZE> operator*(const MatrixNxN<TYPE2, SIZE>& matrix)
    {
        MatrixNxN<double,SIZE> result;
        this->multiplyMatrixByMatrix(*this, matrix, &result);
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
        MatrixNxN<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    units::inverse<typename units::traits::unit_t_traits<TYPE2>::unit_type>
                >
            >,
            SIZE
        > result;
        this->multiplyMatrixByValue(*this, 1.0 / value, &result);
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
        MatrixNxN<
            units::unit_t<
                units::compound_unit<
                    units::inverse<typename units::traits::unit_t_traits<TYPE2>::unit_type>
                >
            >,
            SIZE
        > result;
        this->multiplyMatrixByValue(*this, 1.0 / value, &result);
        return result;
    }

    /**
     * \brief Division operator.
     *
     * This is a specialization for the case when the value is dimensionless.
     */
    MatrixNxN<TYPE, SIZE> operator/(double value) const
    {
        MatrixNxN<TYPE, SIZE> result;
        this->multiplyMatrixByValue(*this, 1.0 / value, &result);
        return result;
    }

    /** \brief Unary addition operator. */
    MatrixNxN<TYPE,SIZE>& operator+=(const MatrixNxN<TYPE,SIZE>& matrix)
    {
        this->add(matrix);
        return *this;
    }

    /** \brief Unary subtraction operator. */
    MatrixNxN<TYPE,SIZE>& operator-=(const MatrixNxN<TYPE,SIZE>& matrix)
    {
        this->subtract(matrix);
        return *this;
    }

    /** \brief Unary multiplication operator (by number). */
    MatrixNxN<TYPE,SIZE>& operator*=(double value)
    {
        *this = (*this) * value;
        return *this;
    }

    /** \brief Unary division operator (by number). */
    MatrixNxN<TYPE,SIZE>& operator/=(double value)
    {
        *this = (*this) / value;
        return *this;
    }
};

/** \brief Multiplication operator. */
template <typename TYPE1, class TYPE2, unsigned int SIZE, typename std::enable_if<
    units::traits::is_unit_t<TYPE1>::value, int>::type = 0
>
auto operator*(TYPE1 value, const MatrixNxN<TYPE2,SIZE>& matrix)
{
    return matrix * value;
}

/**
 * \brief Multiplication operator.
 *
 * This is a specialization for the case when the value is a number.
 */
template<typename TYPE, unsigned int SIZE>
MatrixNxN<TYPE,SIZE> operator*(double value, const MatrixNxN<TYPE,SIZE>& matrix)
{
    return matrix * value;
}

} // namespace mc

#endif // MCUTILS_MATH_MATRIXNXN_H_
