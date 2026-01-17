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
#   error "Do not include this file directly. Include <mcutils/math/Matrix.h> instead."
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
     * \brief Converting constructor.
     * \tparam TYPE_XX type of the xx element
     * \tparam TYPE_XY type of the xy element
     * \tparam TYPE_XZ type of the xz element
     * \tparam TYPE_YX type of the yx element
     * \tparam TYPE_YY type of the yy element
     * \tparam TYPE_YZ type of the yz element
     * \tparam TYPE_ZX type of the zx element
     * \tparam TYPE_ZY type of the zy element
     * \tparam TYPE_ZZ type of the zz element
     * \param xx value of the xx element
     * \param xy value of the xy element
     * \param xz value of the xz element
     * \param yx value of the yx element
     * \param yy value of the yy element
     * \param yz value of the yz element
     * \param zx value of the zx element
     * \param zy value of the zy element
     * \param zz value of the zz element
     */
    template <typename TYPE_XX, typename TYPE_XY, typename TYPE_XZ,
              typename TYPE_YX, typename TYPE_YY, typename TYPE_YZ,
              typename TYPE_ZX, typename TYPE_ZY, typename TYPE_ZZ>
    requires (
        std::is_arithmetic<TYPE_XX>::value == false &&
        std::is_arithmetic<TYPE_XY>::value == false &&
        std::is_arithmetic<TYPE_XZ>::value == false &&
        std::is_arithmetic<TYPE_YX>::value == false &&
        std::is_arithmetic<TYPE_YY>::value == false &&
        std::is_arithmetic<TYPE_YZ>::value == false &&
        std::is_arithmetic<TYPE_ZX>::value == false &&
        std::is_arithmetic<TYPE_ZY>::value == false &&
        std::is_arithmetic<TYPE_ZZ>::value == false &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_XX>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_XY>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_XZ>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_YX>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_YY>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_YZ>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_ZX>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_ZY>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_ZZ>::value
    )
    Matrix3x3(TYPE_XX xx = TYPE{0}, TYPE_XY xy = TYPE{0}, TYPE_XZ xz = TYPE{0},
              TYPE_YX yx = TYPE{0}, TYPE_YY yy = TYPE{0}, TYPE_YZ yz = TYPE{0},
              TYPE_ZX zx = TYPE{0}, TYPE_ZY zy = TYPE{0}, TYPE_ZZ zz = TYPE{0})
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

    /**
     * \brief Sets items of the matrix.
     * \tparam TYPE_XX type of the xx element
     * \tparam TYPE_XY type of the xy element
     * \tparam TYPE_XZ type of the xz element
     * \tparam TYPE_YX type of the yx element
     * \tparam TYPE_YY type of the yy element
     * \tparam TYPE_YZ type of the yz element
     * \tparam TYPE_ZX type of the zx element
     * \tparam TYPE_ZY type of the zy element
     * \tparam TYPE_ZZ type of the zz element
     * \param xx value of the xx element
     * \param xy value of the xy element
     * \param xz value of the xz element
     * \param yx value of the yx element
     * \param yy value of the yy element
     * \param yz value of the yz element
     * \param zx value of the zx element
     * \param zy value of the zy element
     * \param zz value of the zz element
     */
    template <typename TYPE_XX, typename TYPE_XY, typename TYPE_XZ,
              typename TYPE_YX, typename TYPE_YY, typename TYPE_YZ,
              typename TYPE_ZX, typename TYPE_ZY, typename TYPE_ZZ>
    requires (
        std::is_arithmetic<TYPE_XX>::value == false &&
        std::is_arithmetic<TYPE_XY>::value == false &&
        std::is_arithmetic<TYPE_XZ>::value == false &&
        std::is_arithmetic<TYPE_YX>::value == false &&
        std::is_arithmetic<TYPE_YY>::value == false &&
        std::is_arithmetic<TYPE_YZ>::value == false &&
        std::is_arithmetic<TYPE_ZX>::value == false &&
        std::is_arithmetic<TYPE_ZY>::value == false &&
        std::is_arithmetic<TYPE_ZZ>::value == false &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_XX>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_XY>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_XZ>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_YX>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_YY>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_YZ>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_ZX>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_ZY>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_ZZ>::value
    )
    void set(TYPE_XX xx = TYPE{0}, TYPE_XY xy = TYPE{0}, TYPE_XZ xz = TYPE{0},
             TYPE_YX yx = TYPE{0}, TYPE_YY yy = TYPE{0}, TYPE_YZ yz = TYPE{0},
             TYPE_ZX zx = TYPE{0}, TYPE_ZY zy = TYPE{0}, TYPE_ZZ zz = TYPE{0})
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
        transposeMatrix(*this, &result);
        return result;
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
    operator Matrix3x3<NEW_TYPE>() const
    {
        Matrix3x3<NEW_TYPE> result;
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
    Matrix3x3<TYPE> operator+(const Matrix3x3<TYPE>& mat) const
    {
        Matrix3x3<TYPE> result(*this);
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
    auto operator+(const Matrix3x3<RHS_TYPE>& mat) const
    {
        Matrix3x3<std::common_type_t<TYPE, RHS_TYPE>> result(*this);
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
    auto operator+(const Matrix3x3<RHS_TYPE>& mat) const
    {
        Matrix3x3<TYPE> result(*this);
        addMatrices(*this, mat, &result);
        return result;
    }

    /** 
     * \brief Negation operator.
     * \return negated matrix
     */
    Matrix3x3<TYPE> operator-() const
    {
        Matrix3x3<TYPE> result(*this);
        result.negate();
        return result;
    }

    /** 
     * \brief Subtraction operator.
     * \param mat matrix to be subtracted
     * \return difference of the matrices
     */
    Matrix3x3<TYPE> operator-(const Matrix3x3<TYPE>& mat) const
    {
        Matrix3x3<TYPE> result(*this);
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
    auto operator-(const Matrix3x3<TYPE>& mat) const
    {
        Matrix3x3<std::common_type_t<TYPE, RHS_TYPE>> result;
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
    auto operator-(const Matrix3x3<TYPE>& mat) const
    {
        Matrix3x3<TYPE> result;
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
        Matrix3x3<std::common_type_t<TYPE, RHS_TYPE>> result;
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
            Matrix3x3<TYPE> result;
            multiplyMatrixByScalar(*this, val, &result);
            return result;
        }
        else
        {
            Matrix3x3<RHS_TYPE> result;
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
        Matrix3x3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                >
            >
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
            Matrix3x3<
                typename units::detail::strip_angle_dimension<TYPE>::stripped_type
            > temp;
            for (unsigned int i = 0; i < this->kSize; ++i)
            {
                temp(i) = units::detail::strip_angle_dimension<TYPE>::strip((*this)(i));
            }

            Matrix3x3<
                units::unit_t<
                    units::compound_unit<
                        typename units::detail::strip_angle_dimension<TYPE>::stripped_unit,
                        typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                    >
                >
            > result;
            multiplyMatrixByScalar(temp, val, &result);
            return result;
		}
		else
		{
            typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_type temp = 
                units::detail::strip_angle_dimension<RHS_TYPE>::strip(val);

            Matrix3x3<
                units::unit_t<
                    units::compound_unit<
                        typename units::traits::unit_t_traits<TYPE>::unit_type,
                        typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_unit
                    >
                >
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
    auto operator*(const Vector3<RHS_TYPE>& vect) const
    {
        Vector3<std::common_type_t<TYPE, RHS_TYPE>> result;
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
    auto operator*(const Vector3<RHS_TYPE>& vect) const
    {
        if constexpr (units::traits::is_unit_t<TYPE>::value)
        {
            Vector3<TYPE> result;
            multiplyMatrixByVector(*this, vect, &result);
            return result;
        }
        else
        {
            Vector3<RHS_TYPE> result;
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
    auto operator*(const Vector3<RHS_TYPE>& vect) const
    {
        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                >
            >
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
    auto operator*(const Vector3<RHS_TYPE>& vect) const
    {
        if constexpr (units::traits::has_angle_dimension_t<TYPE>::value)
        {
            Matrix3x3<typename units::detail::strip_angle_dimension<TYPE>::stripped_type> temp;
            for (unsigned int i = 0; i < this->kSize; ++i)
            {
                temp(i) = units::detail::strip_angle_dimension<TYPE>::strip((*this)(i));
            }

            Vector3<
                units::unit_t<
                    units::compound_unit<
                        typename units::detail::strip_angle_dimension<TYPE>::stripped_unit,
                        typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                    >
                >
            > result;
            multiplyMatrixByVector(temp, vect, &result);
            return result;
        }
        else
        {
            Vector3<typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_type> temp;
            temp.x() = units::detail::strip_angle_dimension<RHS_TYPE>::strip(vect.x());
            temp.y() = units::detail::strip_angle_dimension<RHS_TYPE>::strip(vect.y());
            temp.z() = units::detail::strip_angle_dimension<RHS_TYPE>::strip(vect.z());

            Vector3<
                units::unit_t<
                    units::compound_unit<
                        typename units::traits::unit_t_traits<TYPE>::unit_type,
                        typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_unit
                    >
                >
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
    auto operator*(const Matrix3x3<RHS_TYPE>& mat) const
    {
        Matrix3x3<std::common_type_t<TYPE, RHS_TYPE>> result;
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
    auto operator*(const Matrix3x3<RHS_TYPE>& mat) const
    {
        if constexpr (units::traits::is_unit_t<TYPE>::value)
        {
            Matrix3x3<TYPE> result;
            multiplyMatrixByMatrix(*this, mat, &result);
            return result;
        } 
        else 
        {
            Matrix3x3<RHS_TYPE> result;
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
    auto operator*(const Matrix3x3<RHS_TYPE>& mat) const
    {
        Matrix3x3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                >
            >
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
    auto operator*(const Matrix3x3<RHS_TYPE>& mat) const
    {
        if constexpr (units::traits::has_angle_dimension_t<TYPE>::value)
        {
            Matrix3x3<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type> temp;
            for (unsigned int i = 0; i < this->kSize; ++i)
            {
                temp(i) = units::detail::strip_angle_dimension<TYPE>::strip((*this)(i));
            }

            Matrix3x3<
                units::unit_t<
                    units::compound_unit<
                        typename units::detail::strip_angle_dimension<TYPE>::stripped_unit,
                        typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                    >
                >
            > result;
            multiplyMatrixByMatrix(temp, mat, &result);
            return result;
        }
        else
        {
            Matrix3x3<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type> temp;
            for (unsigned int i = 0; i < this->kSize; ++i)
            {
                temp(i) = units::detail::strip_angle_dimension<TYPE>::strip(mat(i));
            }

            Matrix3x3<
                units::unit_t<
                    units::compound_unit<
                        typename units::traits::unit_t_traits<TYPE>::unit_type,
                        typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_unit
                    >
                >
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
        Matrix3x3<std::common_type_t<TYPE, RHS_TYPE>> result;
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
            Matrix3x3<TYPE> result;
            multiplyMatrixByScalar(*this, 1.0 / val, &result);
            return result;
        }
        else
        {
            Matrix3x3<
                units::unit_t<
                    units::inverse<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type>
                >
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
        Matrix3x3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    units::inverse<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type>
                >
            >
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
    Matrix3x3<TYPE>& operator+=(const Matrix3x3<RHS_TYPE>& mat)
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
    Matrix3x3<TYPE>& operator-=(const Matrix3x3<RHS_TYPE>& mat)
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
    Matrix3x3<TYPE>& operator*=(RHS_TYPE val)
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
    Matrix3x3<TYPE>& operator/=(RHS_TYPE val)
    {
        *this = (*this) / val;
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
