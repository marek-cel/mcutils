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
#ifndef MCUTILS_XML_XMLNODE_H_
#define MCUTILS_XML_XMLNODE_H_

#include <filesystem>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include <libxml/tree.h>

#include <mcutils/mcutils_api.h>
#include <mcutils/Result.h>

namespace mc {

/**
 * \brief XML node class.
 */
class MCUTILS_API XmlNode
{
public:

    typedef std::map<std::string, std::string> Attributes;

    // LCOV_EXCL_START
    XmlNode() = default;
    XmlNode(const XmlNode& node) = default;
    XmlNode(XmlNode&& node) = default;
    ~XmlNode() = default;
    XmlNode& operator=(const XmlNode& node) = default;
    XmlNode& operator=(XmlNode&& node) = default;
    // LCOV_EXCL_STOP

    /**
     * \param node XML node pointer
     * \param path XML file path pointer
     */
    XmlNode(xmlNodePtr node, std::weak_ptr<std::filesystem::path> path);

    XmlNode addChildElement(const char* name);
    XmlNode addChildElement(const std::string& name)
    {
        return addChildElement(name.c_str());
    }

    /**
     * \brief Adds text node to the element.
     * Adds text node to the element. The text node is added as a child of the
     * element.
     * \param text text
     * \return XML text node
     */
    XmlNode addText(const char* text);
    XmlNode addText(const std::string& text)
    {
        return addText(text.c_str());
    }

    /**
     * \brief Adds attribute to the element.
     * Adds attribute to the element. The attribute is added as a child of the
     * element.
     * \param name name of attribute
     * \param val value of attribute
     * \return result of the operation
     */
    Result addAttribute(const char* name, const char* val);
    Result addAttribute(const std::string& name, const std::string& val)
    {
        return addAttribute(name.c_str(), val.c_str());
    }

    /**
     * \brief Returns the value of the attribute.
     * Returns the value of the attribute or an empty string if the attribute
     * has not been specified.
     * \param name name of attribute
     * \return value of the attribute or an empty string if the attribute has not been specified
     */
    std::string getAttribute(const char* name) const;
    std::string getAttribute(const std::string& name) const
    {
        return getAttribute(name.c_str());
    }

    Result setAttribute(const char* name, const char* val);
    Result setAttribute(const std::string& name, const std::string& val)
    {
        return setAttribute(name.c_str(), val.c_str());
    }

    /**
     * \brief Returns element attributes list.
     * Returns element attributes list or empty list if the node is not
     * an element or element does not has any attributes.
     */
    Attributes getAttributes() const;

    /**
     * Returns first child node.
     */
    XmlNode getFirstChild() const;

    /**
     * Returns first child element node of the given name.
     * \param name element name
     * \return node's first child
     */
    XmlNode getFirstChildElement(const char* name = "") const;
    XmlNode getFirstChildElement(const std::string& name) const
    {
        return getFirstChildElement(name.c_str());
    }

    /**
     * \return file path
     */
    std::filesystem::path getPath() const;

    /**
     * \return node file path and line number
     */
    std::string getPathAndLine() const;

    /**
     * \return node line number
     */
    inline int getLine() const
    {
        if ( isValid() )
        {
            return static_cast<int>(_node->line);
        }

        return std::numeric_limits<int>::quiet_NaN();
    }

    /**
     * \return node name
     */
    std::string getName() const
    {
        if ( isValid() )
        {
            return std::string(reinterpret_cast<const char*>(_node->name));
        }

        return std::string();
    }

    /**
     * \return node's next sibling
     */
    XmlNode getNextSibling() const;

    /**
     * \param name element name
     * \return node's next sibling of a given name
     */
    XmlNode getNextSiblingElement(const char* name = "") const;

    /**
     * \return text if node is a text node, otherwise an empty string
     */
    std::string getText() const;

    /**
     * \param name attribute name
     * \param value attribute value
     * \return result of the operation
     */
    Result setText(const char* text);
    Result setText(const std::string& text)
    {
        return setText(text.c_str());
    }

    /**
     * \param name attribute name
     * \return true if an node has attributes of a given name, false otherwise
     */
    bool hasAttribute(const char* name) const;
    bool hasAttribute(const std::string& name) const
    {
        return hasAttribute(name.c_str());
    }

    /**
     * \return true if an node has attributes, false otherwise
     */
    inline bool hasAttributes() const
    {
        if ( isValid() )
        {
            return ( _node->properties != nullptr );
        }

        return false;
    }

    /**
     * \return true if an node has children, false otherwise
     */
    inline bool hasChildren() const
    {
        if ( isValid() )
        {
            return ( _node->children != nullptr );
        }

        return false;
    }

    /**
     * \return true if an node is an attribute, false otherwise
     */
    inline bool isAttribute() const
    {
        if ( isValid() )
        {
            return ( _node->type == XML_ATTRIBUTE_NODE );
        }

        return false;
    }

    /**
     * \return true if an node is a comment, false otherwise
     */
    inline bool isComment() const
    {
        if ( isValid() )
        {
            return ( _node->type == XML_COMMENT_NODE );
        }

        return false;
    }

    /**
     * \return true if an node is an element, false otherwise
     */
    inline bool isElement() const
    {
        if ( isValid() )
        {
            return ( _node->type == XML_ELEMENT_NODE );
        }

        return false;
    }

    /**
     * \return true if an node is a text, false otherwise
     */
    inline bool isText() const
    {
        if ( isValid() )
        {
            return _node->type == XML_TEXT_NODE;
        }

        return false;
    }

    /**
     * \return true if an node is valid, false otherwise
     */
    inline bool isValid() const
    {
        return _node ? true : false;
    }

private:

    std::weak_ptr<std::filesystem::path> _path; ///< XML file path pointer
    xmlNodePtr _node = nullptr;                 ///< XML node pointer
};

} // namespace mc

#endif // MCUTILS_XML_XMLNODE_H_
