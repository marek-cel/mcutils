/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/
#ifndef MCUTILS_MCUTILS_API_H_
#define MCUTILS_MCUTILS_API_H_

#if defined(_MSC_VER) && !defined(MCUTILS_STATIC_LIB)
#   if defined(MCUTILS_DLL_EXPORTS)
#       define MCUTILS_DLL_SPEC __declspec(dllexport)
#   else
#       define MCUTILS_DLL_SPEC __declspec(dllimport)
#   endif
#else
#   define MCUTILS_DLL_SPEC
#endif

#if defined(__cplusplus)
#   define MCUTILS_API MCUTILS_DLL_SPEC
#endif

#if !defined(MCUTILS_API)
#   define MCUTILS_API
#endif

#endif // MCUTILS_MCUTILS_API_H_
