/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/
#ifndef MCUTILS_MATH_RUNGEKUTTA4_H_
#define MCUTILS_MATH_RUNGEKUTTA4_H_

#include <functional>

namespace mc {

/**
 * \brief Runge-Kutta 4th order numerical integration class template.
 *
 * ### References:
 * - Press W., et al.: Numerical Recipes: The Art of Scientific Computing, 2007, p.907
 * - Krupowicz A.: Metody numeryczne zagadnien poczatkowych rownan rozniczkowych zwyczajnych, 1986, p.185. [in Polish]
 * - Baron B., Piatek L.: Metody numeryczne w C++ Builder, 2004, p.331. [in Polish]
 * - [Runge–Kutta methods - Wikipedia](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods)
 *
 * \tparam T type of the integrated value
 */
template <typename T>
class RungeKutta4
{
public:

    using DerivFun = std::function<T(const T&)>;

    /**
     * \brief Integrates using Runge-Kutta 4th order integration algorithm.
     * \param dx integration step
     * \param yn current value to be integrated
     * \return integration result
     */
    T integrate(double dx, const T& yn)
    {
        T y0 = yn;

        // k1 - derivatives calculation
        T k1 = _fun(y0);

        // k2 - derivatives calculation
        y0 = yn + k1 * (dx / 2.0);
        T k2 = _fun(y0);

        // k3 - derivatives calculation
        y0 = yn + k2 * (dx / 2.0);
        T k3 = _fun(y0);

        // k4 - derivatives calculation
        y0 = yn + k3 * dx;
        T k4 = _fun(y0);

        // integration
        return yn + (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (dx / 6.0);
    }

    inline DerivFun fun() const { return _fun; }

    void setFun(DerivFun fun) { _fun = fun; }

private:

    DerivFun _fun;  ///< function which calculates vector derivative
};

} // namespace mc

#endif // MCUTILS_MATH_RUNGEKUTTA4_H_
