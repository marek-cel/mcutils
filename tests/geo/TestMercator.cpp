#include <gtest/gtest.h>

#include <cmath>

#include <proj.h>

#include <mcutils/geo/Mercator.h>
#include <mcutils/geo/WGS84.h>

// linear position tolerance (0.1 mm)
#define LINEAR_POSITION_TOLERANCE 1.0e-4
// latitude and longitude tolerance (10^-9 rad ~ ca. 6 mm)
#define LAT_LON_TOLERANCE 1.0e-9

class TestMercator : public ::testing::Test
{
protected:
    TestMercator() {}
    virtual ~TestMercator() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMercator, CanInstantiate)
{
    mc::Mercator merc(mc::WGS84::ellipsoid);
}

TEST_F(TestMercator, CanCalculateLat)
{
    mc::Mercator merc(mc::WGS84::ellipsoid);

    constexpr units::length::meter_t nautical_mile = 1_nmi;
    constexpr units::length::meter_t arc_deg = 60.0 * nautical_mile;

    constexpr units::length::meter_t arc_deg30 = 30.0 * arc_deg;
    constexpr units::length::meter_t arc_deg45 = 45.0 * arc_deg;
    constexpr units::length::meter_t arc_deg60 = 60.0 * arc_deg;
    constexpr units::length::meter_t arc_deg90 = 90.0 * arc_deg;

    // expected values calculated with PROJ4
    // tests/mcsim/utils/geo/python/test_geo_mercator.py

    EXPECT_NEAR(merc.calculateLat(0_m)(), 0.0, 1.0e-6);

    EXPECT_NEAR(merc.calculateLat( arc_deg30 )(), 0.503202371118002  , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLat( arc_deg45 )(), 0.7174954798366173 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLat( arc_deg60 )(), 0.8979087261408331 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLat( arc_deg90 )(), 1.1622044409794392 , LAT_LON_TOLERANCE);

    EXPECT_NEAR(merc.calculateLat( -arc_deg30 )(), -0.5032023711180025 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLat( -arc_deg45 )(), -0.7174954798366175 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLat( -arc_deg60 )(), -0.8979087261408334 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLat( -arc_deg90 )(), -1.1622044409794392 , LAT_LON_TOLERANCE);
}

TEST_F(TestMercator, CanCalculateLon)
{
    mc::Mercator merc(mc::WGS84::ellipsoid);

    constexpr units::length::meter_t nautical_mile = 1_nmi;
    constexpr units::length::meter_t arc_deg = 60.0 * nautical_mile;

    constexpr units::length::meter_t arc_deg30  =  30.0 * arc_deg;
    constexpr units::length::meter_t arc_deg45  =  45.0 * arc_deg;
    constexpr units::length::meter_t arc_deg60  =  60.0 * arc_deg;
    constexpr units::length::meter_t arc_deg90  =  90.0 * arc_deg;
    constexpr units::length::meter_t arc_deg120 = 120.0 * arc_deg;
    constexpr units::length::meter_t arc_deg150 = 150.0 * arc_deg;
    constexpr units::length::meter_t arc_deg180 = 180.0 * arc_deg;

    // expected values calculated with PROJ4
    // tests/mcsim/utils/geo/python/test_geo_mercator.py

    EXPECT_NEAR(merc.calculateLon(0_m)(), 0.0, 1.0e-6);

    EXPECT_NEAR(merc.calculateLon( arc_deg30  )() , 0.522660457120943  , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLon( arc_deg45  )() , 0.7839906856814144 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLon( arc_deg60  )() , 1.045320914241886  , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLon( arc_deg90  )() , 1.5679813713628288 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLon( arc_deg120 )() , 2.090641828483772  , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLon( arc_deg150 )() , 2.613302285604715  , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLon( arc_deg180 )() , 3.1359627427256576 , LAT_LON_TOLERANCE);

    EXPECT_NEAR(merc.calculateLon( -arc_deg30  )() , -0.522660457120943  , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLon( -arc_deg45  )() , -0.7839906856814144 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLon( -arc_deg60  )() , -1.045320914241886  , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLon( -arc_deg90  )() , -1.5679813713628288 , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLon( -arc_deg120 )() , -2.090641828483772  , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLon( -arc_deg150 )() , -2.613302285604715  , LAT_LON_TOLERANCE);
    EXPECT_NEAR(merc.calculateLon( -arc_deg180 )() , -3.1359627427256576 , LAT_LON_TOLERANCE);
}

TEST_F(TestMercator, CanCalculateX)
{
    mc::Mercator merc(mc::WGS84::ellipsoid);

    // expected values calculated with PROJ4
    // tests/mcsim/utils/geo/python/test_geo_mercator.py

    EXPECT_NEAR(merc.calculateX(    0_deg )(),         0.000000000, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateX(   30_deg )(),   3339584.723798207, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateX(   45_deg )(),   5009377.085697311, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateX(   60_deg )(),   6679169.447596414, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateX(   90_deg )(),  10018754.171394622, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateX(  120_deg )(),  13358338.895192828, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateX(  150_deg )(),  16697923.618991036, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateX(  180_deg )(),  20037508.342789244, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateX(  -30_deg )(),  -3339584.723798207, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateX(  -45_deg )(),  -5009377.085697311, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateX(  -60_deg )(),  -6679169.447596414, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateX(  -90_deg )(), -10018754.171394622, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateX( -120_deg )(), -13358338.895192828, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateX( -150_deg )(), -16697923.618991036, LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateX( -180_deg )(), -20037508.342789244, LINEAR_POSITION_TOLERANCE);
}

TEST_F(TestMercator, CanCalculateY)
{
    mc::Mercator merc(mc::WGS84::ellipsoid);

    // expected values calculated with PROJ4
    // tests/mcsim/utils/geo/python/test_geo_mercator.py

    EXPECT_NEAR(merc.calculateY( 0_deg )(), 0.0, LINEAR_POSITION_TOLERANCE);

    EXPECT_NEAR(merc.calculateY( 30_deg )(), 3482189.0854086173 , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateY( 45_deg )(), 5591295.918553392  , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateY( 60_deg )(), 8362698.548500749  , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateY( 85_deg )(), 19929239.113379154 , LINEAR_POSITION_TOLERANCE);

    EXPECT_NEAR(merc.calculateY( -30_deg )(), -3482189.085408616  , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateY( -45_deg )(), -5591295.9185533915 , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateY( -60_deg )(), -8362698.548500745  , LINEAR_POSITION_TOLERANCE);
    EXPECT_NEAR(merc.calculateY( -85_deg )(), -19929239.113379147 , LINEAR_POSITION_TOLERANCE);
}
