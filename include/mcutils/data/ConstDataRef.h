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
#ifndef MCUTILS_DATA_CONSTDATAREF_H_
#define MCUTILS_DATA_CONSTDATAREF_H_

#include <limits>
#include <memory>

#include <mcutils/Result.h>

#include <mcutils/data/ValueNode.h>

namespace mc {

/**
 * \brief Constant data reference class template.
 * \tparam T data type
 */
template <typename T>
class ConstDataRef
{
public:

    /**
     * \param value_node value node pointer
     */
    explicit ConstDataRef(std::weak_ptr<ValueNode<T>> value_node = std::weak_ptr<ValueNode<T>>())
        : _value_node(value_node )
    {}

    /**
     * \return returns data value on success or 0 on failure
     */
    inline T getValue(T def = static_cast<T>(0)) const
    {
        if ( isValid() )
        {
            return _value_node.lock()->getValue();
        }

        return def;
    }

    /**
     * \return true if reference is valid, false otherwise
     */
    inline bool isValid() const
    {
        return !_value_node.expired();
    }

    /** Access operator. */
    const T operator()()
    {
        return getValue();
    }

protected:

    std::weak_ptr<ValueNode<T>> _value_node;    ///< value node pointer
};

} // namespace mc

#endif // MCUTILS_DATA_CONSTDATAREF_H_
