#include <gtest/gtest.h>

#include <cmath>

#include <mcutils/data/ValueNode.h>

////////////////////////////////////////////////////////////////////////////////

class TestValueNode : public ::testing::Test
{
protected:
    TestValueNode() {}
    virtual ~TestValueNode() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestValueNode, CanConstruct)
{
    mc::ValueNode<bool> *nodeB = nullptr;
    EXPECT_NO_THROW( nodeB = new mc::ValueNode<bool>() );
    delete nodeB;

    mc::ValueNode<int> *nodeI = nullptr;
    EXPECT_NO_THROW( nodeI = new mc::ValueNode<int>() );
    delete nodeI;

    mc::ValueNode<double> *nodeD = nullptr;
    EXPECT_NO_THROW( nodeD = new mc::ValueNode<double>() );
    delete nodeD;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestValueNode, CanDestruct)
{
    mc::ValueNode<bool> *nodeB = new mc::ValueNode<bool>();
    EXPECT_NO_THROW( delete nodeB );

    mc::ValueNode<int> *nodeI = new mc::ValueNode<int>();
    EXPECT_NO_THROW( delete nodeI );

    mc::ValueNode<double> *nodeD = new mc::ValueNode<double>();
    EXPECT_NO_THROW( delete nodeD );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestValueNode, CanInstantiate)
{
    mc::ValueNode<bool> nodeB;
    EXPECT_FALSE( nodeB.getValue() );

    mc::ValueNode<int> nodeI;
    EXPECT_EQ( nodeI.getValue(), 0 );

    mc::ValueNode<double> nodeD;
    EXPECT_NEAR( nodeD.getValue(), 0.0, 1.0e-12 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestValueNode, CanGetValue)
{
    mc::ValueNode<bool> nodeB;
    EXPECT_FALSE( nodeB.getValue() );
    nodeB.setValue( true );
    EXPECT_TRUE( nodeB.getValue() );

    mc::ValueNode<int> nodeI;
    EXPECT_EQ( nodeI.getValue(), 0 );
    nodeI.setValue( -666 );
    EXPECT_EQ( nodeI.getValue(), -666 );

    mc::ValueNode<double> nodeD;
    EXPECT_NEAR( nodeD.getValue(), 0.0, 1.0e-12 );
    nodeD.setValue( M_PI );
    EXPECT_NEAR( nodeD.getValue(), M_PI, 1.0e-12 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestValueNode, CanSetValue)
{
    mc::ValueNode<bool> nodeB;
    EXPECT_FALSE( nodeB.getValue() );
    nodeB.setValue( true );
    EXPECT_TRUE( nodeB.getValue() );

    mc::ValueNode<int> nodeI;
    EXPECT_EQ( nodeI.getValue(), 0 );
    nodeI.setValue( -666 );
    EXPECT_EQ( nodeI.getValue(), -666 );

    mc::ValueNode<double> nodeD;
    EXPECT_NEAR( nodeD.getValue(), 0.0, 1.0e-12 );
    nodeD.setValue( M_PI );
    EXPECT_NEAR( nodeD.getValue(), M_PI, 1.0e-12 );
}
