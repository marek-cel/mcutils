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
#ifndef MCUTILS_DATA_DATAREF_H_
#define MCUTILS_DATA_DATAREF_H_

#include <limits>
#include <memory>

#include <mcutils/Result.h>

#include <mcutils/data/ConstDataRef.h>

namespace mc {

/**
 * \brief Data reference class template.
 * \tparam T data type
 */
template <typename T>
class DataRef : public ConstDataRef<T>
{
public:

    /**
     * \param value_node value node pointer
     */
    explicit DataRef(std::weak_ptr<ValueNode<T>> value_node = std::weak_ptr<ValueNode<T>>())
        : ConstDataRef<T>(value_node )
    {}

    /**
     * \brief Sets new data value.
     * \param value new value
     * \return Success on success or Failure on failure
     */
    inline Result setValue(T value)
    {
        if ( ConstDataRef<T>::isValid() )
        {
            ConstDataRef<T>::_value_node.lock()->setValue(value);
            return Result::Success;
        }

        return Result::Failure;
    }

    /** \brief Assignment operator. */
    const T operator=(T value)
    {
        setValue(value);
        return ConstDataRef<T>::getValue();
    }
};

} // namespace mc

#endif // MCUTILS_DATA_DATAREF_H_
