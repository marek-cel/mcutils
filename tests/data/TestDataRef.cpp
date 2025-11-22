#include <gtest/gtest.h>

#include <mcutils/data/DataRef.h>
#include <mcutils/data/ValueNode.h>

class TestDataRef : public ::testing::Test
{
protected:
    TestDataRef() {}
    virtual ~TestDataRef() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestDataRef, CanConstruct)
{
    mc::DataRef<bool>* ref_b = nullptr;
    EXPECT_NO_THROW(ref_b = new mc::DataRef<bool>());
    delete ref_b;

    mc::DataRef<int>* ref_i = nullptr;
    EXPECT_NO_THROW(ref_i = new mc::DataRef<int>());
    delete ref_i;

    mc::DataRef<double>* ref_d = nullptr;
    EXPECT_NO_THROW(ref_d = new mc::DataRef<double>());
    delete ref_d;
}

TEST_F(TestDataRef, CanDestruct)
{
    mc::DataRef<bool>* ref_b = new mc::DataRef<bool>();
    EXPECT_NO_THROW(delete ref_b);

    mc::DataRef<int>* ref_i = new mc::DataRef<int>();
    EXPECT_NO_THROW(delete ref_i);

    mc::DataRef<double>* ref_d = new mc::DataRef<double>();
    EXPECT_NO_THROW(delete ref_d);
}

TEST_F(TestDataRef, CanInstantiate)
{
    mc::DataRef<bool> ref_b1;
    EXPECT_FALSE(ref_b1.getValue());
    EXPECT_FALSE(ref_b1.isValid());
    EXPECT_EQ(ref_b1.setValue(true), mc::Result::Failure);

    mc::DataRef<int> ref_i1;
    EXPECT_EQ(ref_i1.getValue(), 0);
    EXPECT_FALSE(ref_i1.isValid());
    EXPECT_EQ(ref_i1.setValue(1), mc::Result::Failure);

    mc::DataRef<double> ref_d1;
    EXPECT_NEAR(ref_d1.getValue(), 0.0, 1.0e-12);
    EXPECT_FALSE(ref_d1.isValid());
    EXPECT_EQ(ref_d1.setValue(3.14), mc::Result::Failure);

    std::shared_ptr<mc::ValueNode<bool>> vnode_b_sp = std::make_shared<mc::ValueNode<bool>>();
    std::weak_ptr<mc::ValueNode<bool>> vnode_b_wp = vnode_b_sp;
    mc::DataRef<bool> ref_b(vnode_b_wp);
    EXPECT_FALSE(ref_b.getValue());
    EXPECT_TRUE(ref_b.isValid());
    EXPECT_EQ(ref_b.setValue(true), mc::Result::Success);

    std::shared_ptr<mc::ValueNode<int>> vnode_i_sp = std::make_shared<mc::ValueNode<int>>();
    std::weak_ptr<mc::ValueNode<int>> vnode_i_wp = vnode_i_sp;
    mc::DataRef<int> ref_i(vnode_i_wp);
    EXPECT_EQ(ref_i.getValue(), 0);
    EXPECT_TRUE(ref_i.isValid());
    EXPECT_EQ(ref_i.setValue(1), mc::Result::Success);

    std::shared_ptr<mc::ValueNode<double>> vnode_d_sp = std::make_shared<mc::ValueNode<double>>();
    std::weak_ptr<mc::ValueNode<double>> vnode_d_wp = vnode_d_sp;
    mc::DataRef<double> ref_d(vnode_d_wp);
    EXPECT_NEAR(ref_d.getValue(), 0.0, 1.0e-12);
    EXPECT_TRUE(ref_d.isValid());
    EXPECT_EQ(ref_d.setValue(3.14), mc::Result::Success);
}

TEST_F(TestDataRef, CanGetValue)
{
    std::shared_ptr<mc::ValueNode<bool>> vnode_b_sp = std::make_shared<mc::ValueNode<bool>>();
    std::weak_ptr<mc::ValueNode<bool>> vnode_b_wp = vnode_b_sp;
    mc::DataRef<bool> ref_b(vnode_b_wp);
    EXPECT_EQ(ref_b.setValue(true), mc::Result::Success);
    EXPECT_TRUE(ref_b.getValue());

    std::shared_ptr<mc::ValueNode<int>> vnode_i_sp = std::make_shared<mc::ValueNode<int>>();
    std::weak_ptr<mc::ValueNode<int>> vnode_i_wp = vnode_i_sp;
    mc::DataRef<int> ref_i(vnode_i_wp);
    EXPECT_EQ(ref_i.setValue(1), mc::Result::Success);
    EXPECT_EQ(ref_i.getValue(), 1);

    std::shared_ptr<mc::ValueNode<double>> vnode_d_sp = std::make_shared<mc::ValueNode<double>>();
    std::weak_ptr<mc::ValueNode<double>> vnode_d_wp = vnode_d_sp;
    mc::DataRef<double> ref_d(vnode_d_wp);
    EXPECT_EQ(ref_d.setValue(3.14), mc::Result::Success);
    EXPECT_NEAR(ref_d.getValue(), 3.14, 1.0e-12);
}
