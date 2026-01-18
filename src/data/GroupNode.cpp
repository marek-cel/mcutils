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

#include <mcutils/data/GroupNode.h>

#include <mcutils/data/ValueNode.h>

namespace mc {

GroupNode::GroupNode(const char* name)
    : Node(name)
{}

std::weak_ptr<Node> GroupNode::getNode(const char* path)
{
    std::lock_guard<std::mutex> lock(_mutex);
    std::string path_temp = str::toLower(path);
    return findNode(path_temp.c_str());
}

void GroupNode::removeChildren()
{
    std::lock_guard<std::mutex> lock(_mutex);
    _children.clear();
}

std::weak_ptr<Node> GroupNode::findNode(const char* path)
{
    std::string path_temp = path;

    stripDataPathDots(path_temp.c_str());

    if ( path_temp.length() > 0 )
    {
        SplittedDataPath spath = splitDataPath(path_temp.c_str());
        Children::iterator it = _children.find(spath.lead);
        if ( it != _children.end() )
        {
            if ( spath.trail.size() > 0 )
            {
                std::shared_ptr<GroupNode> gnode_sp =
                        std::dynamic_pointer_cast<GroupNode,Node>(it->second);

                if ( gnode_sp.get() )
                {
                    return gnode_sp->findNode(spath.trail.c_str());
                }
            }
            else
            {
                return it->second;
            }
        }
    }

    return std::weak_ptr<Node>();
}

} // namespace mc
