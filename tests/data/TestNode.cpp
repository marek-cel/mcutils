#include <gtest/gtest.h>

#include <mcutils/data/Node.h>

class TestNode : public ::testing::Test
{
protected:
    TestNode() {}
    virtual ~TestNode() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestNode, CanConstruct)
{
    mc::Node* node = nullptr;
    EXPECT_NO_THROW(node = new mc::Node("xxx"));
    delete node;
}

TEST_F(TestNode, CanDestruct)
{
    mc::Node* node = new mc::Node("xxx");
    EXPECT_NO_THROW(delete node);
}

TEST_F(TestNode, CanInstantiate)
{
    mc::Node node("xxx");
    EXPECT_STREQ(node.getName().c_str(), "xxx");
}

TEST_F(TestNode, CanGetName)
{
    mc::Node node("xxx");
    EXPECT_STREQ(node.getName().c_str(), "xxx");
}
