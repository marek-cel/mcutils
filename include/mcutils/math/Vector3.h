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
#ifndef MCUTILS_MATH_VECTOR3_H_
#define MCUTILS_MATH_VECTOR3_H_

#ifndef MCUTILS_MATH_VECTOR_H_
#   error "Do not include this file directly. Include <mcutils/math/Vector.h> instead."
#endif

#include <mcutils/math/VectorN.h>

namespace mc {

/**
 * \brief A template class representing a 3D vector.
 *
 * This class provides a variety of vector operations, including addition, subtraction,
 * scalar multiplication, normalization, and length calculation. It supports both
 * dimensionless and unit-based types. The vector elements are stored in a fixed-size
 * array.
 *
 * \tparam TYPE vector item type
 */
template <typename TYPE>
class Vector3 : public VectorN<TYPE, 3>
{
public:

    inline static const Vector3<TYPE> i() { return Vector3<TYPE>(TYPE{1}, TYPE{0}, TYPE{0}); }
    inline static const Vector3<TYPE> j() { return Vector3<TYPE>(TYPE{0}, TYPE{1}, TYPE{0}); }
    inline static const Vector3<TYPE> k() { return Vector3<TYPE>(TYPE{0}, TYPE{0}, TYPE{1}); }

    inline static const Vector3<TYPE> ex() { return i(); }
    inline static const Vector3<TYPE> ey() { return j(); }
    inline static const Vector3<TYPE> ez() { return k(); }

    /**
     * \brief Constructor.
     * \param x value of the x element
     * \param y value of the y element
     * \param z value of the z element
     */
    explicit Vector3(TYPE x = TYPE{0}, TYPE y = TYPE{0}, TYPE z = TYPE{0})
    {
        set(x, y, z);
    }

    /**
     * \brief Constructor.
     * \param x value of the x element
     * \param y value of the y element
     * \param z value of the z element
     */
    template <typename TYPE2>
    requires (
        std::is_arithmetic<TYPE>::value &&
        std::is_arithmetic<TYPE2>::value && 
        std::is_same<TYPE, TYPE2>::value == false
    )
    Vector3(TYPE2 x, TYPE2 y, TYPE2 z)
    {
        set(static_cast<TYPE>(x), static_cast<TYPE>(y), static_cast<TYPE>(z));
    }

    /**
     * \brief Constructor.
     * \param x value of the x element
     * \param y value of the y element
     * \param z value of the z element
     * \tparam TYPE_X type of the x element
     * \tparam TYPE_Y type of the y element
     * \tparam TYPE_Z type of the z element
     */
    template <typename TYPE_X, typename TYPE_Y, typename TYPE_Z>
    requires (
        std::is_arithmetic<TYPE_X>::value == false &&
        std::is_arithmetic<TYPE_Y>::value == false &&
        std::is_arithmetic<TYPE_Z>::value == false &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_X>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_Y>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_Z>::value
    )
    Vector3(TYPE_X x, TYPE_Y y, TYPE_Z z)
    {
        set(x, y, z);
    }

    /**
     * \brief Converting constructor.
     * \param vect other vector
     * \tparam TYPE2 type of the other vector elements
     */
    template <typename TYPE2>
    requires (
        std::is_arithmetic<TYPE2>::value == false &&
        units::traits::is_convertible_unit_t<TYPE, TYPE2>::value &&
        std::is_same<TYPE, TYPE2>::value == false
    )
    Vector3(const Vector3<TYPE>& vect)
    {
        set(vect.x(), vect.y(), vect.z());
    }

    /** \return length of projection of vector on XY-plane */
    inline TYPE getLengthXY() const { return sqrt(x()*x() + y()*y()); }

    /** \return length of projection of vector on XZ-plane */
    inline TYPE getLengthXZ() const { return sqrt(x()*x() + z()*z()); }

    /** \return length of projection of vector on YZ-plane */
    inline TYPE getLengthYZ() const { return sqrt(y()*y() + z()*z()); }

    /** \brief Returns normalized vector. */
    Vector3<double> getNormalized() const
    {
        Vector3<double> result;
        calculateNormalized(*this, &result);
        return result;
    }

    /**
     * \brief Sets vector values.
     * \param x value of the x element
     * \param y value of the y element
     * \param z value of the z element
     */
    void set(TYPE x, TYPE y, TYPE z)
    {
        this->_elements[0] = x;
        this->_elements[1] = y;
        this->_elements[2] = z;
    }

    /**
     * \brief Sets vector values.
     * \param x value of the x element
     * \param y value of the y element
     * \param z value of the z element
     * \tparam TYPE_X type of the x element
     * \tparam TYPE_Y type of the y element
     * \tparam TYPE_Z type of the z element
     */
    template <typename TYPE_X, typename TYPE_Y, typename TYPE_Z>
    requires (
        units::traits::is_unit_t<TYPE_X>::value &&
        units::traits::is_unit_t<TYPE_Y>::value &&
        units::traits::is_unit_t<TYPE_Z>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_X>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_Y>::value &&
        units::traits::is_convertible_unit_t<TYPE, TYPE_Z>::value
    )
    void set(TYPE_X x, TYPE_Y y, TYPE_Z z)
    {
        this->_elements[0] = x;
        this->_elements[1] = y;
        this->_elements[2] = z;
    }

    inline TYPE  x() const { return this->_elements[0]; }
    inline TYPE  y() const { return this->_elements[1]; }
    inline TYPE  z() const { return this->_elements[2]; }
    inline TYPE& x()       { return this->_elements[0]; }
    inline TYPE& y()       { return this->_elements[1]; }
    inline TYPE& z()       { return this->_elements[2]; }

    inline TYPE  p() const { return this->_elements[0]; }
    inline TYPE  q() const { return this->_elements[1]; }
    inline TYPE  r() const { return this->_elements[2]; }
    inline TYPE& p()       { return this->_elements[0]; }
    inline TYPE& q()       { return this->_elements[1]; }
    inline TYPE& r()       { return this->_elements[2]; }

    inline TYPE  u() const { return this->_elements[0]; }
    inline TYPE  v() const { return this->_elements[1]; }
    inline TYPE  w() const { return this->_elements[2]; }
    inline TYPE& u()       { return this->_elements[0]; }
    inline TYPE& v()       { return this->_elements[1]; }
    inline TYPE& w()       { return this->_elements[2]; }

    /**
     * \brief Casting operator.
     * Converts the vector to another type.
     */
    template <typename NEW_TYPE>
    requires (
        std::is_same<TYPE, NEW_TYPE>::value == false &&
        (std::is_arithmetic<NEW_TYPE>::value || units::traits::is_convertible_unit_t<NEW_TYPE, TYPE>::value)
    )
    operator Vector3<NEW_TYPE>() const
    {
        Vector3<NEW_TYPE> result;
        result.x() = static_cast<NEW_TYPE>(this->_elements[0]);
        result.y() = static_cast<NEW_TYPE>(this->_elements[1]);
        result.z() = static_cast<NEW_TYPE>(this->_elements[2]);
        return result;
    }

    /** 
     * \brief Addition operator. 
     * \param rhs right-hand side vector
     * \return sum of the two vectors
     */
    Vector3<TYPE> operator+(const Vector3<TYPE>& rhs) const
    {
        Vector3<TYPE> result;
        addVectors(*this, rhs, &result);
        return result;
    }

    /** 
     * \brief Addition operator. 
     * 
     * This template is enabled when TYPE and RHS_TYPE are both arithmetic types.
     * 
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs right-hand side vector
     * \return sum of the two vectors
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value  && 
        std::is_arithmetic<RHS_TYPE>::value && 
        std::is_same<TYPE, RHS_TYPE>::value == false
    )
    auto operator+(const Vector3<RHS_TYPE>& rhs) const
    {
        Vector3<std::common_type_t<TYPE, RHS_TYPE>> result;
        addVectors(*this, rhs, &result);
        return result;
    }

    /** 
     * \brief Addition operator. 
     * 
     * This template is enabled when TYPE and RHS_TYPE are convertible units.
     * 
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs right-hand side vector
     * \return sum of the two vectors
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value == false && 
        std::is_arithmetic<RHS_TYPE>::value == false &&
        std::is_same<TYPE, RHS_TYPE>::value == false &&
        units::traits::is_convertible_unit_t<TYPE, RHS_TYPE>::value
    )
    Vector3<TYPE> operator+(const Vector3<RHS_TYPE>& rhs) const
    {
        Vector3<TYPE> result;
        addVectors(*this, rhs, &result);
        return result;
    }

    /** \brief Negation operator. */
    Vector3<TYPE> operator-() const
    {
        Vector3<TYPE> result(*this);
        result.negate();
        return result;
    }

    /** 
     * \brief Subtraction operator. 
     * \param rhs right-hand side vector
     * \return difference of the vectors
     */
    Vector3<TYPE> operator-(const Vector3<TYPE>& rhs) const
    {
        Vector3<TYPE> result;
        substractVectors(*this, rhs, &result);
        return result;
    }

    /**
     * \brief Substraction operator.
     * 
     * This template is enabled when TYPE and RHS_TYPE are both arithmetic types.
     * 
     * \param rhs right-hand side vector
     * \return difference of the vectors
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value  && 
        std::is_arithmetic<RHS_TYPE>::value && 
        std::is_same<TYPE, RHS_TYPE>::value == false
    )
    auto operator-(const Vector3<RHS_TYPE>& rhs) const
    {
        Vector3<std::common_type_t<TYPE, RHS_TYPE>> result;
        substractVectors(*this, rhs, &result);
        return result;
    }

    /**
     * \brief Substraction operator.
     * 
     * This template is enabled when TYPE and RHS_TYPE are convertible units.
     * 
     * \param rhs right-hand side vector
     * \return difference of the vectors
     */
    template <typename RHS_TYPE>
    requires (
        std::is_arithmetic<TYPE>::value == false && 
        std::is_arithmetic<RHS_TYPE>::value == false &&
        std::is_same<TYPE, RHS_TYPE>::value == false &&
        units::traits::is_convertible_unit_t<TYPE, RHS_TYPE>::value
    )
    Vector3<TYPE> operator-(const Vector3<RHS_TYPE>& rhs) const
    {
        Vector3<TYPE> result;
        substractVectors(*this, rhs, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     * 
     * This template is enabled when TYPE and RHS_TYPE are both arithmetic types.
     * 
     * \tparam TYPE_RHS RHS operand type
     * \param rhs right-hand side value
     * \return product of the vector multiplied by the value
     */
    template <typename RHS_TYPE>
    requires (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    auto operator*(const RHS_TYPE& rhs) const
    {
        Vector3<std::common_type_t<TYPE, RHS_TYPE>> result;
        multiplyVectorByScalar(*this, rhs, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     * 
     * This template is enabled when TYPE or TYPE_RHS is an arithmetic type
     * while the other is a unit.
     * 
     * \tparam TYPE_RHS RHS operand type
     * \param rhs right-hand side value
     * \return product of the vector multiplied by the value
     */
    template <typename RHS_TYPE>
    requires (
        (units::traits::is_unit_t<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
        (std::is_arithmetic<TYPE>::value && units::traits::is_unit_t<RHS_TYPE>::value)
    )
    auto operator*(const RHS_TYPE& rhs) const
    {
        if constexpr (units::traits::is_unit_t<TYPE>::value)
        {
            Vector3<TYPE> result;
            multiplyVectorByScalar(*this, rhs, &result);
            return result;
        }
        else
        {
            Vector3<RHS_TYPE> result;
            multiplyVectorByScalar(*this, rhs, &result);
            return result;
        }

    }

    /**
     * \brief Multiplication by a scalar operator.
     * 
     * This template is enabled when both TYPE and TYPE_RHS are units and angle stripping is not needed.
     * 
     * \tparam TYPE_RHS RHS operand type
     * \param rhs right-hand side value
     * \return product of the vector multiplied by the value
     */
    template <typename RHS_TYPE>
    requires (
        units::traits::is_unit_t<TYPE>::value && 
        units::traits::is_unit_t<RHS_TYPE>::value &&
        units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value == false
    )
    auto operator*(const RHS_TYPE& rhs) const
    {
        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                >
            >
        > result;
        multiplyVectorByScalar(*this, rhs, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     * 
     * This template is enabled when both TYPE and TYPE_RHS are units and angle stripping is needed.
     * 
     * \tparam TYPE_RHS RHS operand type
     * \param rhs right-hand side value
     * \return product of the vector multiplied by the value
     */
    template <typename RHS_TYPE>
    requires (units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value)
    auto operator*(const RHS_TYPE& rhs) const
    {
		if constexpr (units::traits::has_angle_dimension_t<TYPE>::value)
		{
            Vector3<typename units::detail::strip_angle_dimension<TYPE>::stripped_type> temp;
            temp.x() = units::detail::strip_angle_dimension<TYPE>::strip((*this).x());
            temp.y() = units::detail::strip_angle_dimension<TYPE>::strip((*this).y());
            temp.z() = units::detail::strip_angle_dimension<TYPE>::strip((*this).z());

            Vector3<
                units::unit_t<
                    units::compound_unit<
                        typename units::detail::strip_angle_dimension<TYPE>::stripped_unit,
                        typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                    >
                >
            > result;
            multiplyVectorByScalar(temp, rhs, &result);
            return result;
		}
		else
		{
            typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_type temp = 
                units::detail::strip_angle_dimension<RHS_TYPE>::strip(rhs);

            Vector3<
                units::unit_t<
                    units::compound_unit<
                        typename units::traits::unit_t_traits<TYPE>::unit_type,
                        typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_unit
                    >
                >
            > result;
            multiplyVectorByScalar(*this, temp, &result);
            return result;
		}
    }

    /**
     * \brief Dot product operator.
     * 
     * This template is enabled when TYPE and RHS_TYPE are both arithmetic types.
     * 
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs right-hand side vector
     * \return dot product of the vectors
     */
    template <typename RHS_TYPE>
    requires (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    auto operator*(const Vector3<RHS_TYPE>& rhs) const
    {
        std::common_type_t<TYPE, RHS_TYPE> result;
        calculateDotProduct(*this, rhs, &result);
        return result;
    }

    /**
     * \brief Dot product operator.
     * 
     * This template is enabled when TYPE or TYPE_RHS is an arithmetic type
     * while the other is a unit.
     * 
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs right-hand side vector
     * \return dot product of the vectors
     */
    template <typename RHS_TYPE>
    requires (
        (units::traits::is_unit_t<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
        (std::is_arithmetic<TYPE>::value && units::traits::is_unit_t<RHS_TYPE>::value)
    )
    auto operator*(const Vector3<RHS_TYPE>& rhs) const
    {
        if constexpr (units::traits::is_unit_t<TYPE>::value)
        {
            TYPE result;
            calculateDotProduct(*this, rhs, &result);
            return result;
        }
        else
        {
            RHS_TYPE result;
            calculateDotProduct(*this, rhs, &result);
            return result;
        }
    }

    /**
     * \brief Dot product operator.
     * 
     * This template is enabled when TYPE and RHS_TYPE are both units and angle stripping is not needed.
     * 
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs right-hand side vector
     * \return dot product of the vectors
     */
    template <typename RHS_TYPE>
    requires (
        units::traits::is_unit_t<TYPE>::value && 
        units::traits::is_unit_t<RHS_TYPE>::value &&
        units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value == false
    )
    auto operator*(const Vector3<RHS_TYPE>& rhs) const
    {
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<TYPE>::unit_type,
                typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
            >
        > result;
        calculateDotProduct(*this, rhs, &result);
        return result;
    }

    /**
     * \brief Dot product operator.
     * 
     * This template is enabled when TYPE and RHS_TYPE are both units and angle stripping is needed.
     * 
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs right-hand side vector
     * \return dot product of the vectors
     */
    template <typename RHS_TYPE>
    requires units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value
    auto operator*(const Vector3<RHS_TYPE>& rhs) const
    {
		if constexpr (units::traits::has_angle_dimension_t<TYPE>::value)
		{
            Vector3<typename units::detail::strip_angle_dimension<TYPE>::stripped_type> temp;
            temp.x() = units::detail::strip_angle_dimension<TYPE>::strip((*this).x());
            temp.y() = units::detail::strip_angle_dimension<TYPE>::strip((*this).y());
            temp.z() = units::detail::strip_angle_dimension<TYPE>::strip((*this).z());

            units::unit_t<
                units::compound_unit<
                    typename units::detail::strip_angle_dimension<TYPE>::stripped_unit,
                    typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                >
            > result;
            calculateDotProduct(temp, rhs, &result);
            return result;
		}
		else
		{
            Vector3<typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_type> temp;
            temp.x() = units::detail::strip_angle_dimension<RHS_TYPE>::strip(rhs.x());
            temp.y() = units::detail::strip_angle_dimension<RHS_TYPE>::strip(rhs.y());
            temp.z() = units::detail::strip_angle_dimension<RHS_TYPE>::strip(rhs.z());

            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_unit
                >
            > result;
            calculateDotProduct(*this, temp, &result);
            return result;
		}
    }

    /**
     * \brief Division by a scalar operator.
     * 
     * This template is enabled when TYPE and RHS_TYPE are both arithmetic types.
     * 
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs right-hand side value
     * \return vector divided by the value
     */
    template <typename RHS_TYPE>
    requires (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    auto operator/(const RHS_TYPE& rhs) const
    {
        Vector3<std::common_type_t<TYPE, RHS_TYPE>> result;
        multiplyVectorByScalar(*this, 1.0 / rhs, &result);
        return result;
    }

    /**
     * \brief Division by a scalar operator.
     * 
     * This template is enabled when TYPE or TYPE_RHS is an arithmetic type
     * while the other is a unit.
     * 
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs right-hand side value
     * \return vector divided by the value
     */
    template <typename RHS_TYPE>
    requires (
        (std::is_arithmetic<TYPE>::value && units::traits::is_unit_t<RHS_TYPE>::value) ||
        (units::traits::is_unit_t<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    )
    auto operator/(const RHS_TYPE& rhs) const
    {
        if constexpr (units::traits::is_unit_t<TYPE>::value)
        {
            Vector3<TYPE> result;
            multiplyVectorByScalar(*this, 1.0 / rhs, &result);
            return result;
        }
        else
        {
            Vector3<
                units::unit_t<
                    units::inverse<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type>
                >
            > result;
            multiplyVectorByScalar(*this, 1.0 / rhs, &result);
            return result;
        }
    }

    /**
     * \brief Division by a scalar operator.
     * 
     * This template is enabled when TYPE and RHS_TYPE are both units.
     * 
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs right-hand side value
     * \return vector divided by the value
     */
    template <typename RHS_TYPE>
    requires (units::traits::is_unit_t<TYPE>::value && units::traits::is_unit_t<RHS_TYPE>::value)
    auto operator/(const RHS_TYPE& rhs) const
    {
        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    units::inverse<typename units::traits::unit_t_traits<RHS_TYPE>::unit_type>
                >
            >
        > result;
        multiplyVectorByScalar(*this, 1.0 / rhs, &result);
        return result;
    }

    /**
     * \brief Cross product operator.
     * 
     * This template is enabled when TYPE and RHS_TYPE are both arithmetic types.
     * 
     * \tparam TYPE_RHS RHS operand type
     * \param rhs right-hand side vector
     * \return product of the vector multiplied by the value
     */
    template <typename RHS_TYPE>
    requires (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value)
    auto operator%(const Vector3<RHS_TYPE>& rhs) const
    {
        Vector3<std::common_type_t<TYPE, RHS_TYPE>> result;
        calculateCrossProduct(*this, rhs, &result);
        return result;
    }

    /**
     * \brief Cross product operator.
     * 
     * This template is enabled when TYPE or TYPE_RHS is an arithmetic type
     * while the other is a unit.
     * 
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs right-hand side vector
     * \return dot product of the vectors
     */
    template <typename RHS_TYPE>
    requires (
        (units::traits::is_unit_t<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
        (std::is_arithmetic<TYPE>::value && units::traits::is_unit_t<RHS_TYPE>::value)
    )
    auto operator%(const Vector3<RHS_TYPE>& rhs) const
    {
        if constexpr (units::traits::is_unit_t<TYPE>::value)
        {
            Vector3<TYPE> result;
            calculateCrossProduct(*this, rhs, &result);
            return result;
        }
        else
        {
            Vector3<RHS_TYPE> result;
            calculateCrossProduct(*this, rhs, &result);
            return result;
        }
    }

    /**
     * \brief Cross product operator.
     * 
     * This template is enabled when TYPE and RHS_TYPE are both units and angle stripping is not needed.
     * 
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs right-hand side vector
     * \return dot product of the vectors
     */
    template <typename RHS_TYPE>
    requires (
        units::traits::is_unit_t<TYPE>::value && 
        units::traits::is_unit_t<RHS_TYPE>::value &&
        units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value == false
    )
    auto operator%(const Vector3<RHS_TYPE>& rhs) const
    {
        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                >
            >
        > result;
        calculateCrossProduct(*this, rhs, &result);
        return result;
    }

    /**
     * \brief Cross product operator.
     * 
     * This template is enabled when TYPE and RHS_TYPE are both units and angle stripping is needed.
     * 
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs right-hand side vector
     * \return dot product of the vectors
     */
    template <typename RHS_TYPE>
    requires units::traits::need_angle_stripping_t<TYPE, RHS_TYPE>::value
    auto operator%(const Vector3<RHS_TYPE>& rhs) const
    {
		if constexpr (units::traits::has_angle_dimension_t<TYPE>::value)
		{
            Vector3<typename units::detail::strip_angle_dimension<TYPE>::stripped_type> temp;
            temp.x() = units::detail::strip_angle_dimension<TYPE>::strip((*this).x());
            temp.y() = units::detail::strip_angle_dimension<TYPE>::strip((*this).y());
            temp.z() = units::detail::strip_angle_dimension<TYPE>::strip((*this).z());

            Vector3<
                units::unit_t<
                    units::compound_unit<
                        typename units::detail::strip_angle_dimension<TYPE>::stripped_unit,
                        typename units::traits::unit_t_traits<RHS_TYPE>::unit_type
                    >
                >
            > result;
            calculateCrossProduct(temp, rhs, &result);
            return result;
		}
		else
		{
            Vector3<typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_type> temp;
            temp.x() = units::detail::strip_angle_dimension<RHS_TYPE>::strip(rhs.x());
            temp.y() = units::detail::strip_angle_dimension<RHS_TYPE>::strip(rhs.y());
            temp.z() = units::detail::strip_angle_dimension<RHS_TYPE>::strip(rhs.z());

            Vector3<
                units::unit_t<
                    units::compound_unit<
                        typename units::traits::unit_t_traits<TYPE>::unit_type,
                        typename units::detail::strip_angle_dimension<RHS_TYPE>::stripped_unit
                    >
                >
            > result;
            calculateCrossProduct(*this, temp, &result);
            return result;
		}
    }

    /**
     * \brief Unary addition operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs vector to be added
     * \return reference to the updated vector
     */
    template <typename RHS_TYPE>
    requires (
        (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
        units::traits::is_convertible_unit_t<TYPE, RHS_TYPE>::value
    )
    Vector3<TYPE>& operator+=(const Vector3<RHS_TYPE>& rhs)
    {
        addVectors(*this, rhs, this);
        return *this;
    }

    /**
     * \brief Unary subtraction operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs vector to be subtracted
     * \return reference to the updated vector
     */
    template <typename RHS_TYPE>
    requires (
        (std::is_arithmetic<TYPE>::value && std::is_arithmetic<RHS_TYPE>::value) ||
        units::traits::is_convertible_unit_t<TYPE, RHS_TYPE>::value
    )
    Vector3<TYPE>& operator-=(const Vector3<RHS_TYPE>& rhs)
    {
        substractVectors(*this, rhs, this);
        return *this;
    }

    /**
     * \brief Unary multiplication operator.
     * \tparam RHS_TYPE type of the right-hand side vector elements
     * \param rhs value to multiply the vector by
     * \return reference to the updated vector
     */
    template <typename RHS_TYPE>
    requires std::is_arithmetic<RHS_TYPE>::value
    Vector3<TYPE>& operator*=(RHS_TYPE rhs)
    {
        *this = (*this) * rhs;
        return *this;
    }

    /**
     * \brief Unary division operator.
     * \param rhs value to divide the vector by
     * \return reference to the updated vector
     */
    template <typename RHS_TYPE>
    requires std::is_arithmetic<RHS_TYPE>::value
    Vector3<TYPE>& operator/=(RHS_TYPE rhs)
    {
        *this = (*this) / rhs;
        return *this;
    }
};

/** 
 * \brief Cross product calculation algorithm. 
 * \tparam LHS_TYPE type of the left-hand side vector elements
 * \tparam RHS_TYPE type of the right-hand side vector elements
 * \tparam RESULT_TYPE type of the result vector elements
 * \param lhs left-hand side vector
 * \param rhs right-hand side vector
 * \param result pointer to the result vector
 */
template <typename LHS_TYPE, typename RHS_TYPE, typename RESULT_TYPE>
void calculateCrossProduct(
    const Vector3<LHS_TYPE>& lhs, 
    const Vector3<RHS_TYPE>& rhs, 
    Vector3<RESULT_TYPE>* result
)
{
    result->x() = lhs.y() * rhs.z() - lhs.z() * rhs.y();
    result->y() = lhs.z() * rhs.x() - lhs.x() * rhs.z();
    result->z() = lhs.x() * rhs.y() - lhs.y() * rhs.x();
}

/**
 * \brief Multiplication operator.
 *
 * This is an operator for multiplying a scalar by a vector, which is commutative.
 * 
 * \tparam LHS_TYPE type of the left-hand side scalar
 * \tparam RHS_TYPE type of the right-hand side vector elements
 * \param value scalar value
 * \param vect vector to be multiplied
 * \return product of the vector multiplied by the value
 */
template <typename LHS_TYPE, typename RHS_TYPE>
requires (
    std::is_arithmetic<LHS_TYPE>::value ||
    units::traits::is_unit_t<LHS_TYPE>::value
)
auto operator*(LHS_TYPE value, const Vector3<RHS_TYPE>& vect)
{
    return vect * value;
}

} // namespace mc

#endif // MCUTILS_MATH_VECTOR3_H_
