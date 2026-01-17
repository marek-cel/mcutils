#include <gtest/gtest.h>

#include <mcutils/physics/UnitsUtils.h>

class TestUnitsUtils : public ::testing::Test
{
protected:
    TestUnitsUtils() {}
    virtual ~TestUnitsUtils() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestUnitsUtils, ConvertToMeters)
{
    EXPECT_DOUBLE_EQ( mc::convertToMeters("m"   , 1.0)() , 1.0      );
    EXPECT_DOUBLE_EQ( mc::convertToMeters("cm"  , 1.0)() , 0.01     );
    EXPECT_DOUBLE_EQ( mc::convertToMeters("mm"  , 1.0)() , 0.001    );
    EXPECT_DOUBLE_EQ( mc::convertToMeters("ft"  , 1.0)() , 0.3048   );
    EXPECT_DOUBLE_EQ( mc::convertToMeters("in"  , 1.0)() , 0.0254   );
    EXPECT_DOUBLE_EQ( mc::convertToMeters("km"  , 1.0)() , 1000.0   );
    EXPECT_DOUBLE_EQ( mc::convertToMeters("mi"  , 1.0)() , 1609.344 );
    EXPECT_DOUBLE_EQ( mc::convertToMeters("nmi" , 1.0)() , 1852.0   );
}

TEST_F(TestUnitsUtils, ConvertToRadians)
{
    EXPECT_DOUBLE_EQ( mc::convertToRadians("rad", 1.0)() , 1.0          );
    EXPECT_DOUBLE_EQ( mc::convertToRadians("deg", 1.0)() , M_PI / 180.0 );
}

TEST_F(TestUnitsUtils, ConvertToMetersPerSecond)
{
    EXPECT_NEAR( mc::convertToMPS("mps" , 1.0)() , 1.0     , 1.0e-5 );
    EXPECT_NEAR( mc::convertToMPS("fps" , 1.0)() , 0.3048  , 1.0e-5 );
    EXPECT_NEAR( mc::convertToMPS("kph" , 1.0)() , 0.27777 , 1.0e-5 );
    EXPECT_NEAR( mc::convertToMPS("kts" , 1.0)() , 0.51444 , 1.0e-5 );
    EXPECT_NEAR( mc::convertToMPS("mph" , 1.0)() , 0.44704 , 1.0e-5 );
    EXPECT_NEAR( mc::convertToMPS("fpm" , 1.0)() , 0.00508 , 1.0e-5 );
}

TEST_F(TestUnitsUtils, ConvertToKilograms)
{
    EXPECT_DOUBLE_EQ( mc::convertToKilograms("kg"  , 1.0)() , 1.0        );
    EXPECT_DOUBLE_EQ( mc::convertToKilograms("g"   , 1.0)() , 0.001      );
    EXPECT_DOUBLE_EQ( mc::convertToKilograms("lb"  , 1.0)() , 0.45359237 );
    EXPECT_DOUBLE_EQ( mc::convertToKilograms("slug", 1.0)() , 14.5939029 );
    EXPECT_DOUBLE_EQ( mc::convertToKilograms("t"   , 1.0)() , 1000.0     );
}
