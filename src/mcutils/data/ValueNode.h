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
#ifndef MCUTILS_DATA_VALUENODE_H_
#define MCUTILS_DATA_VALUENODE_H_

#include <memory>
#include <mutex>

#include <mcutils/data/Node.h>

namespace mc {

/**
 * \brief Data node class template.
 * \tparam T data type
 */
template <typename T>
class ValueNode : public Node
{
public:

    /**
     * \param name node name
     */
    explicit ValueNode(const char* name = "")
        : Node(name)
    {}

    /**
     * \return returns node value
     */
    inline T getValue() const
    {
        std::lock_guard<std::mutex> lock(_mutex);
        T result = _value;
        return result;
    }

    /**
     * \brief Sets data node value
     * \param value new node value
     */
    void setValue(const T& value)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _value = value;
    }

protected:

    mutable std::mutex _mutex;      ///< node mutex
    T _value { static_cast<T>(0) }; ///< node value
};

} // namespace mc

#endif // MCUTILS_DATA_VALUENODE_H_
