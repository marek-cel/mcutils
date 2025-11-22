/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/
#ifndef MCUTILS_MATH_RMATRIX_H_
#define MCUTILS_MATH_RMATRIX_H_

#include <mcutils/mcutils_api.h>

#include <mcutils/math/Angles.h>
#include <mcutils/math/Matrix.h>
#include <mcutils/math/Quaternion.h>

namespace mc {

/**
 * \brief Direction cosine (rotation) matrix class.
 *
 * This class represents a 3x3 rotation matrix, which is used to describe the
 * orientation of a rigid body in three-dimensional space.
 *
 * Please notice that all rotations are considered to be passive (alias) rotations.
 *
 * ### References:
 * - Allerton D.: Principles of Flight Simulation, 2009, p.120
 * - Zipfel P.: Modeling and Simulation of Aerospace Vehicle Dynamics, 2007, p.373
 * - Bociek S., Gruszecki J.: Uklady sterowania automatycznego samolotem, 1999, p.23. [in Polish]
 * - Sibilski K.: Modelowanie i symulacja dynamiki ruchu obiektow latajacych, 2004, p.34. [in Polish]
 * - Matulewski J., et. al.: Grafika fizyka metody numeryczne, 2010, p.529. [in Polish]
 * - [Rotation matrix - Wikipedia](https://en.wikipedia.org/wiki/Rotation_matrix)
 * - [Euler angles - Wikipedia](https://en.wikipedia.org/wiki/Euler_angles)
 * - [Active and passive transformation - Wikipedia](https://en.wikipedia.org/wiki/Active_and_passive_transformation)
 */
class MCUTILS_API RotMatrix : public Matrix3x3<double>
{
public:

    /** \brief Creates identity matrix. */
    static RotMatrix getIdentityMatrix();

    /** \brief Constructor. */
    RotMatrix(double xx = 1.0, double xy = 0.0, double xz = 0.0,
              double yx = 0.0, double yy = 1.0, double yz = 0.0,
              double zx = 0.0, double zy = 0.0, double zz = 1.0);

    /** \brief Creates passive (alias) rotation matrix. */
    explicit RotMatrix(const Angles& angl);

    /** \brief Creates passive (alias) rotation matrix. */
    explicit RotMatrix(const Quaternion& qtrn);

    /** \brief Returns Bryant angles of rotation matrix. */
    Angles getAngles() const;

    /** \brief Returns quaternion of rotation matrix. */
    Quaternion getQuaternion() const;

    /** \brief Returns transposed matrix. */
    RotMatrix getTransposed() const;

    /** \brief Addition operator. */
    RotMatrix operator+(const RotMatrix& matrix) const;

    /** \brief Negation operator. */
    RotMatrix operator-() const;

    /** \brief Subtraction operator. */
    RotMatrix operator-(const RotMatrix& matrix) const;

    /** \brief Multiplication operator (by number). */
    RotMatrix operator*(double value) const;

    /** \brief Multiplication operator (by matrix). */
    RotMatrix operator*(const RotMatrix& matrix) const;

    /** \brief Multiplication operator (by vector). */
    template <typename TYPE>
    Vector3<TYPE> operator*(const Vector3<TYPE>& vect) const
    {
        Vector3<TYPE> result;
        this->multiplyMatrixByVector(*this, vect, &result);
        return result;
    }

    /** \brief Division operator (by number). */
    RotMatrix operator/(double value) const;

    /** \brief Unary addition operator. */
    RotMatrix& operator+=(const RotMatrix& matrix);

    /** \brief Unary subtraction operator. */
    RotMatrix& operator-=(const RotMatrix& matrix);

    /** \brief Unary multiplication operator (by number). */
    RotMatrix& operator*=(double value);

    /** \brief Unary division operator (by number). */
    RotMatrix& operator/=(double value);
};

/** \brief Multiplication operator (by number). */
inline RotMatrix operator*(double value, const RotMatrix& matrix)
{
    return matrix * value;
}

} // namespace mc

#endif // MCUTILS_MATH_RMATRIX_H_
