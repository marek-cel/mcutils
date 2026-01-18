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
#ifndef MCUTILS_DATA_GROUPNODE_H_
#define MCUTILS_DATA_GROUPNODE_H_

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>

#include <mcutils/mcutils_api.h>
#include <mcutils/Result.h>

#include <mcutils/data/DataPathUtils.h>
#include <mcutils/data/Node.h>
#include <mcutils/misc/StringUtils.h>

namespace mc {

/**
 * \brief Group node class.
 */
class MCUTILS_API GroupNode : public Node
{
public:

    using Children = std::map<std::string, std::shared_ptr<Node>>;

    /**
     * \param name node name
     */
    explicit GroupNode(const char* name = "");

    /**
     * \brief Creates node of a given path.
     * \tparam node type (e.g.: GroupNode, ValueNode<int>, ValueNode<bool>)
     * \param path Path relative to the node.
     * \param type New node type.
     * \return mc::Success on success or mc::Failure on failure
     */
    template <class TYPE>
    Result addNode(const char* path)
    {
        std::string path_temp = path;
        path_temp = stripDataPathDots(path_temp.c_str());
        if ( path_temp.length() > 0 )
        {
            path_temp = str::toLower(path_temp);
            SplittedDataPath spath = splitDataPath(path_temp.c_str());
            if ( spath.trail.size() > 0 )
            {
                Result result = Result::Success;

                if ( _children.count(spath.lead) == 0 )
                {
                    result = addNode<GroupNode>(spath.lead.c_str());
                }

                if ( result != Result::Success )
                {
                    return result;
                }

                std::weak_ptr<Node> node_wp = findNode(spath.lead.c_str());
                if ( node_wp.expired() )
                {
                    return Result::Failure;
                }

                std::shared_ptr<Node> node_sp = node_wp.lock();
                std::shared_ptr<GroupNode> gnode_sp = std::dynamic_pointer_cast<GroupNode,Node>(node_sp);
                if ( gnode_sp.get() )
                {
                    return gnode_sp->addNode<TYPE>(spath.trail.c_str());
                }
            }
            else
            {
                if ( spath.lead.size() > 0 )
                {
                    if ( _children.count(spath.lead) == 0 )
                    {
                        return createNode<TYPE>(spath.lead.c_str());
                    }
                }
            }
        }

        return Result::Failure;
    }

    /**
     * \brief Creates node of a given path.
     * \tparam node type (e.g.: GroupNode, ValueNode<int>, ValueNode<bool>)
     * \param path Path relative to the node.
     * \param type New node type.
     * \return mc::Success on success or mc::Failure on failure
     */
    template <class TYPE>
    inline Result addNode(const std::string& path)
    {
        return addNode<TYPE>(path.c_str());
    }

    /**
     * \brief Returns pointer to node of the given relative path on success or null
     * pointer on failure (e.g. if node doesn't exist).
     *
     * This function is case insensitive.
     *
     * \param path Path relative to the node.
     * \return pointer to node of the given path on success or null pointer on failure
     */
    std::weak_ptr<Node> getNode(const char* path);

    /**
     * Removes all children.
     */
    void removeChildren();

protected:

    std::mutex _mutex;      ///< node mutex
    Children _children;     ///< node children

    /**
     * \brief Creates a child node of the given name.
     * \tparam node type (e.g.: GroupNode, ValueNode<int>, ValueNode<bool>)
     * \param name node name
     * \return mc::Success on success or mc::Failure on failure
     */
    template <class TYPE>
    Result createNode(const char* name)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        std::string name_lower = str::toLower(name);
        std::shared_ptr<Node> node = std::make_shared<TYPE>(name_lower.c_str());
        if ( node.get() )
        {
            std::pair<typename std::map<std::string, std::shared_ptr<Node>>::iterator, bool> temp =
                    _children.insert(std::pair<std::string, std::shared_ptr<Node>>(name_lower, node));

            if (temp.second == true)
            {
                return Result::Success;
            }
            else
            {
                node = nullptr;
            }
        }

        return Result::Failure;
    }

    /**
     * \brief Creates a child node of the given name.
     * \tparam node type (e.g.: GroupNode, ValueNode<int>, ValueNode<bool>)
     * \param name node name
     * \return mc::Success on success or mc::Failure on failure
     */
    template <class TYPE>
    inline Result createNode(const std::string& name)
    {
        return createNode<TYPE>(name.c_str());
    }

    /**
     * \brief Returns pointer to node of the given relative path on success and null
     * pointer on failure (e.g. if node doesn't exist).
     *
     * This function is case sensitive.
     *
     * \param path Path relative to the node.
     * \return pointer to node of the given path on success and null pointer on failure
     */
    std::weak_ptr<Node> findNode(const char* path);
};

} // namespace mc

#endif // MCUTILS_DATA_GROUPNODE_H_
