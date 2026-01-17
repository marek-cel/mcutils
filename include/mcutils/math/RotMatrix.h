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

    /** 
     * \brief Constructor. 
     * \param xx element
     * \param xy element
     * \param xz element
     * \param yx element
     * \param yy element
     * \param yz element
     * \param zx element
     * \param zy element
     * \param zz element
     */
    RotMatrix(double xx = 1.0, double xy = 0.0, double xz = 0.0,
              double yx = 0.0, double yy = 1.0, double yz = 0.0,
              double zx = 0.0, double zy = 0.0, double zz = 1.0);

    /** 
     * \brief Creates passive (alias) rotation matrix. 
     * \param angl Bryant angles of rotation
     */
    explicit RotMatrix(const Angles& angl);

    /** 
     * \brief Creates passive (alias) rotation matrix. 
     * \param quat Quaternion of rotation
     */
    explicit RotMatrix(const Quaternion& quat);

    /** 
     * \brief Returns Bryant angles of rotation matrix.
     * \return angles of rotation
     */
    Angles getAngles() const;

    /** 
     * \brief Returns quaternion of rotation matrix.
     * \return quaternion of rotation
     */
    Quaternion getQuaternion() const;

    /** 
     * \brief Returns transposed matrix.
     * \return transposed matrix
     */
    RotMatrix getTransposed() const;

    /** 
     * \brief Addition operator. 
     * \param mat matrix to be added
     * \return resulting matrix
     */
    RotMatrix operator+(const RotMatrix& mat) const;

    /** 
     * \brief Negation operator.
     * \return negated matrix
     */
    RotMatrix operator-() const;

    /** 
     * \brief Subtraction operator. 
     * \param mat matrix to be subtracted
     * \return resulting matrix
     */
    RotMatrix operator-(const RotMatrix& mat) const;

    /** 
     * \brief Multiplication operator (by number). 
     * \param val number to multiply by
     * \return resulting matrix
     */
    RotMatrix operator*(double val) const;

    /** 
     * \brief Multiplication operator (by matrix). 
     * \param mat matrix to multiply by
     * \return resulting matrix
     */
    RotMatrix operator*(const RotMatrix& mat) const;

    /** 
     * \brief Multiplication operator (by vector). 
     * \tparam TYPE vector element type
     * \param vect vector to multiply by
     * \return resulting vector
     */
    template <typename TYPE>
    Vector3<TYPE> operator*(const Vector3<TYPE>& vect) const
    {
        Vector3<TYPE> result;
        multiplyMatrixByVector(*this, vect, &result);
        return result;
    }

    /** 
     * \brief Division operator. 
     * \param value number to divide by
     * \return resulting matrix
     */
    RotMatrix operator/(double val) const;

    /** 
     * \brief Unary addition operator.
     * \param mat matrix to be added
     * \return reference to this matrix
     */
    RotMatrix& operator+=(const RotMatrix& mat);

    /** 
     * \brief Unary subtraction operator.
     * \param mat matrix to be subtracted
     * \return reference to this matrix
     */
    RotMatrix& operator-=(const RotMatrix& mat);

    /** 
     * \brief Unary multiplication operator.
     * \param val number to multiply by
     * \return reference to this matrix
     */
    RotMatrix& operator*=(double val);

    /** 
     * \brief Unary division operator.
     * \param val number to divide by
     * \return reference to this matrix
     */
    RotMatrix& operator/=(double val);
};

/** 
 * \brief Multiplication operator.
 * \param val number to multiply by
 * \param mat matrix to multiply
 * \return resulting matrix
 */
inline RotMatrix operator*(double val, const RotMatrix& mat)
{
    return mat * val;
}

} // namespace mc

#endif // MCUTILS_MATH_RMATRIX_H_
