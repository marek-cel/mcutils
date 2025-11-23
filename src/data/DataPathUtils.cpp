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

#include <mcutils/data/DataPathUtils.h>

namespace mc {

SplittedDataPath splitDataPath(const char* path)
{
    SplittedDataPath result;

    std::string str(path);
    size_t pos = str.find('.');

    if ( pos != std::string::npos )
    {
        result.lead  = str.substr(0 , pos);
        result.trail = str.substr(pos + 1);
    }
    else
    {
        result.lead = path;
        result.trail.clear();
    }

    return result;
}

std::string stripDataPathDots(const char* path)
{
    std::string str(path);

    size_t pos;

    // removing leading dots
    pos = str.find('.');

    if ( pos != std::string::npos )
    {
        while ( pos == 0 )
        {
            str = str.substr(pos + 1);
            pos = str.find('.');
        }
    }

    // removing trailing dots
    pos = str.rfind('.');

    if ( pos != std::string::npos )
    {
        while ( pos == str.length() - 1 )
        {
            str.resize(pos);
            pos = str.rfind('.');
        }
    }

    return str;
}

} // namespace mc
