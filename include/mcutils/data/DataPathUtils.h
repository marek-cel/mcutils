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
#ifndef MCUTILS_DATA_DATAPATHUTILS_H_
#define MCUTILS_DATA_DATAPATHUTILS_H_

#include <string>

#include <mcutils/mcutils_api.h>

namespace mc {

/**
 * \brief Splitted path structure.
 */
struct MCUTILS_API SplittedDataPath
{
    std::string lead;   ///< leading sub-path
    std::string trail;  ///< trailing sub-path
};

/**
 * \brief Splits path string apart.
 * \param path path string to be splitted
 * \return path splitted into lead and rest sub-paths
 */
MCUTILS_API SplittedDataPath splitDataPath(const char* path);

/**
 * \brief Strips path string dots.
 * \param path path to be processed
 * \return stripped path
 */
MCUTILS_API std::string stripDataPathDots(const char* path);

} // namespace mc

#endif // MCUTILS_DATA_DATAPATHUTILS_H_
