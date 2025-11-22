#include <gtest/gtest.h>

#include <mcutils/geo/Ellipsoid.h>

class TestEllipsoid : public ::testing::Test
{
protected:
    TestEllipsoid() {}
    virtual ~TestEllipsoid() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestEllipsoid, CanConstruct)
{
    mc::Ellipsoid *ellipsoid = nullptr;
    EXPECT_NO_THROW(ellipsoid = new mc::Ellipsoid(1.0_m, 0.0));
    delete ellipsoid;
}

TEST_F(TestEllipsoid, CanDestruct)
{
    mc::Ellipsoid *ellipsoid = new mc::Ellipsoid(1.0_m, 0.0);
    EXPECT_NO_THROW(delete ellipsoid);
}

TEST_F(TestEllipsoid, CanInstantiate)
{
    // WGS-84 as reference data
    // Department of Defence World Geodetic System 1984, NIMA-TR-8350.2
    constexpr double a   = 6378137.0;           // [m] equatorial radius
    constexpr double b   = 6356752.3142;        // [m] polar radius
    constexpr double f   = 1.0 / 298.257223563; // [-] ellipsoid flattening

    constexpr double r1  = 6371008.7714;        // [m] mean radius
    constexpr double a2  = a * a;               // [m^2] equatorial radius squared
    constexpr double b2  = b * b;               // [m^2] polar radius squared
    constexpr double e2  = 6.6943799901400e-3;  // [-] ellipsoid first eccentricity squared
    constexpr double e   = 8.1819190842622e-2;  // [-] ellipsoid first eccentricity
    constexpr double ep2 = 6.7394967422800e-3;  // [-] ellipsoid second eccentricity squared
    constexpr double ep  = 8.2094437949696e-2;  // [-] ellipsoid second eccentricity

    mc::Ellipsoid ellipsoid(units::length::meter_t(a), f);

    EXPECT_NEAR(ellipsoid.a()()   , a   , 1.0e-3);
    EXPECT_NEAR(ellipsoid.f()     , f   , 1.0e-9);
    EXPECT_NEAR(ellipsoid.b()()   , b   , 1.0e-3);
    EXPECT_NEAR(ellipsoid.r1()()  , r1  , 1.0e-3);
    EXPECT_NEAR(ellipsoid.a2()()  , a2  , 1.0e3); // sic!
    EXPECT_NEAR(ellipsoid.b2()()  , b2  , 1.0e3); // sic!
    EXPECT_NEAR(ellipsoid.e2()    , e2  , 1.0e-9);
    EXPECT_NEAR(ellipsoid.e()     , e   , 1.0e-9);
    EXPECT_NEAR(ellipsoid.ep2()   , ep2 , 1.0e-9);
    EXPECT_NEAR(ellipsoid.ep()    , ep  , 1.0e-9);
}
