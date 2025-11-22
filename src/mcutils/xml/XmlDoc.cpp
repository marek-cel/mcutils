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

#include <mcutils/xml/XmlDoc.h>

#include <cstring>
#include <iostream>

namespace mc {

XmlDoc::XmlDoc()
{
    _doc = xmlNewDoc(reinterpret_cast<const xmlChar*>("1.0"));
}

XmlDoc::XmlDoc(const char* path)
{
    openFile(path);
}

XmlDoc::XmlDoc(const std::string& path)
    : XmlDoc(path.c_str())
{}

XmlDoc::XmlDoc(const std::filesystem::path& path)
    : XmlDoc(path.string().c_str())
{}

XmlDoc::~XmlDoc()
{
    closeFile();
}

XmlNode XmlDoc::createRootNode(const char* name)
{
    XmlNode root_node;

    if ( _doc != nullptr && _root == nullptr )
    {
        xmlNodePtr root = xmlNewNode(nullptr, reinterpret_cast<const xmlChar*>(name));
        if (root != nullptr)
        {
            _root = new XmlNode(root, _path);
            xmlDocSetRootElement(_doc, root);
            return XmlNode(*_root);
        }
    }

    return root_node;
}

void XmlDoc::openFile(const char* path)
{
    closeFile();

    if ( std::strlen(path) > 0 )
    {
        _doc = xmlParseFile(path);

        if ( _doc == nullptr )
        {
            xmlFreeDoc(_doc);
            return;
        }

        xmlNodePtr root = xmlDocGetRootElement(_doc);

        if ( root == nullptr )
        {
            xmlFreeDoc(_doc);
            return;
        }

        _path->assign(path);
        _root = new XmlNode(root, _path);
        _open = true;
    }
}

void XmlDoc::closeFile()
{
    _path->clear();
    _open = false;

    if ( _root ) delete _root;
    if ( _doc  ) xmlFreeDoc(_doc);

    _root = nullptr;
    _doc  = nullptr;
}

Result XmlDoc::saveFile(const char* path)
{
    _path->clear();
    _open = false;

    if ( _doc == nullptr )
    {
        return Result::Failure;
    }

    if ( _root == nullptr )
    {
        return Result::Failure;
    }

    if ( xmlSaveFormatFileEnc(path, _doc, "UTF-8", 1) )
    {
        _path->assign(path);
        _open = true;
        return Result::Success;
    }

    return Result::Failure;
}

} // namespace mc
