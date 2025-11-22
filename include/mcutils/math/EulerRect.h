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
#ifndef MCUTILS_MATH_EULERRECT_H_
#define MCUTILS_MATH_EULERRECT_H_

#include <functional>

namespace mc {

/**
 * \brief Euler's rectangular numerical integration class template.
 *
 * ### References:
 * - Press W., et al.: Numerical Recipes: The Art of Scientific Computing, 2007, p.907
 * - Allerton D.: Principles of Flight Simulation, 2009, p.58
 * - DeLoura M.: Game Programming Gems Vol. 1, 2000, p.176
 * - Krupowicz A.: Metody numeryczne zagadnien poczatkowych rownan rozniczkowych zwyczajnych, 1986, p.29. [in Polish]
 * - Matulewski J., et. al.: Grafika fizyka metody numeryczne, 2010, p.309. [in Polish]
 * - [Euler method - Wikipedia](https://en.wikipedia.org/wiki/Euler_method)
 *
 * \tparam T type of the integrated value
 */
template <typename T>
class EulerRect
{
public:

    using DerivFun = std::function<T(const T&)>;

    /**
     * \brief Integrates using Euler's rectangular integration algorithm.
     * \param dx integration step
     * \param yn current value to be integrated
     * \return integration result
     */
    T integrate(double dx, const T& yn)
    {
        // integration
        return yn + _fun(yn) * dx;
    }

    inline DerivFun fun() const { return _fun; }

    void setFun(DerivFun fun) { _fun = fun; }

private:

    DerivFun _fun;  ///< function which calculates vector derivative
};

} // namespace mc

#endif // MCUTILS_MATH_EULERRECT_H_
