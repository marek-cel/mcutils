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
#ifndef MCUTILS_MATH_MATRIX3X3_H_
#define MCUTILS_MATH_MATRIX3X3_H_

#ifndef MCUTILS_MATH_MATRIX_H_
#   error "Do not include this file directly. Include <mcsim/utils/math/Matrix.h> instead."
#endif

#include <mcutils/math/MatrixNxN.h>
#include <mcutils/math/Vector3.h>

namespace mc {

/**
 * \brief A template class representing a square 3x3 matrix.
 *
 * This class provides a variety of matrix operations, including addition, subtraction,
 * scalar multiplication, matrix multiplication, transposition, and more. It supports
 * both dimensionless and unit-based types, with specializations for angular velocity
 * and angular acceleration. The matrix elements are stored in a row-major order.
 *
 * \tparam TYPE matrix element type
 */
template <typename TYPE>
class Matrix3x3 : public MatrixNxN<TYPE, 3>
{
public:

    /** \brief Creates identity matrix. */
    static Matrix3x3<TYPE> getIdentityMatrix()
    {
        return Matrix3x3<TYPE>(TYPE{1}, TYPE{0}, TYPE{0},
                               TYPE{0}, TYPE{1}, TYPE{0},
                               TYPE{0}, TYPE{0}, TYPE{1});
    }

    /** \brief Constructor. */
    Matrix3x3(TYPE xx = TYPE{0}, TYPE xy = TYPE{0}, TYPE xz = TYPE{0},
              TYPE yx = TYPE{0}, TYPE yy = TYPE{0}, TYPE yz = TYPE{0},
              TYPE zx = TYPE{0}, TYPE zy = TYPE{0}, TYPE zz = TYPE{0})
    {
        set(xx, xy, xz, yx, yy, yz, zx, zy, zz);
    }

    /**
     * \brief Sets items of the matrix.
     * \param xx item at position xx
     * \param xy item at position xy
     * \param xz item at position xz
     * \param yx item at position yx
     * \param yy item at position yy
     * \param yz item at position yz
     * \param zx item at position zx
     * \param zy item at position zy
     * \param zz item at position zz
     */
    void set(TYPE xx, TYPE xy, TYPE xz,
             TYPE yx, TYPE yy, TYPE yz,
             TYPE zx, TYPE zy, TYPE zz)
    {
        this->_elements[0] = xx;
        this->_elements[1] = xy;
        this->_elements[2] = xz;
        this->_elements[3] = yx;
        this->_elements[4] = yy;
        this->_elements[5] = yz;
        this->_elements[6] = zx;
        this->_elements[7] = zy;
        this->_elements[8] = zz;
    }

    inline TYPE xx() const { return this->_elements[0]; }
    inline TYPE xy() const { return this->_elements[1]; }
    inline TYPE xz() const { return this->_elements[2]; }
    inline TYPE yx() const { return this->_elements[3]; }
    inline TYPE yy() const { return this->_elements[4]; }
    inline TYPE yz() const { return this->_elements[5]; }
    inline TYPE zx() const { return this->_elements[6]; }
    inline TYPE zy() const { return this->_elements[7]; }
    inline TYPE zz() const { return this->_elements[8]; }

    inline TYPE& xx() { return this->_elements[0]; }
    inline TYPE& xy() { return this->_elements[1]; }
    inline TYPE& xz() { return this->_elements[2]; }
    inline TYPE& yx() { return this->_elements[3]; }
    inline TYPE& yy() { return this->_elements[4]; }
    inline TYPE& yz() { return this->_elements[5]; }
    inline TYPE& zx() { return this->_elements[6]; }
    inline TYPE& zy() { return this->_elements[7]; }
    inline TYPE& zz() { return this->_elements[8]; }

    /** \brief Returns transposed matrix. */
    Matrix3x3<TYPE> getTransposed() const
    {
        Matrix3x3<TYPE> result;
        this->transposeMatrix(*this, &result);
        return result;
    }

    /** \brief Converts the matrix to a dimensionless matrix. */
    inline Matrix3x3<double> getDimensionless() const
    {
        Matrix3x3<double> result;
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
    operator Matrix3x3<TYPE2>() const
    {
        Matrix3x3<TYPE2> result;
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
    Matrix3x3<TYPE> operator+(const Matrix3x3<TYPE>& matrix) const
    {
        Matrix3x3<TYPE> result(*this);
        result.add(matrix);
        return result;
    }

    /** \brief Negation operator. */
    Matrix3x3<TYPE> operator-() const
    {
        Matrix3x3<TYPE> result(*this);
        result.negate();
        return result;
    }

    /** \brief Subtraction operator. */
    Matrix3x3<TYPE> operator-(const Matrix3x3<TYPE>& matrix) const
    {
        Matrix3x3<TYPE> result(*this);
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
        Matrix3x3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<TYPE2>::unit_type
                >
            >
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

        Matrix3x3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
                >
            >
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

        Matrix3x3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
                >
            >
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
    Matrix3x3<TYPE2> operator*(TYPE2 value) const
    {
        Matrix3x3<TYPE2> result;
        this->multiplyMatrixByValue(*this, value, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     *
     * This is a specialization for the case when the value is dimensionless.
     */
    Matrix3x3<TYPE> operator*(double value) const
    {
        Matrix3x3<TYPE> result;
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
    auto operator*(const Vector3<TYPE2>& vect) const
    {
        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<TYPE2>::unit_type
                >
            >
        > result;
        this->multiplyMatrixByVector(*this, vect, &result);
        return result;
    }

    /**
     * \brief Multiplication operator by a vector.
     *
     * This is a specialization for the case when the vector is angular velocity.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     *  This specialization is enabled when TYPE is a unit and TYPE2 is angular velocity.
     *
     * Example: calculating angular momentum from inertia and angular velocity.
     * L = I * omega
     *
     * \tparam TYPE2 RHS operand type
     * \param vect vector to be multiplied by
     * \return product of the matrix multiplied by the vector
     */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_convertible_unit_t<
            TYPE2, units::angular_velocity::radians_per_second_t
        >::value, int>::type = 0
    >
    auto operator*(const Vector3<TYPE2>& vect) const
    {
        Vector3<units::angular_velocity::radians_per_second_t> temp_rad_per_s = vect;
        Vector3<units::auxiliary::per_second_t> temp;
        temp.x() = units::auxiliary::per_second_t{ temp_rad_per_s.x()() };
        temp.y() = units::auxiliary::per_second_t{ temp_rad_per_s.y()() };
        temp.z() = units::auxiliary::per_second_t{ temp_rad_per_s.z()() };

        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
                >
            >
        > result;
        this->multiplyMatrixByVector(*this, temp, &result);
        return result;
    }

    /**
     * \brief Multiplication operator by a vector.
     *
     * This is a specialization for the case when the vector is angular acceleration.
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
     * \param vect vector to be multiplied by
     * \return product of the matrix multiplied by the vector
     */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_convertible_unit_t<
            TYPE2, units::angular_acceleration::radians_per_second_squared_t
        >::value, int>::type = 0
    >
    auto operator*(const Vector3<TYPE2>& vect) const
    {
        Vector3<units::angular_acceleration::radians_per_second_squared_t> temp_rad_per_s = vect;
        Vector3<units::auxiliary::per_second_squared_t> temp;
        temp.x() = units::auxiliary::per_second_squared_t{ temp_rad_per_s.x()() };
        temp.y() = units::auxiliary::per_second_squared_t{ temp_rad_per_s.y()() };
        temp.z() = units::auxiliary::per_second_squared_t{ temp_rad_per_s.z()() };

        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
                >
            >
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
    Vector3<TYPE> operator*(const Vector3<TYPE2>& vect)
    {
        Vector3<TYPE> result;
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
    Vector3<TYPE2> operator*(const Vector3<TYPE2>& vect)
    {
        Vector3<TYPE2> result;
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
    Vector3<double> operator*(const Vector3<TYPE2>& vect)
    {
        Vector3<double> result;
        this->multiplyMatrixByVector(*this, vect, &result);
        return result;
    }

    /** \brief Multiplies by a matrix by a matrix. */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator*(const Matrix3x3<TYPE2>& matrix)
    {
        Matrix3x3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<TYPE2>::unit_type
                >
            >
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
    Matrix3x3<TYPE2> operator*(const Matrix3x3<TYPE2>& matrix)
    {
        Matrix3x3<TYPE2> result;
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
    Matrix3x3<TYPE> operator*(const Matrix3x3<TYPE2>& matrix)
    {
        Matrix3x3<TYPE> result;
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
    Matrix3x3<double> operator*(const Matrix3x3<TYPE2>& matrix)
    {
        Matrix3x3<double> result;
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
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator/(TYPE2 value) const
    {
        Matrix3x3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    units::inverse<typename units::traits::unit_t_traits<TYPE2>::unit_type>
                >
            >
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
        Matrix3x3<
            units::unit_t<
                units::compound_unit<
                    units::inverse<typename units::traits::unit_t_traits<TYPE2>::unit_type>
                >
            >
        > result;
        this->multiplyMatrixByValue(*this, 1.0 / value, &result);
        return result;
    }

    /**
     * \brief Division operator.
     *
     * This is a specialization for the case when the value is dimensionless.
     */
    Matrix3x3<TYPE> operator/(double value) const
    {
        Matrix3x3<TYPE> result;
        this->multiplyMatrixByValue(*this, 1.0 / value, &result);
        return result;
    }

    /** \brief Unary addition operator. */
    Matrix3x3<TYPE>& operator+=(const Matrix3x3<TYPE>& matrix)
    {
        this->add(matrix);
        return *this;
    }

    /** \brief Unary subtraction operator. */
    Matrix3x3<TYPE>& operator-=(const Matrix3x3<TYPE>& matrix)
    {
        this->subtract(matrix);
        return *this;
    }

    /** \brief Unary multiplication operator (by number). */
    Matrix3x3<TYPE>& operator*=(double value)
    {
        *this = (*this) * value;
        return *this;
    }

    /** \brief Unary division operator (by number). */
    Matrix3x3<TYPE>& operator/=(double value)
    {
        *this = (*this) / value;
        return *this;
    }
};

/** \brief Multiplication operator. */
template <typename TYPE1, class TYPE2, typename std::enable_if<
    units::traits::is_unit_t<TYPE1>::value, int>::type = 0
>
auto operator*(TYPE1 value, const Matrix3x3<TYPE2>& matrix)
{
    return matrix * value;
}

/**
 * \brief Multiplication operator.
 * This is a specialization for the case when the value is a number.
 */
template<typename TYPE>
Matrix3x3<TYPE> operator*(double value, const Matrix3x3<TYPE>& matrix)
{
    return matrix * value;
}

} // namespace mc

#endif // MCUTILS_MATH_MATRIX3X3_H_
