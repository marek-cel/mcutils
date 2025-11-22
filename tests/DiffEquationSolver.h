#ifndef TESTS_SDK_DIFFEQUATIONSOLVER_H_
#define TESTS_SDK_DIFFEQUATIONSOLVER_H_

#include <cmath>

#include <mcutils/math/Vector.h>

/**
 * \brief The DiffEquationSolver class
 *
 *
 * Linear homogeneous ordinary differential (Cauchy–Euler) equation is used to
 * test numerical integration classes.
 *
 * Mass-Spring-Damper (MSD) model is used as an example. MSD is described
 * by the following differential equation:
 * m * (d^2 x)/(d t^2)  =  -k * x  -  c * dx/dt
 * Where:
 * m  -  mass
 * k  -  stiffness
 * c  -  damping
 *
 * This equation can be transformed to the following form:
 * m * (d^2 x)/(d t^2)  +  c * dx/dt  +  k * x  =  0
 *
 * Initial values are given as follows:
 * x_0 = x ( t_0 = 0 )
 * x_1 = x'( t_0 = 0 )
 *
 * Assuming that:
 * x = e^( r * t )
 * Then:
 * x'  = r   * e^( r * t )
 * x'' = r^2 * e^( r * t )
 *
 * Subsituting this into equation [1] gives:
 * m * r^2 * e^( r * t )  +  c * r * e^( r * t )  +  k * e^( r * t )  =  0
 *
 * Dividing this equation by e^( r * t ) gives:
 * m * r^2  +  c * r  +  k  =  0
 *
 * Discriminant of this equation is:
 * Delta  =  c^2 - 4 * m * k
 *
 * If Delta > 0 then equation [1] has solution in the following form:
 * x( t )  =  C_1 * e^( r_1 * t )  +  C_2 * e^( r_2 * t )
 * Where:
 * r_1  =  ( -c - sqrt( Delta ) ) / ( 2 * m )
 * r_2  =  ( -c + sqrt( Delta ) ) / ( 2 * m )
 * Then:
 * x'( t )  =  C_1 * r_1 * e^( r_1 * t )  +  C_2 * r_2 * e^( r_2 * t )
 * x'( 0 )  =  C_1 * r_1  +  C_2 * r_2
 *
 * If Delta = 0 then equation [1] has solution in the following form:
 * x( t )  =  ( C_1 * t + C_2 ) * e^( r_1 * t )
 * Where:
 * r_1  =  -c / ( 2 * m )
 * Then:
 * x'( t )  =  C_1  * e^( r_1 * t ) + ( C_1 * t + C_2 ) * r_1 * e^( r_1 * t )
 * x'( 0 )  =  C_1  +  C_2 * r_1
 *
 * If Delta < 0 then equation [1] has solution in the following form:
 * x( t )  =  e^( a * t ) * (  C_1 * cos( b*t )  +  C_2 * sin( b*t )  )
 * Where:
 * a  =  -c / ( 2 * m )
 * b  =  sqrt( 4 * m * k  -  c^2 ) / ( 2 * m )
 * Then:
 * x'( t )  =  a * e^( a * t ) * (  C_1 * cos( b*t )  +  C_2 * sin( b*t )  )
 *          +  e^( a * t ) * ( -C_1 * b * sin( b*t )  + C_2 * b * cos( b*t ) )
 * x'( 0 )  =  C_1 * a  +  C_2 * b
 *
 * ### References:
 * - Krysicki W., Wlodarski L.: Analiza matematyczna w zadaniach, Tom II. PWN, Ed. XXVII, 2018 [in Polish], p.287
 */
template <class INTEGRATOR>
class DiffEquationSolver
{
public:

    static constexpr double ZERO      { 1.0e-9 };
    static constexpr double T_MAX     { 10.0   };
    static constexpr double T_STEP    { 1.0e-2 };
    static constexpr double DELTA_MAX { 1.0e-2 };   ///< max error due to DIFFEQUATIONSOLVER_T_STEP for 1st order method ( 10^-2 )^1 = 10^-2

    /**
     * \brief DiffEquationSolver
     * \param m mass
     * \param k stiffness
     * \param c damping
     */
    DiffEquationSolver(double m, double k, double c, INTEGRATOR* integrator)
    {
        _m = m;
        _k = k;
        _c = c;

        _integrator = integrator;
    }

    /**
     * \brief solve
     * \param x_0 initial value
     * \param x_1 initial value first derivative
     * \return
     */
    bool Solve(double x_0, double x_1)
    {
        // state vector
        // index 0: x
        // index 1: dx/dt
        mc::Vector3d s;

        // initial conditions
        s(0) = x_0;
        s(1) = x_1;

        _integrator->setFun(
            [this](const mc::Vector3d& state)
            {
                return GetStateDeriv(state);
            }
        );

        double t = 0.0;
        double x = 0.0;

        // m * r^2  +  c * r  +  k  =  0
        double delta = CalcDelta(_m, _c, _k);

        //std::cout << "Delta= " << delta << std::endl;

        if ( fabs(delta) < ZERO ) // numerical zero
        {
            // x( t )  =  e^( a * t ) * (  C_1 * cos( b*t )  +  C_2 * sin( b*t )  )

            // a  =  -c / ( 2 * m )
            // b  =  sqrt( 4 * m * k  -  c^2 ) / ( 2 * m )
            double a = -_c / (2.0 * _m);
            double b = sqrt(4.0*_m*_k - _c*_c) / (2.0 * _m);

            // x ( t )  =  e^( a * t ) * (  C_1 * cos( b*t )  +  C_2 * sin( b*t )  )
            // x'( t )  =  a * e^( a * t ) * (  C_1 * cos( b*t )  +  C_2 * sin( b*t )  )
            //          +  e^( a * t ) * ( -C_1 * b * sin( b*t )  + C_2 * b * cos( b*t ) )
            //
            // x ( 0 )  =  C_1
            // x'( 0 )  =  C_1 * a  +  C_2 * b
            //
            // x_0  =  C_1
            // x_1  =  C_1 * a  +  C_2 * b
            //
            // C_1  =  x_0
            // C_2  = ( x_1 - C_1 * a ) / b
            double c_1 = x_0;
            double c_2 = (x_1 - c_1 * a) / b;

            while ( t <= T_MAX )
            {
                x = exp(a * t) * (c_1 * cos(b*t) + c_2 * sin(b*t));

                //std::cout << t << "," << x << "," << s( 0 ) << std::endl;

                if ( fabs(s(0) - x) > DELTA_MAX ) return false;

                t += T_STEP;

                s = _integrator->integrate(T_STEP, s);
            }
        }
        else if ( fabs(delta) >= ZERO ) // numerical zero
        {
            // x( t )  =  C_1 * e^( r_1 * t )  +  C_2 * e^( r_2 * t )

            //  r_1  =  ( -c - sqrt( Delta ) ) / ( 2 * m )
            //  r_2  =  ( -c + sqrt( Delta ) ) / ( 2 * m )
            double sqrt_delta = sqrt(delta);
            double r_1 = (-_c - sqrt_delta) / (2.0 * _m);
            double r_2 = (-_c + sqrt_delta) / (2.0 * _m);

            // x ( t )  =  C_1 * e^( r_1 * t )  +  C_2 * e^( r_2 * t )
            // x'( t )  =  C_1 * r_1 * e^( r_1 * t )  +  C_2 * r_2 * e^( r_2 * t )
            //
            // x ( 0 )  =  C_1  +  C_2
            // x'( 0 )  =  C_1 * r_1  +  C_2 * r_2
            //
            // x_0  =  C_1  +  C_2
            // x_1  =  C_1 * r_1  +  C_2 * r_2
            //
            // C_2  =  ( x_1 - x_0 * r_1 ) / ( r_2 - r_1 )
            // C_1  =  x_0 - C_2
            double c_2 = (x_1 - x_0 * r_1) / (r_2 - r_1);
            double c_1 = x_0 - c_2;

            while ( t <= T_MAX )
            {
                x = c_1 * exp(r_1 * t) + c_2 * exp(r_2 * t);

                //std::cout << t << "," << x << "," << s( 0 ) << std::endl;

                if ( fabs(s(0) - x) > DELTA_MAX ) return false;

                t += T_STEP;

                s = _integrator->integrate(T_STEP, s);
            }
        }
        else // delta == numerical zero
        {
            // x( t )  =  ( C_1 * t + C_2 ) * e^( r_1 * t )

            // r_1  =  -c / ( 2 * m )
            double r_1 = -_c / (2.0 * _m);

            // x ( t )  =  ( C_1 * t + C_2 ) * e^( r_1 * t )
            // x'( t )  =  C_1  * e^( r_1 * t ) + ( C_1 * t + C_2 ) * r_1 * e^( r_1 * t )
            //
            // x ( 0 )  =  C_2
            // x'( 0 )  =  C_1  +  C_2 * r_1
            //
            // x_0  =  C_2
            // x_1  =  C_1  +  C_2 * r_1
            //
            // C_2  = x_0
            // C_1  = x_1  -  C_2 * r_1
            double c_2  = x_0;
            double c_1  = x_1 - c_2 * r_1;

            while ( t <= T_MAX )
            {
                x = (c_1 * t + c_2) * exp(r_1 * t);

                //std::cout << t << "," << x << "," << s( 0 ) << std::endl;

                if ( fabs(s(0) - x) > DELTA_MAX ) return false;

                t += T_STEP;

                s = _integrator->integrate(T_STEP, s);
            }
        }

        return true;
    }

    /**
     * \brief calcDelta
     * \param a
     * \param b
     * \param c
     * \return
     */
    double CalcDelta(double a, double b, double c)
    {
        return b*b - 4.0 * a * c;
    }

    /**
     * \brief computeStateDeriv
     * \param state
     * \param deriv
     */
    mc::Vector3d GetStateDeriv(const mc::Vector3d& state)
    {
        mc::Vector3d deriv;
        deriv(0) = state(1);
        deriv(1) = -_k * state(0) - _c * state(1);
        return deriv;
    }

private:

    INTEGRATOR* _integrator;

    double _m;      ///< [kg]       mass
    double _k;      ///< [N/m]      stiffness
    double _c;      ///< [N/(m/s)]  damping
};

#endif // TESTS_SDK_DIFFEQUATIONSOLVER_H_
