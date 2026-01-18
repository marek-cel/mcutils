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

#include <mcutils/xml/XmlUtils.h>

#include <limits>

#include <mcutils/misc/Check.h>
#include <mcutils/physics/UnitsUtils.h>

using namespace units::literals;

namespace mc {

double readDouble(XmlNode node)
{
    double result = std::numeric_limits<double>::quiet_NaN();
    if ( node.isValid() )
    {
        double temp = misc::toDouble(node.getFirstChild().getText());
        if ( check::isValid(temp) )
            result = temp;
    }
    return result;
}

int readInt(XmlNode node)
{
    int result = std::numeric_limits<int>::quiet_NaN();
    if ( node.isValid() )
    {
        int temp = misc::toInt(node.getFirstChild().getText());
        if ( check::isValid(temp) )
            result = temp;
    }
    return result;
}

units::length::meter_t readLength(XmlNode node)
{
    units::length::meter_t result(std::numeric_limits<double>::quiet_NaN());
    if ( node.isValid() )
    {
        double temp = misc::toDouble(node.getFirstChild().getText());
        if ( check::isValid(temp) )
        {
            if ( node.hasAttribute("unit") )
            {
                std::string unit_name = node.getAttribute("unit");
                result = convertToMeters(unit_name.c_str(), temp);
            }
            else
            {
                result = temp * 1_m;
            }
        }
    }
    return result;
}

units::angle::radian_t readAngle(XmlNode node)
{
    units::angle::radian_t result(std::numeric_limits<double>::quiet_NaN());
    if ( node.isValid() )
    {
        double temp = misc::toDouble(node.getFirstChild().getText());
        if ( check::isValid(temp) )
        {
            if ( node.hasAttribute("unit") )
            {
                std::string unit_name = node.getAttribute("unit");
                result = convertToRadians(unit_name.c_str(), temp);
            }
            else
            {
                result = temp * 1_rad;
            }
        }
    }
    return result;
}

units::velocity::meters_per_second_t readVelocity(XmlNode node)
{
    units::velocity::meters_per_second_t result(std::numeric_limits<double>::quiet_NaN());
    if ( node.isValid() )
    {
        double temp = misc::toDouble(node.getFirstChild().getText());
        if ( check::isValid(temp) )
        {
            if ( node.hasAttribute("unit") )
            {
                std::string unit_name = node.getAttribute("unit");
                result = convertToMPS(unit_name.c_str(), temp);
            }
            else
            {
                result = temp * 1_mps;
            }
        }
    }
    return result;
}

units::mass::kilogram_t readMass(XmlNode node)
{
    units::mass::kilogram_t result(std::numeric_limits<double>::quiet_NaN());
    if ( node.isValid() )
    {
        double temp = misc::toDouble(node.getFirstChild().getText());
        if ( check::isValid(temp) )
        {
            if ( node.hasAttribute("unit") )
            {
                std::string unit_name = node.getAttribute("unit");
                result = convertToKilograms(unit_name.c_str(), temp);
            }
            else
            {
                result = temp * 1_kg;
            }
        }
    }
    return result;
}

Angles readAngles(XmlNode node)
{
    Angles result;

    result.phi() = 1_rad * std::numeric_limits<double>::quiet_NaN();
    result.tht() = 1_rad * std::numeric_limits<double>::quiet_NaN();
    result.psi() = 1_rad * std::numeric_limits<double>::quiet_NaN();

    if ( node.isValid() )
    {
        XmlNode node_phi = node.getFirstChildElement("phi");
        XmlNode node_tht = node.getFirstChildElement("tht");
        XmlNode node_psi = node.getFirstChildElement("psi");

        if ( node_phi.isValid() && node_tht.isValid() && node_psi.isValid() )
        {
            Angles temp;

            if ( node.hasAttribute("unit") )
            {
                std::string unit_name = node.getAttribute("unit");
                temp.phi() = convertToRadians(unit_name.c_str(), readDouble(node_phi));
                temp.tht() = convertToRadians(unit_name.c_str(), readDouble(node_tht));
                temp.psi() = convertToRadians(unit_name.c_str(), readDouble(node_psi));
            }
            else
            {
                temp.phi() = 1_rad * readDouble(node_phi);
                temp.tht() = 1_rad * readDouble(node_tht);
                temp.psi() = 1_rad * readDouble(node_psi);
            }

            if ( temp.isValid() )
                result = temp;
        }
    }

    return result;
}

Vector3d readVector3d(XmlNode node)
{
    Vector3d result;

    result.x() = std::numeric_limits<double>::quiet_NaN();
    result.y() = std::numeric_limits<double>::quiet_NaN();
    result.z() = std::numeric_limits<double>::quiet_NaN();

    if ( node.isValid() )
    {
        XmlNode node_x = node.getFirstChildElement("x");
        XmlNode node_y = node.getFirstChildElement("y");
        XmlNode node_z = node.getFirstChildElement("z");

        if ( node_x.isValid() && node_y.isValid() && node_z.isValid() )
        {
            Vector3d temp;

            temp.x() = readDouble(node_x);
            temp.y() = readDouble(node_y);
            temp.z() = readDouble(node_z);

            if ( temp.isValid() )
                result = temp;
        }
    }

    return result;
}

Vector3_m readVector3_m(XmlNode node)
{
    Vector3_m result;

    result.x() = 1_m * std::numeric_limits<double>::quiet_NaN();
    result.y() = 1_m * std::numeric_limits<double>::quiet_NaN();
    result.z() = 1_m * std::numeric_limits<double>::quiet_NaN();

    if ( node.isValid() )
    {
        XmlNode node_x = node.getFirstChildElement("x");
        XmlNode node_y = node.getFirstChildElement("y");
        XmlNode node_z = node.getFirstChildElement("z");

        if ( node_x.isValid() && node_y.isValid() && node_z.isValid() )
        {
            Vector3_m temp;

            if ( node.hasAttribute("unit") )
            {
                std::string unit_name = node.getAttribute("unit");
                temp.x() = convertToMeters(unit_name.c_str(), readDouble(node_x));
                temp.y() = convertToMeters(unit_name.c_str(), readDouble(node_y));
                temp.z() = convertToMeters(unit_name.c_str(), readDouble(node_z));
            }
            else
            {
                temp.x() = 1_m * readDouble(node_x);
                temp.y() = 1_m * readDouble(node_y);
                temp.z() = 1_m * readDouble(node_z);
            }

            if ( temp.isValid() )
                result = temp;
        }
    }

    return result;
}

} // namespace mc
