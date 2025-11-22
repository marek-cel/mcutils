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
#ifndef MCUTILS_XML_XMLDOC_H_
#define MCUTILS_XML_XMLDOC_H_

#include <filesystem>
#include <string>

#include <libxml/tree.h>

#include <mcutils/mcutils_api.h>
#include <mcutils/Result.h>
#include <mcutils/xml/XmlNode.h>

namespace mc {

/**
 * \brief XML Document class.
 */
class MCUTILS_API XmlDoc
{
public:

    /**
     * \brief Creates an empty XML document.
     */
    XmlDoc();

    /**
     * \brief Opens XML file.
     * \param path XML file path
     */
    XmlDoc(const char* path);

    /**
     * \brief Opens XML file.
     * \param file XML file path
     */
    XmlDoc(const std::string& path);

    /**
     * \brief Opens XML file.
     * \param file XML file path
     */
    XmlDoc(const std::filesystem::path& path);

    /**
     * \brief Destructor.
     */
    ~XmlDoc();

    /**
     * \brief Creates XML document root node.
     * \param name XML document root node name
     * \return XML document root node
     */
    XmlNode createRootNode(const char* name);
    inline XmlNode createRootNode(const std::string& name)
    {
        return createRootNode(name.c_str());
    }

    /**
     * \return file path
     */
    inline std::filesystem::path getPath() const
    {
        return *_path;
    }

    /**
     * Gets XML document root node.
     * \return XML document root node
     */
    inline XmlNode getRootNode()
    {
        return XmlNode(*_root);
    }

    /**
     * Checks if XML document is open.
     * \return returns true if XML document is open
     */
    inline bool isOpen() const
    {
        return _open;
    }

    /**
     * Open file for reading.
     * \param path XML file path
     */
    void openFile(const char* path);
    inline void openFile(const std::string& path)
    {
        openFile(path.c_str());
    }
    inline void openFile(const std::filesystem::path& path)
    {
        openFile(path.string());
    }

    /** Closes file. */
    void closeFile();

    /**
     * \brief Saves XML document to file.
     * \param path XML file path
     * \return result of the operation
     */
    Result saveFile(const char* path);
    inline Result saveFile(const std::string& path)
    {
        return saveFile(path.c_str());
    }
    inline Result saveFile(const std::filesystem::path& path)
    {
        return saveFile(path.string());
    }

private:

    std::shared_ptr<std::filesystem::path> _path = std::make_shared<std::filesystem::path>(); ///< XML file path

    xmlDocPtr _doc = nullptr;   ///< XML document pointer
    bool _open = false;         ///< specifies if document is open
    XmlNode *_root = nullptr;   ///< XML document root node
};

} // namespace mc

#endif // MCUTILS_XML_XMLDOC_H_
