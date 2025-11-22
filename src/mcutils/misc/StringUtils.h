/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/
#ifndef MCUTILS_MISC_STRINGUTILS_H_
#define MCUTILS_MISC_STRINGUTILS_H_

#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include <mcutils/mcutils_api.h>

namespace mc {
namespace misc {

/**
 * \brief Compares strings.
 * \param str_1 1st string to compare
 * \param str_2 2nd string to compare
 * \param case_sensitive specifies if comparison is case sensitive
 * \return integer result of the comparison (returns 0 if strings are equal)
 */
MCUTILS_API int compareStrings(const std::string& str_1, const std::string& str_2,
                               bool case_sensitive = false);

/**
 * \brief Returns string first line;
 * \param str string to be processed
 * \return string first line
 */
MCUTILS_API std::string getFirstLine(const std::string& str);

/**
 * \brief Splits string with the given delimeter.
 * \param str string to be splitted
 * \param sep string separator
 * \return vector of strings
 */
MCUTILS_API std::vector<std::string> splitString(const std::string& str, const std::string& sep);

/**
 * \brief Returns string with leading white spaces removed.
 * \param str string to be processed
 * \return string with leading white spaces removed
 */
MCUTILS_API std::string stripLeadingSpaces(const std::string& str);

/**
 * \brief Returns string with trailing white spaces removed.
 * \param str string to be processed
 * \return string with trailing white spaces removed
 */
MCUTILS_API std::string stripTrailingSpaces(const std::string& str);

/**
 * \brief Returns string with both leading and trailing white spaces removed.
 * \param str string to be processed
 * \return string with leading and trailing white spaces removed
 */
MCUTILS_API std::string stripSpaces(const std::string& str);

/**
 * \brief Converts string into variable.
 * \param str string to be processed
 * \param def default value
 * \return result value
 */
MCUTILS_API bool toBool(const std::string& str, bool def = std::numeric_limits<bool>::quiet_NaN());

/**
 * \brief Converts string into variable.
 * \param str string to be processed
 * \param def default value
 * \return result value
 */
MCUTILS_API int toInt(const std::string& str, int def = std::numeric_limits<int>::quiet_NaN());

/**
 * \brief Converts string into variable.
 * \param str string to be processed
 * \param def default value
 * \return result value
 */
MCUTILS_API double toDouble(const std::string& str, double def = std::numeric_limits<double>::quiet_NaN());

/**
 * \brief Converts variable into string.
 * \param val value to be processed
 * \return result string
 */
template <typename T>
inline std::string toString(T val)
{
    std::stringstream ss;
    ss.imbue(std::locale("C"));
    ss << val;
    return ss.str();
}

/**
 * \brief Converts string to lower case.
 * \param str string to be processed
 * \return result string
 */
MCUTILS_API std::string toLower(const std::string& str);

/**
 * \brief Converts string to upper case.
 * \param str string to be processed
 * \return result string
 */
MCUTILS_API std::string toUpper(const std::string& str);

} // namespace misc
} // namespace mc

#endif // MCUTILS_MISC_STRINGUTILS_H_
