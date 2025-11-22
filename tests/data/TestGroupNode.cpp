#include <gtest/gtest.h>

#include <mcutils/data/GroupNode.h>
#include <mcutils/data/ValueNode.h>

class TestGroupNode : public ::testing::Test
{
protected:
    TestGroupNode() {}
    virtual ~TestGroupNode() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestGroupNode, CanConstruct)
{
    mc::GroupNode* node = nullptr;
    EXPECT_NO_THROW(node = new mc::GroupNode());
    delete node;
}

TEST_F(TestGroupNode, CanDestruct)
{
    mc::GroupNode* node = new mc::GroupNode();
    EXPECT_NO_THROW(delete node);
}

TEST_F(TestGroupNode, CanInstantiate)
{
    mc::GroupNode node;
    EXPECT_STREQ(node.getName().c_str(), "");
}

TEST_F(TestGroupNode, CanInstantiateAndSetName)
{
    mc::GroupNode node("xxx");
    EXPECT_STREQ(node.getName().c_str(), "xxx");
}

TEST_F(TestGroupNode, CanAddNodeBool)
{
    mc::GroupNode root;
    EXPECT_EQ(mc::Result::Success, root.addNode<mc::ValueNode<bool>>("group.data_b"));
    std::weak_ptr<mc::Node> node_wp = root.getNode("group.data_b");
    EXPECT_FALSE(node_wp.expired());
    std::shared_ptr<mc::Node> node_sp = node_wp.lock();
    std::shared_ptr<mc::ValueNode<bool>> vnode_b_sp
        = std::dynamic_pointer_cast<mc::ValueNode<bool>,mc::Node>(node_sp);
    EXPECT_NE(vnode_b_sp.get(), nullptr);
}

TEST_F(TestGroupNode, CanAddNodeInt)
{
    mc::GroupNode root;
    EXPECT_EQ(mc::Result::Success, root.addNode<mc::ValueNode<int>>("group.data_i"));
    std::weak_ptr<mc::Node> node_wp = root.getNode("group.data_i");
    EXPECT_FALSE(node_wp.expired());
    std::shared_ptr<mc::Node> node_sp = node_wp.lock();
    std::shared_ptr<mc::ValueNode<int>> vnode_i_sp
        = std::dynamic_pointer_cast<mc::ValueNode<int>,mc::Node>(node_sp);
    EXPECT_NE(vnode_i_sp.get(), nullptr);
}

TEST_F(TestGroupNode, CanAddNodeFloat)
{
    mc::GroupNode root;
    EXPECT_EQ(mc::Result::Success, root.addNode<mc::ValueNode<double>>("group.data_d"));
    std::weak_ptr<mc::Node> node_wp = root.getNode("group.data_d");
    EXPECT_FALSE(node_wp.expired());
    std::shared_ptr<mc::Node> node_sp = node_wp.lock();
    std::shared_ptr<mc::ValueNode<double>> vnode_d_sp
        = std::dynamic_pointer_cast<mc::ValueNode<double>,mc::Node>(node_sp);
    EXPECT_NE(vnode_d_sp.get(), nullptr);
}

TEST_F(TestGroupNode, CanGetNode)
{
    mc::GroupNode root;

    root.addNode<mc::ValueNode<bool>>("group.data_b");
    root.addNode<mc::ValueNode<int>>("group.data_i");
    root.addNode<mc::ValueNode<double>>("group.data_d");

    std::weak_ptr<mc::Node> node_wp;
    std::shared_ptr<mc::Node> node_sp;
    std::shared_ptr<mc::GroupNode> gnode_sp;
    std::shared_ptr<mc::ValueNode<bool>> vnode_b_sp;
    std::shared_ptr<mc::ValueNode<int>> vnode_i_sp;
    std::shared_ptr<mc::ValueNode<double>> vnode_d_sp;

    node_wp = root.getNode("group");
    EXPECT_FALSE(node_wp.expired());
    node_sp = node_wp.lock();
    gnode_sp = std::dynamic_pointer_cast<mc::GroupNode,mc::Node>(node_sp);
    EXPECT_NE(gnode_sp.get(), nullptr);

    node_wp = root.getNode("group.data_b");
    EXPECT_FALSE(node_wp.expired());
    node_sp = node_wp.lock();
    vnode_b_sp = std::dynamic_pointer_cast<mc::ValueNode<bool>,mc::Node>(node_sp);
    EXPECT_NE(vnode_b_sp.get(), nullptr);

    node_wp = root.getNode("group.data_i");
    EXPECT_FALSE(node_wp.expired());
    node_sp = node_wp.lock();
    vnode_i_sp = std::dynamic_pointer_cast<mc::ValueNode<int>,mc::Node>(node_sp);
    EXPECT_NE(vnode_i_sp.get(), nullptr);

    node_wp = root.getNode("group.data_d");
    EXPECT_FALSE(node_wp.expired());
    node_sp = node_wp.lock();
    vnode_d_sp = std::dynamic_pointer_cast<mc::ValueNode<double>,mc::Node>(node_sp);
    EXPECT_NE(vnode_d_sp.get(), nullptr);

    node_wp = root.getNode("group.data666");
    EXPECT_TRUE(node_wp.expired());
}

TEST_F(TestGroupNode, CanRemoveChildren)
{
    mc::GroupNode root;

    root.addNode<mc::ValueNode<bool>>("group.data_b");
    root.addNode<mc::ValueNode<int>>("group.data_i");
    root.addNode<mc::ValueNode<double>>("group.data_d");

    std::weak_ptr<mc::Node> node_wp;
    std::shared_ptr<mc::Node> node_sp;
    std::shared_ptr<mc::GroupNode> gnode_sp;

    node_wp = root.getNode("group");
    EXPECT_FALSE( node_wp.expired() );
    node_sp = node_wp.lock();
    gnode_sp = std::dynamic_pointer_cast<mc::GroupNode,mc::Node>(node_sp);
    gnode_sp->removeChildren();

    node_wp = root.getNode("group");
    EXPECT_FALSE(node_wp.expired());

    node_wp = root.getNode("group.data_b");
    EXPECT_TRUE(node_wp.expired());

    node_wp = root.getNode("group.data_i");
    EXPECT_TRUE(node_wp.expired());

    node_wp = root.getNode("group.data_d");
    EXPECT_TRUE(node_wp.expired());
}