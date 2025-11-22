/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/
#ifndef MCUTILS_MATH_VECTOR3_H_
#define MCUTILS_MATH_VECTOR3_H_

#ifndef MCUTILS_MATH_VECTOR_H_
#   error "Do not include this file directly. Include <mcsim/utils/math/Vector.h> instead."
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
     * \param x value of the first element
     * \param y value of the second element
     * \param z value of the third element
     */
    explicit Vector3(TYPE x = TYPE{0}, TYPE y = TYPE{0}, TYPE z = TYPE{0})
    {
        set(x, y, z);
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
        this->calculateNormalized(*this, &result);
        return result;
    }

    /** \brief Converts the vector to a dimensionless vector. */
    inline Vector3<double> getDimensionless() const
    {
        Vector3<double> result;
        result.x() = static_cast<double>(this->_elements[0]);
        result.y() = static_cast<double>(this->_elements[1]);
        result.z() = static_cast<double>(this->_elements[2]);
        return result;
    }

    /** \brief Sets vector values. */
    void set(TYPE x, TYPE y, TYPE z)
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

    /** \brief Casting operator. */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value
        &&
        units::traits::is_convertible_unit_t<TYPE, TYPE2>::value, int>::type = 0
    >
    operator Vector3<TYPE2>() const
    {
        Vector3<TYPE2> result;
        for (unsigned int i = 0; i < this->kSize; ++i)
        {
            result(i) = this->_elements[i];
        }
        return result;
    }

    /** \brief Addition operator. */
    Vector3<TYPE> operator+(const Vector3<TYPE>& vect) const
    {
        Vector3<TYPE> result(*this);
        result.add(vect);
        return result;
    }

    /** \brief Negation operator. */
    Vector3<TYPE> operator-() const
    {
        Vector3<TYPE> result(*this);
        result.negate();
        return result;
    }

    /** \brief Subtraction operator. */
    Vector3<TYPE> operator-(const Vector3<TYPE>& vect) const
    {
        Vector3<TYPE> result(*this);
        result.subtract(vect);
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
     * This template is enabled when TYPE and TYPE2 are both units, but not angular velocity
     * or angular acceleration, or when TYPE2 is a time unit.
     *
     * \tparam TYPE2 RHS operand type
     * \param value value to be multiplied by
     * \return product of the vector multiplied by the value
     */
    template <class TYPE2, typename std::enable_if<
        (
            !units::traits::is_convertible_unit_t<TYPE, units::angular_velocity::radians_per_second_t>::value
            &&
            !units::traits::is_convertible_unit_t<TYPE, units::angular_acceleration::radians_per_second_squared_t>::value
            &&
            !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
            &&
            !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
            ||
            units::traits::is_convertible_unit_t<TYPE2, units::time::second_t>::value
        )
        &&
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator*(TYPE2 value) const
    {
        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<TYPE2>::unit_type
                >
            >
        > result;
        this->multiplyVectorByValue(*this, value, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     *
     * This is a specialization for the case when the vector is angular velocity.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This specialization is enabled when TYPE is angular velocity and TYPE2 is a unit other than
     * angular velocity, angular acceleration or time.
     *
     * \tparam TYPE2 RHS operand type
     * \param value value to be multiplied by
     * \return product of the vector multiplied by the value
     */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_convertible_unit_t<TYPE, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::time::second_t>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator*(TYPE2 value) const
    {
        Vector3<units::angular_velocity::radians_per_second_t> temp_rad_per_s = *this;
        Vector3<units::auxiliary::per_second_t> temp;
        temp.x() = units::auxiliary::per_second_t{ temp_rad_per_s.x()() };
        temp.y() = units::auxiliary::per_second_t{ temp_rad_per_s.y()() };
        temp.z() = units::auxiliary::per_second_t{ temp_rad_per_s.z()() };

        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE2>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
                >
            >
        > result;
        this->multiplyVectorByValue(temp, value, &result);
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
     * \tparam TYPE2 RHS operand type
     * \param value value to be multiplied by
     * \return product of the vector multiplied by the value
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

        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
                >
            >
        > result;
        this->multiplyVectorByValue(*this, temp, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     *
     * This is a specialization for the case when the vector is angular acceleration.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This specialization is enabled when TYPE is angular acceleration and TYPE2 is a unit other than
     * angular velocity, angular acceleration or time.
     *
     * \tparam TYPE2 RHS operand type
     * \param value value to be multiplied by
     * \return product of the vector multiplied by the value
     */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_convertible_unit_t<TYPE, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::time::second_t>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator*(TYPE2 value) const
    {
        Vector3<units::angular_acceleration::radians_per_second_squared_t> temp_rad_per_s_sq = *this;
        Vector3<units::auxiliary::per_second_squared_t> temp;
        temp.x() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.x()() };
        temp.y() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.y()() };
        temp.z() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.z()() };

        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE2>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
                >
            >
        > result;
        this->multiplyVectorByValue(temp, value, &result);
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
     * \tparam TYPE2 RHS operand type
     * \param value value to be multiplied by
     * \return product of the vector multiplied by the value
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

        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
                >
            >
        > result;
        this->multiplyVectorByValue(*this, temp, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     *
     * This is a specialization for the case when the vector is dimensionless.
     */
    template <class TYPE2, typename std::enable_if<
        !units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    Vector3<TYPE2> operator*(TYPE2 value) const
    {
        Vector3<TYPE2> result;
        this->multiplyVectorByValue(*this, value, &result);
        return result;
    }

    /**
     * \brief Multiplication by a scalar operator.
     *
     * This is a specialization for the case when the value is dimensionless.
     *
     * \tparam TYPE2 RHS operand type
     * \param value [-] value to be multiplied by
     * \return product of the vector multiplied by the value
     */
    Vector3<TYPE> operator*(double value) const
    {
        Vector3<TYPE> result;
        this->multiplyVectorByValue(*this, value, &result);
        return result;
    }

    /**
     * \brief Calculates the dot product of two vectors.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     * So operators for angular velocity and angular acceleration are defined
     * as specializations of this template.
     *
     * This template is enabled when TYPE and TYPE2 are both units, but not angular velocity
     * or angular acceleration.
     *
     * \tparam TYPE2 RHS vector type
     * \param vect RHS vector
     * \return dot product of two vectors
     */
    template <class TYPE2, typename std::enable_if<
        !units::traits::is_convertible_unit_t<TYPE, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
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
        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<TYPE>::unit_type,
                typename units::traits::unit_t_traits<TYPE2>::unit_type
            >
        > result {0};
        this->calculateDotProduct(*this, vect, &result);
        return result;
    }

    /**
     * \brief Calculates the dot product of two vectors.
     *
     * This is a specialization for the case when the first vector is angular velocity.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This specialization is enabled when TYPE is angular velocity and TYPE2 is a unit other than
     * angular velocity or angular acceleration.
     *
     * \tparam TYPE2 RHS vector type
     * \param vect RHS vector
     * \return dot product of two vectors
     */
    template <typename TYPE2, typename std::enable_if<
        units::traits::is_convertible_unit_t<TYPE, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator*(const Vector3<TYPE2>& vect) const
    {
        Vector3<units::angular_velocity::radians_per_second_t> temp_rad_per_s = *this;
        Vector3<units::auxiliary::per_second_t> temp;
        temp.x() = units::auxiliary::per_second_t{ temp_rad_per_s.x()() };
        temp.y() = units::auxiliary::per_second_t{ temp_rad_per_s.y()() };
        temp.z() = units::auxiliary::per_second_t{ temp_rad_per_s.z()() };

        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<TYPE2>::unit_type,
                typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
            >
        > result {0};
        this->calculateDotProduct(temp, vect, &result);
        return result;
    }

    /**
     * \brief Calculates the dot product of two vectors.
     *
     * This is a specialization for the case when the second vector is angular velocity.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This specialization is enabled when TYPE is a unit and TYPE2 is angular velocity.
     *
     * \tparam TYPE2 RHS vector type (angular velocity, eg. units::angular_velocity::radians_per_second_t)
     * \param vect [angular velocity, eg. rad/s] RHS vector
     * \return dot product of two vectors
     */
    template <typename TYPE2, typename std::enable_if<
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

        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<TYPE>::unit_type,
                typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
            >
        > result {0};
        this->calculateDotProduct(*this, temp, &result);
        return result;
    }

    /**
     * \brief Calculates the dot product of two vectors.
     *
     * This is a specialization for the case when the first vector is angular acceleration.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This specialization is enabled when TYPE is angular acceleration and TYPE2 is a unit other than
     * angular velocity or angular acceleration.
     *
     * \tparam TYPE2 RHS vector type
     * \param vect RHS vector
     * \return dot product of two vectors
     */
    template <typename TYPE2, typename std::enable_if<
        units::traits::is_convertible_unit_t<TYPE, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator*(const Vector3<TYPE2>& vect) const
    {
        Vector3<units::angular_acceleration::radians_per_second_squared_t> temp_rad_per_s_sq = *this;
        Vector3<units::auxiliary::per_second_squared_t> temp;
        temp.x() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.x()() };
        temp.y() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.y()() };
        temp.z() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.z()() };

        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<TYPE2>::unit_type,
                typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
            >
        > result {0};
        this->calculateDotProduct(temp, vect, &result);
        return result;
    }

    /**
     * \brief Calculates the dot product of two vectors.
     *
     * This is a specialization for the case when the second vector is angular acceleration.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This specialization is enabled when TYPE is a unit and TYPE2 is angular acceleration.
     *
     * \tparam TYPE2 RHS vector type
     * \param vect [angular acceleration, eg. rad/s^2] RHS vector
     * \return dot product of two vectors
     */
    template <typename TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_convertible_unit_t<
            TYPE2, units::angular_acceleration::radians_per_second_squared_t
        >::value, int>::type = 0
    >
    auto operator*(const Vector3<TYPE2>& vect) const
    {
        Vector3<units::angular_acceleration::radians_per_second_squared_t> temp_rad_per_s_sq = vect;
        Vector3<units::auxiliary::per_second_squared_t> temp;
        temp.x() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.x()() };
        temp.y() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.y()() };
        temp.z() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.z()() };

        units::unit_t<
            units::compound_unit<
                typename units::traits::unit_t_traits<TYPE>::unit_type,
                typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
            >
        > result {0};
        this->calculateDotProduct(*this, temp, &result);
        return result;
    }

    /**
     * \brief Calculates the dot product of two vectors.
     *
     * This is a specialization for the case when the first vector is dimensionless.
     *
     * \tparam TYPE2 RHS vector type
     * \param vect RHS vector
     * \return dot product of two vectors
     */
    template <typename TYPE2, typename std::enable_if<
        !units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    TYPE2 operator*(const Vector3<TYPE2>& vect) const
    {
        TYPE2 result {0};
        this->calculateDotProduct(*this, vect, &result);
        return result;
    }

    /**
     * \brief Calculates the dot product of two vectors.
     *
     * This is a specialization for the case when the second vector is dimensionless.
     *
     * \tparam TYPE2 RHS vector type (dimensionless)
     * \param vect [-] RHS vector
     * \return dot product of two vectors
     */
    template <typename TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        !units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    TYPE operator*(const Vector3<TYPE2>& vect) const
    {
        TYPE result {0};
        this->calculateDotProduct(*this, vect, &result);
        return result;
    }

    /**
     * \brief Calculates the dot product of two vectors.
     *
     * This is a specialization for the case when both vectors are dimensionless.
     *
     * \tparam TYPE2 RHS vector type (dimensionless)
     * \param vect [-] RHS vector
     * \return dot product of two vectors
     */
    template <typename TYPE2, typename std::enable_if<
        !units::traits::is_unit_t<TYPE>::value
        &&
        !units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    double operator*(const Vector3<TYPE2>& vect) const
    {
        double result = 0.0;
        this->calculateDotProduct(*this, vect, &result);
        return result;
    }

    /**
     * \brief Division by scalar operator.
     *
     * \tparam TYPE2 RHS operand type
     * \param value value to divide the vector by
     * \return result of the division
     */
    template <class TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator/(TYPE2 value) const
    {
        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    units::inverse<typename units::traits::unit_t_traits<TYPE2>::unit_type>
                >
            >
        > result;
        this->multiplyVectorByValue(*this, 1.0 / value, &result);
        return result;
    }

    /**
     * \brief Division by scalar operator.
     *
     * This is a specialization for the case when the vector is a dimensionless.
     *
     * \param value [-] value to divide the vector by
     * \return result of the division
     */
    template <class TYPE2, typename std::enable_if<
        !units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator/(TYPE2 value) const
    {
        Vector3<
            units::unit_t<
                units::compound_unit<
                    units::inverse<typename units::traits::unit_t_traits<TYPE2>::unit_type>
                >
            >
        > result;
        this->multiplyVectorByValue(*this, 1.0 / value, &result);
        return result;
    }

    /**
     * \brief Division by scalar operator.
     *
     * This is a specialization for the case when the value is a number.
     *
     * \param value [-] value to divide the vector by
     * \return result of the division
     */
    Vector3<TYPE> operator/(double value) const
    {
        Vector3<TYPE> result;
        this->multiplyVectorByValue(*this, 1.0 / value, &result);
        return result;
    }

    /**
     * \brief Calculates the cross product of two vectors.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This template is enabled when TYPE and TYPE2 are both units, but not angular velocity
     * or angular acceleration.
     */
    template <class TYPE2, typename std::enable_if<
        !units::traits::is_convertible_unit_t<TYPE, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator%(const Vector3<TYPE2>& vect)
    {
        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<TYPE2>::unit_type
                >
            >
        > result;
        calculateCrossProduct(*this, vect, &result);
        return result;
    }

    /**
     * \brief Calculates the cross product of two vectors.
     *
     * This is a specialization for the case when the first vector is angular velocity.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This specialization is enabled when TYPE is angular velocity and TYPE2 is a unit other than
     * angular velocity or angular acceleration.
     *
     * Example: calculating linear velocity from angular velocity and radius.
     * v = omega x r
     *
     * \tparam TYPE2 RHS operand type
     * \param vect RHS vector
     * \return cross product of two vectors
     */
    template <typename TYPE2, typename std::enable_if<
        units::traits::is_convertible_unit_t<TYPE, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator%(const Vector3<TYPE2>& vect)
    {
        Vector3<units::angular_velocity::radians_per_second_t> temp_rad_per_s = *this;
        Vector3<units::auxiliary::per_second_t> temp;
        temp.x() = units::auxiliary::per_second_t{ temp_rad_per_s.x()() };
        temp.y() = units::auxiliary::per_second_t{ temp_rad_per_s.y()() };
        temp.z() = units::auxiliary::per_second_t{ temp_rad_per_s.z()() };

        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE2>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_t>::unit_type
                >
            >
        > result;
        calculateCrossProduct(temp, vect, &result);
        return result;
    }

    /**
     * \brief Calculates the cross product of two vectors.
     *
     * This is a specialization for the case when the second vector is angular velocity.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This specialization is enabled when TYPE is a unit and TYPE2 is angular velocity.
     *
     * \tparam TYPE2 RHS operand type
     * \param vect [angular velocity, eg. rad/s] RHS vector
     * \return cross product of two vectors
     */
    template <typename TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_convertible_unit_t<
            TYPE2, units::angular_velocity::radians_per_second_t
        >::value, int>::type = 0
    >
    auto operator%(const Vector3<TYPE2>& vect)
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
        calculateCrossProduct(*this, temp, &result);
        return result;
    }

    /**
     * \brief Calculates the cross product of two vectors.
     *
     * This is a specialization for the case when the first vector is angular acceleration.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This specialization is enabled when TYPE is angular acceleration and TYPE2 is a unit other than
     * angular velocity or angular acceleration.
     *
     * Example: calculating Euler acceleration from angular acceleration and radius.
     * a = alpha x r
     *
     * \tparam TYPE2 RHS operand type
     * \param vect RHS vector
     * \return cross product of two vectors
     */
    template <typename TYPE2, typename std::enable_if<
        units::traits::is_convertible_unit_t<TYPE, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_velocity::radians_per_second_t>::value
        &&
        !units::traits::is_convertible_unit_t<TYPE2, units::angular_acceleration::radians_per_second_squared_t>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    auto operator%(const Vector3<TYPE2>& vect)
    {
        Vector3<units::angular_acceleration::radians_per_second_squared_t> temp_rad_per_s_sq = *this;
        Vector3<units::auxiliary::per_second_squared_t> temp;
        temp.x() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.x()() };
        temp.y() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.y()() };
        temp.z() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.z()() };

        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE2>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
                >
            >
        > result;
        calculateCrossProduct(temp, vect, &result);
        return result;
    }

    /**
     * \brief Calculates the cross product of two vectors.
     *
     * This is a specialization for the case when the second vector is angular acceleration.
     *
     * As radians can be treated as dimensionless ratio of two lengths: arc length and radius,
     * this makes radians a pure number without physical dimension.
     *
     * This specialization is enabled when TYPE is a unit and TYPE2 is angular acceleration.
     *
     * \tparam TYPE2 RHS operand type
     * \param vect [angular acceleration, eg. rad/s^2] RHS vector
     * \return cross product of two vectors
     */
    template <typename TYPE2, typename std::enable_if<
        units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_convertible_unit_t<
            TYPE2, units::angular_acceleration::radians_per_second_squared_t
        >::value, int>::type = 0
    >
    auto operator%(const Vector3<TYPE2>& vect) const
    {
        Vector3<units::angular_acceleration::radians_per_second_squared_t> temp_rad_per_s_sq = vect;
        Vector3<units::auxiliary::per_second_squared_t> temp;
        temp.x() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.x()() };
        temp.y() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.y()() };
        temp.z() = units::auxiliary::per_second_squared_t{ temp_rad_per_s_sq.z()() };

        Vector3<
            units::unit_t<
                units::compound_unit<
                    typename units::traits::unit_t_traits<TYPE>::unit_type,
                    typename units::traits::unit_t_traits<units::auxiliary::per_second_squared_t>::unit_type
                >
            >
        > result;
        calculateCrossProduct(*this, temp, &result);
        return result;
    }

    /**
     * \brief Calculates the cross product of two vectors.
     *
     * This is a specialization for the case when the first vector is dimensionless.
     */
    template <class TYPE2, typename std::enable_if<
        !units::traits::is_unit_t<TYPE>::value
        &&
        units::traits::is_unit_t<TYPE2>::value, int>::type = 0
    >
    Vector3<TYPE2> operator%(const Vector3<TYPE2>& vect)
    {
        Vector3<TYPE2> result;
        calculateCrossProduct(*this, vect, &result);
        return result;
    }

    /**
     * \brief Calculates the cross product of two vectors.
     *
     * This is a specialization for the case when the second vector is dimensionless.
     */
    Vector3<TYPE> operator%(const Vector3<double>& vect)
    {
        Vector3<TYPE> result;
        calculateCrossProduct(*this, vect, &result);
        return result;
    }

    /** \brief Unary addition operator. */
    Vector3<TYPE>& operator+=(const Vector3<TYPE>& vect)
    {
        this->add(vect);
        return *this;
    }

    /** \brief Unary subtraction operator. */
    Vector3<TYPE>& operator-=(const Vector3<TYPE>& vect)
    {
        this->subtract(vect);
        return *this;
    }

    /** \brief Unary multiplication operator (by number). */
    Vector3<TYPE>& operator*=(double value)
    {
        *this = (*this) * value;
        return *this;
    }

    /** \brief Unary division operator (by number). */
    Vector3<TYPE>& operator/=(double value)
    {
        *this = (*this) / value;
        return *this;
    }

protected:

    /** \brief Cross product calculation algorithm. */
    template <typename TYPE1, typename TYPE2, typename TYPE3>
    void calculateCrossProduct(const Vector3<TYPE1>& vect1, const Vector3<TYPE2>& vect2, Vector3<TYPE3>* result) const
    {
        result->x() = vect1.y() * vect2.z() - vect1.z() * vect2.y();
        result->y() = vect1.z() * vect2.x() - vect1.x() * vect2.z();
        result->z() = vect1.x() * vect2.y() - vect1.y() * vect2.x();
    }
};

/** \brief Multiplication operator. */
template <typename TYPE1, class TYPE2, typename std::enable_if<
    units::traits::is_unit_t<TYPE1>::value, int>::type = 0
>
auto operator*(TYPE1 value, const Vector3<TYPE2>& vect)
{
    return vect * value;
}

/**
 * \brief Multiplication operator.
 *
 * This is a specialization for the case when the value is a number.
 */
template<typename TYPE>
Vector3<TYPE> operator*(double value, const Vector3<TYPE>& vect)
{
    return vect * value;
}

} // namespace mc

#endif // MCUTILS_MATH_VECTOR3_H_
