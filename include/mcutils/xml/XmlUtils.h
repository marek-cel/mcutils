/****************************************************************************//*
 *  Copyright (C) 2025 Marek M. Cel
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
#ifndef MCUTILS_XML_XMLUTILS_H_
#define MCUTILS_XML_XMLUTILS_H_

#include <mcutils/mcutils_api.h>

#include <mcutils/units.h>
#include <mcutils/math/Angles.h>
#include <mcutils/math/Vector.h>
#include <mcutils/xml/XmlNode.h>

namespace mc {
namespace xml {

/**
 * \brief Reads double value from XML node.
 * \param node XML node to be processed
 * \return double value
 */
MCUTILS_API double readDouble(XmlNode node);

/**
 * \brief Reads integer value from XML node.
 * \param node XML node to be processed
 * \return integer value
 */
MCUTILS_API int readInt(XmlNode node);

/**
 * \brief Reads length value from XML node.
 * \param node XML node to be processed
 * \return length value
 */
MCUTILS_API units::length::meter_t readLength(XmlNode node);

/**
 * \brief Reads time value from XML node.
 * \param node XML node to be processed
 * \return time value
 */
MCUTILS_API units::angle::radian_t readAngle(XmlNode node);

/**
 * \brief Reads velocity value from XML node.
 * \param node XML node to be processed
 * \return velocity value
 */
MCUTILS_API units::velocity::meters_per_second_t readVelocity(XmlNode node);

/**
 * \brief Reads mass value from XML node.
 * \param node XML node to be processed
 * \return mass value
 */
MCUTILS_API units::mass::kilogram_t readMass(XmlNode node);

/**
 * \brief Reads angles value from XML node.
 * \param node XML node to be processed
 * \return angles value
 */
MCUTILS_API Angles readAngles(XmlNode node);

// /**
//  * \brief Reads 3D dimensionless vector from XML node.
//  * \param node XML node to be processed
//  * \return 3D dimensionless vector
//  */
// MCUTILS_API Vector3d readVector3d(XmlNode node);

// /**
//  * \brief Reads 3D length vector from XML node.
//  * \param node XML node to be processed
//  * \return 3D length vector
//  */
// MCUTILS_API Vector3_m readVector3_m(XmlNode node);

} // namespace xml
} // namespace mc

#endif // MCUTILS_XML_XMLUTILS_H_
