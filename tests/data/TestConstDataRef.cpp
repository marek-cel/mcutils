#include <gtest/gtest.h>

#include <mcutils/data/ConstDataRef.h>
#include <mcutils/data/ValueNode.h>

class TestConstDataRef : public ::testing::Test
{
protected:
    TestConstDataRef() {}
    virtual ~TestConstDataRef() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestConstDataRef, CanConstruct)
{
    mc::ConstDataRef<bool>* ref_b = nullptr;
    EXPECT_NO_THROW(ref_b = new mc::ConstDataRef<bool>());
    delete ref_b;

    mc::ConstDataRef<int>* ref_i = nullptr;
    EXPECT_NO_THROW(ref_i = new mc::ConstDataRef<int>());
    delete ref_i;

    mc::ConstDataRef<double>* ref_d = nullptr;
    EXPECT_NO_THROW(ref_d = new mc::ConstDataRef<double>());
    delete ref_d;
}

TEST_F(TestConstDataRef, CanDestruct)
{
    mc::ConstDataRef<bool>* ref_b = new mc::ConstDataRef<bool>();
    EXPECT_NO_THROW(delete ref_b);

    mc::ConstDataRef<int>* ref_i = new mc::ConstDataRef<int>();
    EXPECT_NO_THROW(delete ref_i);

    mc::ConstDataRef<double>* ref_d = new mc::ConstDataRef<double>();
    EXPECT_NO_THROW(delete ref_d);
}

TEST_F(TestConstDataRef, CanInstantiate)
{
    mc::ConstDataRef<bool> ref_b1;
    EXPECT_FALSE(ref_b1.getValue());
    EXPECT_FALSE(ref_b1.isValid());

    mc::ConstDataRef<int> ref_i1;
    EXPECT_EQ(ref_i1.getValue(), 0);
    EXPECT_FALSE(ref_i1.isValid());

    mc::ConstDataRef<double> ref_d1;
    EXPECT_NEAR(ref_d1.getValue(), 0.0, 1.0e-12);
    EXPECT_FALSE(ref_d1.isValid());
}

TEST_F(TestConstDataRef, CanInstantiateWithValueNode)
{
    std::shared_ptr<mc::ValueNode<bool>> vnode_b = std::make_shared<mc::ValueNode<bool>>();
    mc::ConstDataRef<bool> ref_b(vnode_b);
    EXPECT_TRUE(ref_b.isValid());
    EXPECT_FALSE(ref_b.getValue());

    std::shared_ptr<mc::ValueNode<int>> vnode_i = std::make_shared<mc::ValueNode<int>>();
    mc::ConstDataRef<int> ref_i(vnode_i);
    EXPECT_TRUE(ref_i.isValid());
    EXPECT_EQ(ref_i.getValue(), 0);

    std::shared_ptr<mc::ValueNode<double>> vnode_d = std::make_shared<mc::ValueNode<double>>();
    mc::ConstDataRef<double> ref_d(vnode_d);
    EXPECT_TRUE(ref_d.isValid());
    EXPECT_NEAR(ref_d.getValue(), 0.0, 1.0e-12);
}

TEST_F(TestConstDataRef, CanGetValue)
{
    std::shared_ptr<mc::ValueNode<bool>> vnode_b = std::make_shared<mc::ValueNode<bool>>();
    vnode_b->setValue(true);
    mc::ConstDataRef<bool> ref_b(vnode_b);
    EXPECT_TRUE(ref_b.getValue());

    std::shared_ptr<mc::ValueNode<int>> vnode_i = std::make_shared<mc::ValueNode<int>>();
    vnode_i->setValue(1);
    mc::ConstDataRef<int> ref_i(vnode_i);
    EXPECT_EQ(ref_i.getValue(), 1);

    std::shared_ptr<mc::ValueNode<double>> vnode_d = std::make_shared<mc::ValueNode<double>>();
    vnode_d->setValue(3.14);
    mc::ConstDataRef<double> ref_d(vnode_d);
    EXPECT_NEAR(ref_d.getValue(), 3.14, 1.0e-12);
}
