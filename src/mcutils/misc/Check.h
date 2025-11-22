/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/
#ifndef MCUTILS_MISC_CHECK_H_
#define MCUTILS_MISC_CHECK_H_

#ifdef _MSC_VER
#   include <float.h>
#endif

#include <cmath>
#include <vector>

namespace mc {
namespace misc {

/**
 * \brief Checks if given varaible is Infinite.
 * \param val value to test
 * \return function returns TRUE if tested value is Infinite, TRUE otherwise
 */
template <typename T>
inline bool isInf(const T& val)
{
#   ifdef _MSC_VER
    return !_finite(static_cast<double>(val));
#   else
    return std::isinf(static_cast<double>(val));
#   endif
}

/**
 * \brief Checks if given varaible is NaN.
 * \param val value to test
 * \return function returns TRUE if tested value is NaN, TRUE otherwise
 */
template <typename T>
inline bool isNaN(const T& val)
{
    return val != val;
}

/**
 * \brief Checks if given varaible is Infinite or NaN.
 * \param val value to test
 * \return function returns FALSE if tested value is Infinite or NaN, TRUE otherwise
 */
template <typename T>
inline bool isValid(const T& val)
{
    return !( isNaN(val) || isInf(val) );
}

/**
 * \brief Checks if given array is Infinite or NaN.
 * \param array array to test
 * \param size the size of given array
 * \return function returns FALSE if tested array is Infinite or NaN, TRUE otherwise
 */
template <typename T>
inline bool isValid(const T array[], unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        if (isNaN(array[i]) || isInf(array[i])) return false;
    }

    return true;
}

} // namespace misc
} // namespace mc

#endif // MCUTILS_MISC_CHECK_H_
