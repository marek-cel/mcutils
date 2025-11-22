#include <gtest/gtest.h>

#include <mcutils/data/DataTree.h>

class TestDataTree : public ::testing::Test
{
protected:
    TestDataTree() {}
    virtual ~TestDataTree() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestDataTree, CanConstruct)
{
    mc::DataTree *dt = nullptr;
    EXPECT_NO_THROW(dt = new mc::DataTree());
    delete dt;
}

TEST_F(TestDataTree, CanDestruct)
{
    mc::DataTree *dt = new mc::DataTree();
    EXPECT_NO_THROW(delete dt);
}

TEST_F(TestDataTree, CanInstantiate)
{
    mc::DataTree dt;
}

TEST_F(TestDataTree, CanAddEntry)
{
    mc::DataTree dt;

    mc::DataRef<bool>   dr_b;
    mc::DataRef<int>    dr_i;
    mc::DataRef<double> dr_d;

    dr_b = dt.addEntry<bool>   ( "dataBool" );
    dr_i = dt.addEntry<int>    ( "dataInt"  );
    dr_d = dt.addEntry<double> ( "dataDbl"  );
    EXPECT_TRUE(dr_b.isValid());
    EXPECT_TRUE(dr_i.isValid());
    EXPECT_TRUE(dr_d.isValid());

    dr_b = dt.addEntry<bool>   ( "dataBool" );
    dr_i = dt.addEntry<int>    ( "dataInt"  );
    dr_d = dt.addEntry<double> ( "dataDbl"  );
    EXPECT_FALSE(dr_b.isValid());
    EXPECT_FALSE(dr_i.isValid());
    EXPECT_FALSE(dr_d.isValid());

    dr_b = dt.addEntry<bool>   ( "group0.dataBool" );
    dr_i = dt.addEntry<int>    ( "group0.dataInt"  );
    dr_d = dt.addEntry<double> ( "group0.dataDbl"  );
    EXPECT_TRUE(dr_b.isValid());
    EXPECT_TRUE(dr_i.isValid());
    EXPECT_TRUE(dr_d.isValid());

    dr_b = dt.addEntry<bool>   ( "group1.dataBool" );
    dr_i = dt.addEntry<int>    ( "group1.dataInt"  );
    dr_d = dt.addEntry<double> ( "group1.dataDbl"  );
    EXPECT_TRUE(dr_b.isValid());
    EXPECT_TRUE(dr_i.isValid());
    EXPECT_TRUE(dr_d.isValid());
}

TEST_F(TestDataTree, CanGetDataRefBool)
{
    mc::DataTree dt;

    dt.addEntry<bool>("group.dataBool");
    dt.addEntry<int>("group.dataInt");
    dt.addEntry<double>("group.dataDbl");

    std::string path;

    mc::ConstDataRef<bool> dr;
    EXPECT_FALSE(dr.isValid());

    dr = dt.getDataRef<bool>("group.dataBool");
    EXPECT_TRUE(dr.isValid());

    path = "group.dataBool";
    dr = dt.getDataRef<bool>(path);
    EXPECT_TRUE(dr.isValid());

    dr = dt.getDataRef<bool>("group.dataInt");
    EXPECT_FALSE(dr.isValid());

    path = "group.dataInt";
    dr = dt.getDataRef<bool>(path);
    EXPECT_FALSE(dr.isValid());

    dr = dt.getDataRef<bool>("group.dataDbl");
    EXPECT_FALSE(dr.isValid());

    path = "group.dataDbl";
    dr = dt.getDataRef<bool>(path);
    EXPECT_FALSE(dr.isValid());

    dr = dt.getDataRef<bool>("group.dataNotExisting");
    EXPECT_FALSE(dr.isValid());

    dr = dt.getDataRef<bool>("group");
    EXPECT_FALSE(dr.isValid());
}

TEST_F(TestDataTree, CanGetDataRefInt)
{
    mc::DataTree dt;

    dt.addEntry<bool>("group.dataBool");
    dt.addEntry<int>("group.dataInt");
    dt.addEntry<double>("group.dataDbl");

    std::string path;

    mc::ConstDataRef<int> dr;
    EXPECT_FALSE(dr.isValid());

    dr = dt.getDataRef<int>("group.dataBool");
    EXPECT_FALSE(dr.isValid());

    path = "group.dataBool";
    dr = dt.getDataRef<int>(path);
    EXPECT_FALSE(dr.isValid());

    dr = dt.getDataRef<int>("group.dataInt");
    EXPECT_TRUE(dr.isValid());

    path = "group.dataInt";
    dr = dt.getDataRef<int>(path);
    EXPECT_TRUE(dr.isValid());

    dr = dt.getDataRef<int>("group.dataDbl");
    EXPECT_FALSE(dr.isValid());

    path = "group.dataDbl";
    dr = dt.getDataRef<int>(path);
    EXPECT_FALSE(dr.isValid());

    dr = dt.getDataRef<int>("group.dataNotExisting");
    EXPECT_FALSE(dr.isValid());

    dr = dt.getDataRef<int>("group");
    EXPECT_FALSE(dr.isValid());
}

TEST_F(TestDataTree, CanGetDataRefDouble)
{
    mc::DataTree dt;

    dt.addEntry<bool>("group.dataBool");
    dt.addEntry<int>("group.dataInt");
    dt.addEntry<double>("group.dataDbl");

    std::string path;

    mc::ConstDataRef<double> dr;
    EXPECT_FALSE(dr.isValid());

    dr = dt.getDataRef<double>("group.dataBool");
    EXPECT_FALSE(dr.isValid());

    path = "group.dataBool";
    dr = dt.getDataRef<double>(path);
    EXPECT_FALSE(dr.isValid());

    dr = dt.getDataRef<double>("group.dataInt");
    EXPECT_FALSE(dr.isValid());

    path = "group.dataInt";
    dr = dt.getDataRef<double>(path);
    EXPECT_FALSE(dr.isValid());

    dr = dt.getDataRef<double>("group.dataDbl");
    EXPECT_TRUE(dr.isValid());

    path = "group.dataDbl";
    dr = dt.getDataRef<double>(path);
    EXPECT_TRUE(dr.isValid());

    dr = dt.getDataRef<double>("group.dataNotExisting");
    EXPECT_FALSE(dr.isValid());

    dr = dt.getDataRef<double>("group");
    EXPECT_FALSE(dr.isValid());
}

TEST_F(TestDataTree, CanGetSubTree)
{
    mc::DataTree dt;

    dt.addEntry<bool>("group1.group2.dataBool");

    mc::ConstDataRef<bool> dr;
    EXPECT_FALSE(dr.isValid());

    mc::DataTree dt_sub = dt.getSubTree("group1");

    dr = dt_sub.getDataRef<bool>("group2.dataBool");
    EXPECT_TRUE(dr.isValid());
}

TEST_F(TestDataTree, CanValidate)
{
    std::shared_ptr<mc::GroupNode> gnode_sp;
    mc::DataTree dt1(gnode_sp);
    EXPECT_FALSE(dt1.isValid());

    mc::DataTree dt2;
    EXPECT_TRUE(dt2.isValid());
}
