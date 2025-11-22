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
#ifndef MCUTILS_DATA_NODE_H_
#define MCUTILS_DATA_NODE_H_

#include <string>

namespace mc {

/**
 * \brief Node base class.
 */
class Node
{
public:

    // LCOV_EXCL_START
    Node() = delete;
    Node(const Node&) = delete;
    Node(Node&&) = delete;
    virtual ~Node() = default;
    Node& operator=(const Node&) = delete;
    Node& operator=(Node&&) = delete;
    // LCOV_EXCL_STOP

    /**
     * \param name node name
     */
    explicit Node(const char* name)
        : _name (name)
    {}

    inline std::string getName() const { return _name; }

protected:

    const std::string _name;    ///< data node name
};

} // namespace mc

#endif // MCUTILS_DATA_NODE_H_
