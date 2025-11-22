#include <gtest/gtest.h>

#include <cmath>

#include <units.h>

#include <mcutils/math/Table.h>

using namespace units::literals;

class TestTable : public ::testing::Test
{
protected:
    TestTable() {}
    virtual ~TestTable() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestTable, CanInstantiate)
{
    mc::Table<double,double> tab1;
    EXPECT_EQ(tab1.size(), 1);
    EXPECT_DOUBLE_EQ(tab1.getValue(0.0), 0.0);
    EXPECT_DOUBLE_EQ(tab1.getValue(1.7), 0.0);

    mc::Table<double,double> tab2(2.2, 1.7);
    EXPECT_EQ(tab2.size(), 1);
    EXPECT_DOUBLE_EQ(tab2.getValue(0.0), 2.2);
    EXPECT_DOUBLE_EQ(tab2.getValue(1.7), 2.2);
}

TEST_F(TestTable, CanInstantiateAndSetDataFromArray)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.getValue(key_values[i]), table_data[i]);
    }
}

TEST_F(TestTable, CanInstantiateAndSetDataFromVector)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    for ( unsigned int i = 0; i < key_values.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.getValue(key_values[i]), table_data[i]);
    }
}

TEST_F(TestTable, CanInstantiateAndCopy)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);
    mc::Table<double,double> tab1(tab);

    for ( unsigned int i = 0; i < key_values.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab1.getValue(key_values[i]), tab.getValue(key_values[i]));
    }
}

TEST_F(TestTable, CanInstantiateAndMove)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(std::move(mc::Table<double,double>(key_values, table_data)));

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.getValue(key_values[i]), table_data[i]);
    }
}

TEST_F(TestTable, CanGetKeyByIndex)
{
    mc::Table<double,double> tab0;
    EXPECT_DOUBLE_EQ(tab0.getKeyByIndex(0), 0.0);

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.getKeyByIndex(0), -2.0);
    EXPECT_DOUBLE_EQ(tab.getKeyByIndex(1), -1.0);
    EXPECT_DOUBLE_EQ(tab.getKeyByIndex(2),  0.0);
    EXPECT_DOUBLE_EQ(tab.getKeyByIndex(3),  1.0);
    EXPECT_DOUBLE_EQ(tab.getKeyByIndex(4),  2.0);
    EXPECT_DOUBLE_EQ(tab.getKeyByIndex(5),  3.0);
}

TEST_F(TestTable, CanGetKeyByIndexNotInited)
{
    mc::Table<double,double> tab;
    EXPECT_TRUE(std::isnan(tab.getKeyByIndex(1)));
}

TEST_F(TestTable, CanGetSize)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    EXPECT_EQ(tab.size(), 6);
}

TEST_F(TestTable, CanGetKeyOfValueMin)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.getKeyOfValueMin(), 0.0);
}

TEST_F(TestTable, CanGetKeyOfValueMinRanged)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.getKeyOfValueMin(-2.0, 0.0), 0.0);
}

TEST_F(TestTable, CanGetKeyOfValueMax)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.getKeyOfValueMax(), 3.0);
}

TEST_F(TestTable, CanGetKeyOfValueMaxRanged)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.getKeyOfValueMax(1.0, 2.0), 2.0);
}

TEST_F(TestTable, CanGetValue)
{
    mc::Table<double,units::length::meter_t> tab0;
    EXPECT_DOUBLE_EQ(tab0.getValue(0.0)(), 0.0);
    EXPECT_DOUBLE_EQ(tab0.getValue(1.7)(), 0.0);

    // y = x^2 - 1
    std::vector<double>                 key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<units::length::meter_t> table_data {  1_m,  0_m, -1_m,  0_m,  3_m,  8_m };

    mc::Table<double,units::length::meter_t> tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.getValue(2.0)(), 3.0);
}

TEST_F(TestTable, CanGetValueFromEmptyTable)
{
    std::vector<double> key_values;
    std::vector<double> table_data;
    mc::Table<double,double> tab(key_values, table_data);
    double x = tab.getValue(0.0);
    EXPECT_FALSE(x == x); // NaN
}

TEST_F(TestTable, CanGetValueAndInterpolate)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.getValue(2.5), 5.5);
}

TEST_F(TestTable, CanGetValueOutOfRange)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.getValue( -9.0 ), 1.0);
    EXPECT_DOUBLE_EQ(tab.getValue(  9.0 ), 8.0);
}

TEST_F(TestTable, CanGetValueByIndex)
{
    mc::Table<double,double> tab0;
    EXPECT_DOUBLE_EQ(tab0.getValueByIndex(0), 0.0);
    EXPECT_TRUE(std::isnan(tab0.getValueByIndex(1)));

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.getValueByIndex(0), table_data[0]);
    EXPECT_DOUBLE_EQ(tab.getValueByIndex(1), table_data[1]);
    EXPECT_DOUBLE_EQ(tab.getValueByIndex(2), table_data[2]);
    EXPECT_DOUBLE_EQ(tab.getValueByIndex(3), table_data[3]);
    EXPECT_DOUBLE_EQ(tab.getValueByIndex(4), table_data[4]);
    EXPECT_DOUBLE_EQ(tab.getValueByIndex(5), table_data[5]);
}

TEST_F(TestTable, CanGetFirstValue)
{
    mc::Table<double,double> tab0;
    EXPECT_DOUBLE_EQ(tab0.getFirstValue(), 0.0);

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.getFirstValue(), table_data[0]);
}

TEST_F(TestTable, CanGetFirstValueFromEmptyTable)
{
    std::vector<double> key_values;
    std::vector<double> table_data;
    mc::Table<double,double> tab(key_values, table_data);
    double x = tab.getFirstValue();
    EXPECT_FALSE(x == x); // NaN
}

TEST_F(TestTable, CanGetLastValue)
{
    mc::Table<double,double> tab0;
    EXPECT_DOUBLE_EQ( tab0.getLastValue(), 0.0 );

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.getLastValue(), table_data[5]);
}

TEST_F(TestTable, CanGetLastValueFromEmptyTable)
{
    std::vector<double> key_values;
    std::vector<double> table_data;
    mc::Table<double,double> tab(key_values, table_data);
    double x = tab.getLastValue();
    EXPECT_FALSE(x == x); // NaN
}

TEST_F(TestTable, CanGetValueMin)
{
    mc::Table<double,double> tab0;
    EXPECT_DOUBLE_EQ(tab0.getValueMin(), 0.0);

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.getValueMin(), -1.0);
}

TEST_F(TestTable, CanGetValueMinFromEmptyTable)
{
    std::vector<double> key_values;
    std::vector<double> table_data;
    mc::Table<double,double> tab(key_values, table_data);
    double x = tab.getValueMin();
    EXPECT_FALSE(x == x); // NaN
}

TEST_F(TestTable, CanGetValueMax)
{
    mc::Table<double,double> tab0;
    EXPECT_NEAR(tab0.getValueMax(), 0.0, 1.0e-16);

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    EXPECT_DOUBLE_EQ(tab.getValueMax(), 8.0);
}

TEST_F(TestTable, CanGetValueMaxFromEmptyTable)
{
    std::vector<double> key_values;
    std::vector<double> table_data;
    mc::Table<double,double> tab(key_values, table_data);
    double x = tab.getValueMax();
    EXPECT_FALSE(x == x); // NaN
}

TEST_F(TestTable, CanValidate)
{
    std::vector<double> k1 { 0.0,  1.0,  2.0 };
    std::vector<double> v1 { 0.0,  1.0,  2.0 };
    mc::Table<double,double> t1(k1, v1);
    EXPECT_TRUE(t1.isValid());

    std::vector<double> k2 { std::numeric_limits<double>::quiet_NaN(), 1.0, 2.0 };
    std::vector<double> v2 { 0.0, 1.0, 2.0 };
    mc::Table<double,double> t2(k2, v2);
    EXPECT_FALSE(t2.isValid());

    std::vector<double> k3 { 0.0, 1.0, 2.0 };
    std::vector<double> v3 { std::numeric_limits<double>::quiet_NaN(), 1.0, 2.0 };
    mc::Table<double,double> t3(k3, v3);
    EXPECT_FALSE(t3.isValid());
}

TEST_F(TestTable, CanMultiplyKeys)
{
    const double coef = 2.0;

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    tab.multiplyKeys(coef);

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.getKeyByIndex(i), key_values[i] * coef);
        EXPECT_DOUBLE_EQ(tab.getValue(key_values[i] * coef), table_data[i]);
    }

    EXPECT_DOUBLE_EQ(tab.getValue(1.5 * coef), 1.5);
}

TEST_F(TestTable, CanMultiplyValues)
{
    const double coef = 2.0;

    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab(key_values, table_data);

    tab.multiplyValues(coef);

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.getKeyByIndex(i), key_values[i]);
        EXPECT_DOUBLE_EQ(tab.getValue(key_values[i]), table_data[i] * coef);
    }

    EXPECT_DOUBLE_EQ(tab.getValue(1.5), 1.5 * coef);
}

TEST_F(TestTable, CanConvertToString)
{
    std::vector<double> key_values { 0.0,  1.0,  2.0 };
    std::vector<double> table_data { 0.0,  2.0,  4.0 };

    mc::Table<double,double> tab(key_values, table_data);

    EXPECT_STREQ(tab.toString().c_str(), "0\t0\n1\t2\n2\t4\n");
}

TEST_F(TestTable, CanSetDataFromVector)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab;
    tab.setData(key_values, table_data);

    for ( unsigned int i = 0; i < key_values.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.getValue(key_values[i]), table_data[i]);
    }
}

TEST_F(TestTable, CanSetFromString)
{
    char str[] =
    { R"##(
      -2.0  4.0
      -1.0  1.0
       0.0  0.0
       1.0  1.0
       2.0  4.0
       3.0  9.0
    )##" };
    mc::Table<double,double> tab;
    tab.setFromString(str);

    EXPECT_TRUE(tab.isValid());

    EXPECT_EQ(tab.size(), 6);

    for ( int i = 0; i < 6; ++i )
    {
        double x = i - 2;
        double y = x*x;
        EXPECT_DOUBLE_EQ(tab.getValue(x), y);
    }

    char str2[] = { "lorem ipsum" };
    mc::Table<double,double> tab2;
    tab2.setFromString(str2);
    EXPECT_FALSE(tab2.isValid());
}

TEST_F(TestTable, CanAdd)
{
    mc::Table<double,double> tab;

    std::vector<double> k0 { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> t1 {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 }; // y = x^2 - 1
    std::vector<double> t2 { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 }; // y = x

    mc::Table<double,double> tab1(k0, t1);
    mc::Table<double,double> tab2(k0, t2);

    tab = tab1 + tab2;

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.getKeyByIndex(i), k0[i]);
        EXPECT_DOUBLE_EQ(tab.getValue(k0[i]), t1[i] + t2[i]);
    }
}

TEST_F(TestTable, CanAssign)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab1(key_values, table_data);
    mc::Table<double,double> tab;

    tab = tab1;

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.getValue(key_values[i]), table_data[i]);
    }
}

TEST_F(TestTable, CanAssignAndMove)
{
    // y = x^2 - 1
    std::vector<double> key_values { -2.0, -1.0,  0.0,  1.0,  2.0,  3.0 };
    std::vector<double> table_data {  1.0,  0.0, -1.0,  0.0,  3.0,  8.0 };

    mc::Table<double,double> tab;
    tab = std::move(mc::Table<double,double>(key_values, table_data));

    for ( unsigned int i = 0; i < tab.size(); ++i )
    {
        EXPECT_DOUBLE_EQ(tab.getValue(key_values[i]), table_data[i]);
    }
}