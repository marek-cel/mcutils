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
#ifndef MCUTILS_DATA_DATATREE_H_
#define MCUTILS_DATA_DATATREE_H_

#include <memory>
#include <string>

#include <mcutils/Result.h>

#include <mcutils/mcutils_api.h>

#include <mcutils/data/DataRef.h>
#include <mcutils/data/GroupNode.h>

namespace mc {

/**
 * \brief Data tree class.
 */
class MCUTILS_API DataTree
{
public:

    /**
     * \param root data tree root group node
     */
    explicit DataTree(std::shared_ptr<GroupNode> root = std::make_shared<GroupNode>());

    /**
     * \brief Adds new leaf entry.
     * \tparam TYPE data type (eg.: bool, int double)
     * \param path path of entry to be created
     * \return valid data reference to created entry on success or invalid on failure
     */
    template <typename TYPE>
    DataRef<TYPE> addEntry(const char* path)
    {
        if ( Result::Success == _root->addNode<ValueNode<TYPE>>(path) )
        {
            std::weak_ptr<Node> node_wp = _root->getNode(path);
            if ( !node_wp.expired() )
            {
                std::shared_ptr<Node> node_sp = node_wp.lock();
                std::shared_ptr<ValueNode<TYPE>> vnode_sp
                    = std::dynamic_pointer_cast<ValueNode<TYPE>,Node>(node_sp);
                if ( vnode_sp )
                {
                    return DataRef<TYPE>(vnode_sp);
                }
            }
        }

        return DataRef<TYPE>();
    }

    /**
     * \brief Adds new leaf entry.
     * \tparam TYPE data type (eg.: bool, int double)
     * \param path path of entry to be created
     * \return valid data reference to created entry on success or invalid on failure
     */
    template <typename TYPE>
    inline DataRef<TYPE> addEntry(const std::string& path)
    {
        return addEntry<TYPE>(path.c_str());
    }

    /**
     * \brief Gets data reference to leaf entry.
     * \tparam TYPE data type (eg.: bool, int double)
     * \param path path of entry to be retrieved
     * \return valid data reference if entry exists or invalid if doesn't
     */
    template <typename TYPE>
    ConstDataRef<TYPE> getDataRef(const char* path)
    {
        std::weak_ptr<Node> node_wp = _root->getNode(path);

        if ( !node_wp.expired() )
        {
            std::shared_ptr<Node> node_sp = node_wp.lock();
            std::shared_ptr<ValueNode<TYPE>> vnode_sp =
                    std::dynamic_pointer_cast<ValueNode<TYPE>,Node>(node_sp);
            return ConstDataRef<TYPE>(vnode_sp);
        }

        return ConstDataRef<TYPE>();
    }

    /**
     * \brief Gets data reference to leaf entry.
     * \tparam TYPE data type (eg.: bool, int double)
     * \param path path of entry to be retrieved
     * \return valid data reference if entry exists or invalid if doesn't
     */
    template <typename TYPE>
    inline ConstDataRef<TYPE> getDataRef(const std::string& path)
    {
        return getDataRef<TYPE>(path.c_str());
    }

    /**
     * \brief Returns sub-tree of a given path.
     * \param path path of sub-tree to be retrieved
     * \return sub-tree
     */
    DataTree getSubTree(const char* path);
    inline DataTree getSubTree(const std::string& path)
    {
        return getSubTree(path.c_str());
    }

    /**
     * \return true if data tree is valid, false otherwise
     */
    inline bool isValid() const
    {
        return _root.get() != nullptr;
    }

protected:

    std::shared_ptr<GroupNode> _root;
};

} // namespace mc

#endif // MCUTILS_DATA_DATATREE_H_
