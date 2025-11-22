/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/
#ifndef MCUTILS_MATH_GAUSSJORDAN_H_
#define MCUTILS_MATH_GAUSSJORDAN_H_

#include <mcutils/Result.h>

#include <mcutils/math/Matrix.h>
#include <mcutils/math/Vector.h>

namespace mc {
namespace math {

/**
 * \brief Solves system of linear equations using Gauss-Jordan method.
 *
 * ### References:
 * - Press W., et al.: Numerical Recipes: The Art of Scientific Computing, 2007, p.41
 * - Baron B., Piatek L.: Metody numeryczne w C++ Builder, 2004, p.34. [in Polish]
 * - [Gaussian elimination - Wikipedia](https://en.wikipedia.org/wiki/Gaussian_elimination)
 *
 * \tparam TYPE type of the matrix and vector
 * \tparam SIZE size of the matrix and vector
 *
 * \param mtr left hand side matrix
 * \param rhs right hand size vector
 * \param x result vector
 * \param eps minimum value treated as not-zero
 *
 * \return mc::Result::Success on success and mc::Result::Failure on failure
 */
template <typename TYPE, unsigned int SIZE>
Result solveGaussJordan(const MatrixNxN<TYPE, SIZE>& mtr, const VectorN<TYPE, SIZE>& rhs,
                        VectorN<TYPE, SIZE>* x, double eps = 1.0e-9)
{
    MatrixNxN<TYPE, SIZE> mtr_temp = mtr;
    VectorN<TYPE, SIZE>   rhs_temp = rhs;

    for (unsigned int r = 0; r < SIZE; ++r)
    {
        // run along diagonal, swapping rows to move zeros (outside the diagonal) downwards
        if (fabs(mtr_temp(r,r)) < fabs(eps))
        {
            if ( r < SIZE - 1 )
            {
                mtr_temp.swapRows(r, r+1);
                rhs_temp.swapRows(r, r+1);
            }
            else
            {
                return Result::Failure;
            }
        }

        // value on diagonal A(r,r)
        double a_rr = mtr_temp(r,r);
        double a_rr_inv = 1.0 / a_rr;

        // deviding current row by value on diagonal
        for (unsigned int c = 0; c < SIZE; ++c)
        {
            mtr_temp(r,c) *= a_rr_inv;
        }

        rhs_temp(r) *= a_rr_inv;

        // substracting current row from others rows
        // for every row current row is multiplied by A(i,r)
        // where r stands for row that is substracted from other rows
        // and i stands for row that is substracting from
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            if (i != r)
            {
                double a_ir = mtr_temp(i,r);
                for (unsigned int c = 0; c < SIZE; ++c)
                {
                    mtr_temp(i,c) -= a_ir * mtr_temp(r,c);
                }
                rhs_temp(i) -= a_ir * rhs_temp(r);
            }
        }
    }

    // rewritting results
    *x = rhs_temp;

    return Result::Success;
}

} // namespace math
} // namespace mc

#endif // MCUTILS_MATH_GAUSSJORDAN_H_
