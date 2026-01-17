#include <gtest/gtest.h>

#include <mcutils/math/Matrix.h>

class TestRotMatrix : public ::testing::Test
{
protected:
    constexpr static int size = 3;
    TestRotMatrix() {}
    virtual ~TestRotMatrix() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestRotMatrix, CanGetIdentityMatrix)
{
    mc::RotMatrix m = mc::RotMatrix::getIdentityMatrix();

    EXPECT_DOUBLE_EQ(m(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m(0,1), 0.0);
    EXPECT_DOUBLE_EQ(m(0,2), 0.0);

    EXPECT_DOUBLE_EQ(m(1,0), 0.0);
    EXPECT_DOUBLE_EQ(m(1,1), 1.0);
    EXPECT_DOUBLE_EQ(m(1,2), 0.0);

    EXPECT_DOUBLE_EQ(m(2,0), 0.0);
    EXPECT_DOUBLE_EQ(m(2,1), 0.0);
    EXPECT_DOUBLE_EQ(m(2,2), 1.0);
}

TEST_F(TestRotMatrix, CanConstruct)
{
    mc::RotMatrix* m = nullptr;
    EXPECT_NO_THROW(m = new mc::RotMatrix());
    delete m;
}

TEST_F(TestRotMatrix, CanDestruct)
{
    mc::RotMatrix* m = new mc::RotMatrix();
    EXPECT_NO_THROW(delete m);
}

TEST_F(TestRotMatrix, CanInstantiate)
{
    mc::RotMatrix m;
    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            if ( r == c )
                EXPECT_DOUBLE_EQ(m(r,c), 1.0) << "Error at row " << r << " and col " << c;
            else
                EXPECT_DOUBLE_EQ(m(r,c), 0.0) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestRotMatrix, CanInstantiateAndCopy)
{
    constexpr int size = 3;

    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::RotMatrix m0;
    m0.setFromStdVector(x);

    mc::RotMatrix m1(m0);

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestRotMatrix, CanInstantiateAndSetData)
{
    mc::Matrix3x3 m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    EXPECT_DOUBLE_EQ(m1(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m1(0,1), 2.0);
    EXPECT_DOUBLE_EQ(m1(0,2), 3.0);
    EXPECT_DOUBLE_EQ(m1(1,0), 4.0);
    EXPECT_DOUBLE_EQ(m1(1,1), 5.0);
    EXPECT_DOUBLE_EQ(m1(1,2), 6.0);
    EXPECT_DOUBLE_EQ(m1(2,0), 7.0);
    EXPECT_DOUBLE_EQ(m1(2,1), 8.0);
    EXPECT_DOUBLE_EQ(m1(2,2), 9.0);
}

TEST_F(TestRotMatrix, CanInstantiateAndSetDataFromAnglesZeros)
{
    mc::Angles ang(0.0_rad, 0.0_rad, 0.0_rad);
    mc::RotMatrix m(ang);

    EXPECT_NEAR(m.xx(), 1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(), 1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(), 1.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanInstantiateAndSetDataFromPhiPi)
{
    mc::Angles ang(1.0_rad * M_PI, 0.0_rad, 0.0_rad);
    mc::RotMatrix m(ang);

    EXPECT_NEAR(m.xx(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(), -1.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanInstantiateAndSetDataFromThetaPi)
{
    mc::Angles ang(0.0_rad, 1.0_rad * M_PI, 0.0_rad);
    mc::RotMatrix m(ang);

    EXPECT_NEAR(m.xx(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(), -1.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanInstantiateAndSetDataFromPsiPi)
{
    mc::Angles ang(0.0_rad, 0.0_rad, 1.0_rad * M_PI);
    mc::RotMatrix m(ang);

    EXPECT_NEAR(m.xx(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(),  1.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanInstantiateAndSetDataFromPhiThetaPsiHalfPi)
{
    mc::Angles ang(1.0_rad * M_PI_2, 1.0_rad * M_PI_2, 1.0_rad * M_PI_2);
    mc::RotMatrix m(ang);

    EXPECT_NEAR(m.xx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(),  0.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanInstantiateAndSetDataFromPhiThetaPsiQuarterPi)
{
    mc::Angles ang(1.0_rad * M_PI_4, 1.0_rad * M_PI_4, 1.0_rad * M_PI_4);
    mc::RotMatrix m(ang);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_rot_matrix.m
    EXPECT_NEAR(m.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m.xy(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m.xz(), -0.7071, 1.0e-3);
    EXPECT_NEAR(m.yx(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m.yy(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m.yz(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m.zx(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m.zy(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m.zz(),  0.5000, 1.0e-3);
}

TEST_F(TestRotMatrix, CanInstantiateAndSetDataFromRandomAngles)
{
    mc::Angles a1(-1.0_rad * M_PI_4,  1.0_rad * M_PI_4,  1.0_rad * M_PI_4);
    mc::Angles a2( 1.0_rad * M_PI_4, -1.0_rad * M_PI_4,  1.0_rad * M_PI_4);
    mc::Angles a3( 1.0_rad * M_PI_4,  1.0_rad * M_PI_4, -1.0_rad * M_PI_4);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_rot_matrix.m
    mc::RotMatrix m1(a1);
    EXPECT_NEAR(m1.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m1.xy(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m1.xz(), -0.7071, 1.0e-3);
    EXPECT_NEAR(m1.yx(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m1.yy(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m1.yz(), -0.5000, 1.0e-3);
    EXPECT_NEAR(m1.zx(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m1.zy(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m1.zz(),  0.5000, 1.0e-3);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_rot_matrix.m
    mc::RotMatrix m2(a2);
    EXPECT_NEAR(m2.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m2.xy(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m2.xz(),  0.7071, 1.0e-3);
    EXPECT_NEAR(m2.yx(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m2.yy(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m2.yz(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m2.zx(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m2.zy(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m2.zz(),  0.5000, 1.0e-3);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_rot_matrix.m
    mc::RotMatrix m3(a3);
    EXPECT_NEAR(m3.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m3.xy(), -0.5000, 1.0e-3);
    EXPECT_NEAR(m3.xz(), -0.7071, 1.0e-3);
    EXPECT_NEAR(m3.yx(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m3.yy(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m3.yz(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m3.zx(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m3.zy(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m3.zz(),  0.5000, 1.0e-3);
}

TEST_F(TestRotMatrix, CanInstantiateAndSetDataFromQuaternionAngleZeros)
{
    mc::Angles ang(0.0_rad, 0.0_rad, 0.0_rad);
    mc::Quaternion quat(ang);
    mc::RotMatrix m(quat);

    EXPECT_NEAR(m.xx(), 1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(), 1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(), 0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(), 1.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanInstantiateAndSetDataFromQuaternionPhiPi)
{
    mc::Angles ang(1.0_rad * M_PI, 0.0_rad, 0.0_rad);
    mc::Quaternion quat(ang);
    mc::RotMatrix m(quat);

    EXPECT_NEAR(m.xx(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(), -1.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanInstantiateAndSetDataFromQuaternionThetaPi)
{
    mc::Angles ang(0.0_rad, 1.0_rad * M_PI, 0.0_rad);
    mc::Quaternion quat(ang);
    mc::RotMatrix m(quat);

    EXPECT_NEAR(m.xx(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(), -1.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanInstantiateAndSetDataFromQuaternionPsiPi)
{
    mc::Angles ang(0.0_rad, 0.0_rad, 1.0_rad * M_PI);
    mc::Quaternion quat(ang);
    mc::RotMatrix m(quat);

    EXPECT_NEAR(m.xx(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(),  1.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanInstantiateAndSetDataFromQuaternionPhiThetaPsiHalfPi)
{
    mc::Angles ang(1.0_rad * M_PI_2, 1.0_rad * M_PI_2, 1.0_rad * M_PI_2);
    mc::Quaternion quat(ang);
    mc::RotMatrix m(quat);

    EXPECT_NEAR(m.xx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.xz(), -1.0, 1.0e-9);
    EXPECT_NEAR(m.yx(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.yy(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.yz(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zx(),  1.0, 1.0e-9);
    EXPECT_NEAR(m.zy(),  0.0, 1.0e-9);
    EXPECT_NEAR(m.zz(),  0.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanInstantiateAndSetDataFromQuaternionPhiThetaPsiQuarterPi)
{
    mc::Angles ang(1.0_rad * M_PI_4, 1.0_rad * M_PI_4, 1.0_rad * M_PI_4);
    mc::Quaternion quat(ang);
    mc::RotMatrix m(quat);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_rot_matrix.m
    EXPECT_NEAR(m.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m.xy(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m.xz(), -0.7071, 1.0e-3);
    EXPECT_NEAR(m.yx(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m.yy(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m.yz(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m.zx(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m.zy(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m.zz(),  0.5000, 1.0e-3);
}

TEST_F(TestRotMatrix, CanInstantiateAndSetDataFromQuaternionRandomAngle)
{
    mc::Angles a1(-1.0_rad * M_PI_4,  1.0_rad * M_PI_4,  1.0_rad * M_PI_4);
    mc::Angles a2( 1.0_rad * M_PI_4, -1.0_rad * M_PI_4,  1.0_rad * M_PI_4);
    mc::Angles a3( 1.0_rad * M_PI_4,  1.0_rad * M_PI_4, -1.0_rad * M_PI_4);

    mc::Quaternion q1(a1);
    mc::Quaternion q2(a2);
    mc::Quaternion q3(a3);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_rot_matrix.m
    mc::RotMatrix m1(q1);
    EXPECT_NEAR(m1.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m1.xy(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m1.xz(), -0.7071, 1.0e-3);
    EXPECT_NEAR(m1.yx(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m1.yy(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m1.yz(), -0.5000, 1.0e-3);
    EXPECT_NEAR(m1.zx(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m1.zy(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m1.zz(),  0.5000, 1.0e-3);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_rot_matrix.m
    mc::RotMatrix m2(q2);
    EXPECT_NEAR(m2.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m2.xy(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m2.xz(),  0.7071, 1.0e-3);
    EXPECT_NEAR(m2.yx(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m2.yy(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m2.yz(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m2.zx(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m2.zy(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m2.zz(),  0.5000, 1.0e-3);

    // expected values calculated with GNU Octave
    // tests/math/octave/test_rot_matrix.m
    mc::RotMatrix m3(q3);
    EXPECT_NEAR(m3.xx(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m3.xy(), -0.5000, 1.0e-3);
    EXPECT_NEAR(m3.xz(), -0.7071, 1.0e-3);
    EXPECT_NEAR(m3.yx(),  0.8536, 1.0e-3);
    EXPECT_NEAR(m3.yy(),  0.1464, 1.0e-3);
    EXPECT_NEAR(m3.yz(),  0.5000, 1.0e-3);
    EXPECT_NEAR(m3.zx(), -0.1464, 1.0e-3);
    EXPECT_NEAR(m3.zy(), -0.8536, 1.0e-3);
    EXPECT_NEAR(m3.zz(),  0.5000, 1.0e-3);
}

TEST_F(TestRotMatrix, CanGetAnglesZeros)
{
    mc::RotMatrix m(mc::Angles(0.0_rad, 0.0_rad, 0.0_rad));
    mc::Angles ang = m.getAngles();

    EXPECT_NEAR(ang.phi()(), 0.0, 1.0e-9);
    EXPECT_NEAR(ang.tht()(), 0.0, 1.0e-9);
    EXPECT_NEAR(ang.psi()(), 0.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanGetAnglesPhiPi)
{
    mc::RotMatrix m(mc::Angles(1.0_rad * M_PI, 0.0_rad, 0.0_rad));
    mc::Angles ang = m.getAngles();

    EXPECT_NEAR(ang.phi()(), M_PI, 1.0e-9);
    EXPECT_NEAR(ang.tht()(), 0.0, 1.0e-9);
    EXPECT_NEAR(ang.psi()(), 0.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanGetAnglesPsiPi)
{
    mc::RotMatrix m(mc::Angles(0.0_rad, 0.0_rad, 1.0_rad * M_PI));
    mc::Angles ang = m.getAngles();

    EXPECT_NEAR(ang.phi()(), 0.0, 1.0e-9);
    EXPECT_NEAR(ang.tht()(), 0.0, 1.0e-9);
    EXPECT_NEAR(ang.psi()(), M_PI, 1.0e-9);
}

TEST_F(TestRotMatrix, CanGetAnglesInGimbalLock)
{
    // singularity - gimbal lock
    mc::RotMatrix mas1(mc::Angles( 0.0_rad          , 1.0_rad * M_PI_2 , 0.0_rad          ));
    mc::RotMatrix mas2(mc::Angles( 1.0_rad * M_PI_4 , 1.0_rad * M_PI_2 , 0.0_rad          ));
    mc::RotMatrix mas3(mc::Angles( 1.0_rad * M_PI_2 , 1.0_rad * M_PI_2 , 0.0_rad          ));
    mc::RotMatrix mas4(mc::Angles( 1.0_rad * M_PI   , 1.0_rad * M_PI_2 , 0.0_rad          ));
    mc::RotMatrix mas5(mc::Angles( 0.0_rad          , 1.0_rad * M_PI_2 , 1.0_rad * M_PI_2 ));

    mc::Angles as1 = mas1.getAngles();
    mc::Angles as2 = mas2.getAngles();
    mc::Angles as3 = mas3.getAngles();
    mc::Angles as4 = mas4.getAngles();
    mc::Angles as5 = mas5.getAngles();

    EXPECT_NEAR(as1.phi()(),     0.0, 1.0e-9);
    EXPECT_NEAR(as1.tht()(),  M_PI_2, 1.0e-9);
    EXPECT_NEAR(as1.psi()(),     0.0, 1.0e-9);

    EXPECT_NEAR(as2.phi()(),  M_PI_4, 1.0e-9);
    EXPECT_NEAR(as2.tht()(),  M_PI_2, 1.0e-9);
    EXPECT_NEAR(as2.psi()(),     0.0, 1.0e-9);

    EXPECT_NEAR(as3.phi()(),  M_PI_2, 1.0e-9);
    EXPECT_NEAR(as3.tht()(),  M_PI_2, 1.0e-9);
    EXPECT_NEAR(as3.psi()(),     0.0, 1.0e-9);

    EXPECT_NEAR(as4.phi()(),    M_PI, 1.0e-9);
    EXPECT_NEAR(as4.tht()(),  M_PI_2, 1.0e-9);
    EXPECT_NEAR(as4.psi()(),     0.0, 1.0e-9);

    EXPECT_NEAR(as5.phi()(), -M_PI_2, 1.0e-9);
    EXPECT_NEAR(as5.tht()(),  M_PI_2, 1.0e-9);
    EXPECT_NEAR(as5.psi()(),     0.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanGetQuaternion)
{
    mc::RotMatrix m(mc::Quaternion(0.6, 0.0, 0.0, 0.8));
    mc::Quaternion q = m.getQuaternion();

    EXPECT_NEAR(q.e0(), 0.6, 1.0e-9);
    EXPECT_NEAR(q.ex(), 0.0, 1.0e-9);
    EXPECT_NEAR(q.ey(), 0.0, 1.0e-9);
    EXPECT_NEAR(q.ez(), 0.8, 1.0e-9);
}

TEST_F(TestRotMatrix, CanGetQuaternionWhichMatchesAngles)
{
    mc::RotMatrix m1(  1.0,  0.0,  0.0,
                       0.0,  1.0,  0.0,
                       0.0,  0.0,  1.0 );
    mc::RotMatrix m2( -1.0,  0.0,  0.0,
                       0.0, -1.0,  0.0,
                       0.0,  0.0,  1.0 );
    mc::RotMatrix m3( -1.0,  0.0,  0.0,
                       0.0,  1.0,  0.0,
                       0.0,  0.0, -1.0 );
    mc::RotMatrix m4(  1.0,  0.0,  0.0,
                       0.0, -1.0,  0.0,
                       0.0,  0.0, -1.0 );

    mc::Angles a1 = m1.getAngles();
    mc::Angles a2 = m2.getAngles();
    mc::Angles a3 = m3.getAngles();
    mc::Angles a4 = m4.getAngles();

    mc::Quaternion qa1(a1);
    mc::Quaternion qa2(a2);
    mc::Quaternion qa3(a3);
    mc::Quaternion qa4(a4);

    mc::Quaternion qm1 = m1.getQuaternion();
    mc::Quaternion qm2 = m2.getQuaternion();
    mc::Quaternion qm3 = m3.getQuaternion();
    mc::Quaternion qm4 = m4.getQuaternion();

    EXPECT_NEAR(qa1.e0(), qm1.e0(), 1.0e-9);
    EXPECT_NEAR(qa1.ex(), qm1.ex(), 1.0e-9);
    EXPECT_NEAR(qa1.ey(), qm1.ey(), 1.0e-9);
    EXPECT_NEAR(qa1.ez(), qm1.ez(), 1.0e-9);

    EXPECT_NEAR(qa2.e0(), qm2.e0(), 1.0e-9);
    EXPECT_NEAR(qa2.ex(), qm2.ex(), 1.0e-9);
    EXPECT_NEAR(qa2.ey(), qm2.ey(), 1.0e-9);
    EXPECT_NEAR(qa2.ez(), qm2.ez(), 1.0e-9);

    EXPECT_NEAR(qa3.e0(), qm3.e0(), 1.0e-9);
    EXPECT_NEAR(qa3.ex(), qm3.ex(), 1.0e-9);
    EXPECT_NEAR(qa3.ey(), qm3.ey(), 1.0e-9);
    EXPECT_NEAR(qa3.ez(), qm3.ez(), 1.0e-9);

    EXPECT_NEAR(qa4.e0(), qm4.e0(), 1.0e-9);
    EXPECT_NEAR(qa4.ex(), qm4.ex(), 1.0e-9);
    EXPECT_NEAR(qa4.ey(), qm4.ey(), 1.0e-9);
    EXPECT_NEAR(qa4.ez(), qm4.ez(), 1.0e-9);
}

TEST_F(TestRotMatrix, CanGetTransposed)
{
    std::vector<double> x
    {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    mc::RotMatrix m0;
    m0.setFromStdVector(x);

    mc::RotMatrix m1(m0);
    mc::RotMatrix mt = m1.getTransposed();

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
            EXPECT_DOUBLE_EQ(mt(r,c), m0(c,r)) << "Error at row " << r << " and col " << c;
        }
    }
}

TEST_F(TestRotMatrix, CanAdd)
{
    mc::RotMatrix m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::RotMatrix m2( 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0 );

    mc::RotMatrix m0 = m1 + m2;

    EXPECT_DOUBLE_EQ(m0.xx(),  2.0);
    EXPECT_DOUBLE_EQ(m0.xy(),  3.0);
    EXPECT_DOUBLE_EQ(m0.xz(),  4.0);
    EXPECT_DOUBLE_EQ(m0.yx(),  5.0);
    EXPECT_DOUBLE_EQ(m0.yy(),  6.0);
    EXPECT_DOUBLE_EQ(m0.yz(),  7.0);
    EXPECT_DOUBLE_EQ(m0.zx(),  8.0);
    EXPECT_DOUBLE_EQ(m0.zy(),  9.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 10.0);
}

TEST_F(TestRotMatrix, CanNegate)
{
    mc::RotMatrix m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::RotMatrix m0 = -m1;

    EXPECT_DOUBLE_EQ(m0.xx(), -1.0);
    EXPECT_DOUBLE_EQ(m0.xy(), -2.0);
    EXPECT_DOUBLE_EQ(m0.xz(), -3.0);
    EXPECT_DOUBLE_EQ(m0.yx(), -4.0);
    EXPECT_DOUBLE_EQ(m0.yy(), -5.0);
    EXPECT_DOUBLE_EQ(m0.yz(), -6.0);
    EXPECT_DOUBLE_EQ(m0.zx(), -7.0);
    EXPECT_DOUBLE_EQ(m0.zy(), -8.0);
    EXPECT_DOUBLE_EQ(m0.zz(), -9.0);
}

TEST_F(TestRotMatrix, CanSubtract)
{
    mc::RotMatrix m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::RotMatrix m2( 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0 );

    mc::RotMatrix m0 = m1 - m2;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 2.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 3.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 4.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 5.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 6.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 7.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 8.0);
}

TEST_F(TestRotMatrix, CanMultiplyByNumber)
{
    mc::RotMatrix m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::RotMatrix m0 = m1 * 0.5;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m0.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m0.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m0.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 4.5);
}

TEST_F(TestRotMatrix, CanMultiplyByMatrix)
{
    mc::RotMatrix m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::RotMatrix m2( 1.1, 2.2, 3.3,
                      4.4, 5.5, 6.6,
                      7.7, 8.8, 9.9 );

    mc::RotMatrix m0 = m1 * m2;

    EXPECT_NEAR(m0.xx(),  33.0, 1.0e-9);
    EXPECT_NEAR(m0.xy(),  39.6, 1.0e-9);
    EXPECT_NEAR(m0.xz(),  46.2, 1.0e-9);
    EXPECT_NEAR(m0.yx(),  72.6, 1.0e-9);
    EXPECT_NEAR(m0.yy(),  89.1, 1.0e-9);
    EXPECT_NEAR(m0.yz(), 105.6, 1.0e-9);
    EXPECT_NEAR(m0.zx(), 112.2, 1.0e-9);
    EXPECT_NEAR(m0.zy(), 138.6, 1.0e-9);
    EXPECT_NEAR(m0.zz(), 165.0, 1.0e-9);
}

template <typename T>
void RotMatrix_CanMultiplyByVector()
{
    mc::RotMatrix m1(  1.0,  0.0,  0.0,
                       0.0,  1.0,  0.0,
                       0.0,  0.0,  1.0 );

    mc::RotMatrix m2( -1.0,  0.0,  0.0,
                       0.0, -1.0,  0.0,
                       0.0,  0.0, -1.0 );

    mc::RotMatrix m3(  0.0,  1.0,  0.0,
                       1.0,  0.0,  0.0,
                       0.0,  0.0,  1.0 );

    mc::RotMatrix m4(  1.0,  0.0,  0.0,
                       0.0,  0.0, -1.0,
                       0.0, -1.0,  0.0 );

    mc::Vector3<T> v(T{1}, T{2}, T{3});

    mc::Vector3d v1 = static_cast<mc::Vector3d>(m1 * v);
    EXPECT_NEAR(v1.x(),  1.0, 1.0e-9);
    EXPECT_NEAR(v1.y(),  2.0, 1.0e-9);
    EXPECT_NEAR(v1.z(),  3.0, 1.0e-9);

    mc::Vector3d v2 = static_cast<mc::Vector3d>(m2 * v);
    EXPECT_NEAR(v2.x(), -1.0, 1.0e-9);
    EXPECT_NEAR(v2.y(), -2.0, 1.0e-9);
    EXPECT_NEAR(v2.z(), -3.0, 1.0e-9);

    mc::Vector3d v3 = static_cast<mc::Vector3d>(m3 * v);
    EXPECT_NEAR(v3.x(),  2.0, 1.0e-9);
    EXPECT_NEAR(v3.y(),  1.0, 1.0e-9);
    EXPECT_NEAR(v3.z(),  3.0, 1.0e-9);

    mc::Vector3d v4 = static_cast<mc::Vector3d>(m4 * v);
    EXPECT_NEAR(v4.x(),  1.0, 1.0e-9);
    EXPECT_NEAR(v4.y(), -3.0, 1.0e-9);
    EXPECT_NEAR(v4.z(), -2.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanMultiplyByVector)
{
    RotMatrix_CanMultiplyByVector<double>();
    RotMatrix_CanMultiplyByVector<units::length::meter_t>();
    RotMatrix_CanMultiplyByVector<units::velocity::meters_per_second_t>();
    RotMatrix_CanMultiplyByVector<units::acceleration::meters_per_second_squared_t>();
    RotMatrix_CanMultiplyByVector<units::angular_velocity::radians_per_second_t>();
    RotMatrix_CanMultiplyByVector<units::angular_velocity::degrees_per_second_t>();
    RotMatrix_CanMultiplyByVector<units::angular_acceleration::radians_per_second_squared_t>();
    RotMatrix_CanMultiplyByVector<units::angular_acceleration::degrees_per_second_squared_t>();
    RotMatrix_CanMultiplyByVector<units::force::newton_t>();
    RotMatrix_CanMultiplyByVector<units::torque::newton_meter_t>();
}

TEST_F(TestRotMatrix, CanMultiplyByVectorAngularVel)
{
    mc::RotMatrix m1( 1.0, 0.0, 0.0,
                      0.0, 1.0, 0.0,
                      0.0, 0.0, 1.0 );

    mc::Vector3_rad_per_s v(1.0_rad_per_s, 2.0_rad_per_s, 3.0_rad_per_s);

    mc::Vector3_rad_per_s v1 = m1 * v;
    EXPECT_NEAR(v1.x()(),  1.0, 1.0e-9);
    EXPECT_NEAR(v1.y()(),  2.0, 1.0e-9);
    EXPECT_NEAR(v1.z()(),  3.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanMultiplyByVectorAngularAcc)
{
    mc::RotMatrix m1( 1.0, 0.0, 0.0,
                      0.0, 1.0, 0.0,
                      0.0, 0.0, 1.0 );

    mc::Vector3_rad_per_s_sq v(1.0_rad_per_s_sq, 2.0_rad_per_s_sq, 3.0_rad_per_s_sq);

    mc::Vector3_rad_per_s_sq v1 = m1 * v;
    EXPECT_NEAR(v1.x()(),  1.0, 1.0e-9);
    EXPECT_NEAR(v1.y()(),  2.0, 1.0e-9);
    EXPECT_NEAR(v1.z()(),  3.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanMultiplyByVectorDimensionless)
{
    mc::RotMatrix m1( 1.0, 0.0, 0.0,
                      0.0, 1.0, 0.0,
                      0.0, 0.0, 1.0 );

    mc::RotMatrix m2( -1.0,  0.0,  0.0,
                       0.0, -1.0,  0.0,
                       0.0,  0.0, -1.0 );

    mc::RotMatrix m3( 0.0, 1.0, 0.0,
                      1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0 );

    mc::RotMatrix m4( 1.0,  0.0,  0.0,
                      0.0,  0.0, -1.0,
                      0.0, -1.0,  0.0 );

    mc::Vector3d v(1.0, 2.0, 3.0);

    mc::Vector3d v1 = m1 * v;
    EXPECT_NEAR(v1.x(),  1.0, 1.0e-9);
    EXPECT_NEAR(v1.y(),  2.0, 1.0e-9);
    EXPECT_NEAR(v1.z(),  3.0, 1.0e-9);

    mc::Vector3d v2 = m2 * v;
    EXPECT_NEAR(v2.x(), -1.0, 1.0e-9);
    EXPECT_NEAR(v2.y(), -2.0, 1.0e-9);
    EXPECT_NEAR(v2.z(), -3.0, 1.0e-9);

    mc::Vector3d v3 = m3 * v;
    EXPECT_NEAR(v3.x(),  2.0, 1.0e-9);
    EXPECT_NEAR(v3.y(),  1.0, 1.0e-9);
    EXPECT_NEAR(v3.z(),  3.0, 1.0e-9);

    mc::Vector3d v4 = m4 * v;
    EXPECT_NEAR(v4.x(),  1.0, 1.0e-9);
    EXPECT_NEAR(v4.y(), -3.0, 1.0e-9);
    EXPECT_NEAR(v4.z(), -2.0, 1.0e-9);
}

TEST_F(TestRotMatrix, CanDivideByNumber)
{
    mc::RotMatrix m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );
    mc::RotMatrix m0 = m1 / 2.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m0.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m0.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m0.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 4.5);
}

TEST_F(TestRotMatrix, CanUnaryAdd)
{
    mc::RotMatrix m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::RotMatrix m2( 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0 );

    m1 += m2;

    EXPECT_DOUBLE_EQ(m1.xx(),  2.0);
    EXPECT_DOUBLE_EQ(m1.xy(),  3.0);
    EXPECT_DOUBLE_EQ(m1.xz(),  4.0);
    EXPECT_DOUBLE_EQ(m1.yx(),  5.0);
    EXPECT_DOUBLE_EQ(m1.yy(),  6.0);
    EXPECT_DOUBLE_EQ(m1.yz(),  7.0);
    EXPECT_DOUBLE_EQ(m1.zx(),  8.0);
    EXPECT_DOUBLE_EQ(m1.zy(),  9.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 10.0);
}

TEST_F(TestRotMatrix, CanUnarySubtract)
{
    mc::RotMatrix m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    mc::RotMatrix m2( 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0 );

    m1 -= m2;

    EXPECT_DOUBLE_EQ(m1.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m1.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m1.xz(), 2.0);
    EXPECT_DOUBLE_EQ(m1.yx(), 3.0);
    EXPECT_DOUBLE_EQ(m1.yy(), 4.0);
    EXPECT_DOUBLE_EQ(m1.yz(), 5.0);
    EXPECT_DOUBLE_EQ(m1.zx(), 6.0);
    EXPECT_DOUBLE_EQ(m1.zy(), 7.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 8.0);
}

TEST_F(TestRotMatrix, CanUnaryMultiplyByNumber)
{
    mc::RotMatrix m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    m1 *= 0.5;

    EXPECT_DOUBLE_EQ(m1.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m1.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m1.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m1.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m1.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m1.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m1.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m1.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 4.5);
}

TEST_F(TestRotMatrix, CanUnaryDivideByNumber)
{
    mc::RotMatrix m1( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0 );

    m1 /= 2.0;

    EXPECT_DOUBLE_EQ(m1.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m1.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m1.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m1.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m1.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m1.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m1.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m1.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 4.5);
}
