#include <gtest/gtest.h>

#include <mcutils/xml/XmlNode.h>
#include <mcutils/xml/XmlDoc.h>
#include <mcutils/xml/XmlUtils.h>

class TestXmlUtils : public ::testing::Test
{
protected:
    TestXmlUtils() {}
    virtual ~TestXmlUtils() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestXmlUtils, CanReadDouble)
{
    std::string file = "../tests/xml/data/test_xml_sample_data_values.xml";
    mc::XmlDoc doc(file.c_str());
    mc::XmlNode root = doc.getRootNode();
    mc::XmlNode node = root.getFirstChildElement("test_double");

    double result = mc::readDouble(node);

    EXPECT_DOUBLE_EQ(result, 3.14);
}

TEST_F(TestXmlUtils, CanReadInt)
{
    std::string file = "../tests/xml/data/test_xml_sample_data_values.xml";
    mc::XmlDoc doc(file.c_str());
    mc::XmlNode root = doc.getRootNode();
    mc::XmlNode node = root.getFirstChildElement("test_int");

    int result = mc::readInt(node);

    EXPECT_EQ(result, 42);
}

TEST_F(TestXmlUtils, CanReadLength)
{
    std::string file = "../tests/xml/data/test_xml_sample_data_values.xml";
    mc::XmlDoc doc(file.c_str());
    mc::XmlNode root = doc.getRootNode();
    mc::XmlNode node    = root.getFirstChildElement("test_length");
    mc::XmlNode node_m  = root.getFirstChildElement("test_length_m");
    mc::XmlNode node_cm = root.getFirstChildElement("test_length_cm");
    mc::XmlNode node_mm = root.getFirstChildElement("test_length_mm");
    mc::XmlNode node_ft = root.getFirstChildElement("test_length_ft");
    mc::XmlNode node_in = root.getFirstChildElement("test_length_in");

    units::length::meter_t result    = mc::readLength(node);
    units::length::meter_t result_m  = mc::readLength(node_m);
    units::length::meter_t result_cm = mc::readLength(node_cm);
    units::length::meter_t result_mm = mc::readLength(node_mm);
    units::length::meter_t result_ft = mc::readLength(node_ft);
    units::length::meter_t result_in = mc::readLength(node_in);

    EXPECT_DOUBLE_EQ( result()    , 1.0    );
    EXPECT_DOUBLE_EQ( result_m()  , 1.0    );
    EXPECT_DOUBLE_EQ( result_cm() , 0.01   );
    EXPECT_DOUBLE_EQ( result_mm() , 0.001  );
    EXPECT_DOUBLE_EQ( result_ft() , 0.3048 );
    EXPECT_DOUBLE_EQ( result_in() , 0.0254 );
}

TEST_F(TestXmlUtils, CanReadAngle)
{
    std::string file = "../tests/xml/data/test_xml_sample_data_values.xml";
    mc::XmlDoc doc(file.c_str());
    mc::XmlNode root = doc.getRootNode();
    mc::XmlNode node      = root.getFirstChildElement("test_angle");
    mc::XmlNode node_rad  = root.getFirstChildElement("test_angle_rad");
    mc::XmlNode node_deg  = root.getFirstChildElement("test_angle_deg");

    units::angle::radian_t result     = mc::readAngle(node);
    units::angle::radian_t result_rad = mc::readAngle(node_rad);
    units::angle::radian_t result_deg = mc::readAngle(node_deg);

    EXPECT_DOUBLE_EQ( result()      , 1.0          );
    EXPECT_DOUBLE_EQ( result_rad()  , 1.0          );
    EXPECT_DOUBLE_EQ( result_deg()  , M_PI / 180.0 );
}

TEST_F(TestXmlUtils, CanReadVelocity)
{
    std::string file = "../tests/xml/data/test_xml_sample_data_values.xml";
    mc::XmlDoc doc(file.c_str());
    mc::XmlNode root = doc.getRootNode();
    mc::XmlNode node     = root.getFirstChildElement("test_vel");
    mc::XmlNode node_mps = root.getFirstChildElement("test_vel_mps");
    mc::XmlNode node_fps = root.getFirstChildElement("test_vel_fps");
    mc::XmlNode node_kph = root.getFirstChildElement("test_vel_kph");
    mc::XmlNode node_mph = root.getFirstChildElement("test_vel_mph");
    mc::XmlNode node_kts = root.getFirstChildElement("test_vel_kts");
    mc::XmlNode node_fpm = root.getFirstChildElement("test_vel_fpm");

    units::velocity::meters_per_second_t result     = mc::readVelocity(node);
    units::velocity::meters_per_second_t result_mps = mc::readVelocity(node_mps);
    units::velocity::meters_per_second_t result_fps = mc::readVelocity(node_fps);
    units::velocity::meters_per_second_t result_kph = mc::readVelocity(node_kph);
    units::velocity::meters_per_second_t result_mph = mc::readVelocity(node_mph);
    units::velocity::meters_per_second_t result_kts = mc::readVelocity(node_kts);
    units::velocity::meters_per_second_t result_fpm = mc::readVelocity(node_fpm);

    EXPECT_NEAR( result()     , 1.0       , 1.0e-5 );
    EXPECT_NEAR( result_mps() , 1.0       , 1.0e-5 );
    EXPECT_NEAR( result_fps() , 0.3048    , 1.0e-5 );
    EXPECT_NEAR( result_kph() , 0.2777778 , 1.0e-5 );
    EXPECT_NEAR( result_mph() , 0.44704   , 1.0e-5 );
    EXPECT_NEAR( result_kts() , 0.5144444 , 1.0e-5 );
    EXPECT_NEAR( result_fpm() , 0.00508   , 1.0e-5 );

}

TEST_F(TestXmlUtils, CanReadMass)
{
    std::string file = "../tests/xml/data/test_xml_sample_data_values.xml";
    mc::XmlDoc doc(file.c_str());
    mc::XmlNode root = doc.getRootNode();
    mc::XmlNode node      = root.getFirstChildElement("test_mass");
    mc::XmlNode node_kg   = root.getFirstChildElement("test_mass_kg");
    mc::XmlNode node_g    = root.getFirstChildElement("test_mass_g");
    mc::XmlNode node_lb   = root.getFirstChildElement("test_mass_lb");
    mc::XmlNode node_slug = root.getFirstChildElement("test_mass_slug");
    mc::XmlNode node_t    = root.getFirstChildElement("test_mass_t");

    units::mass::kilogram_t result      = mc::readMass(node);
    units::mass::kilogram_t result_kg   = mc::readMass(node_kg);
    units::mass::kilogram_t result_g    = mc::readMass(node_g);
    units::mass::kilogram_t result_lb   = mc::readMass(node_lb);
    units::mass::kilogram_t result_slug = mc::readMass(node_slug);
    units::mass::kilogram_t result_t    = mc::readMass(node_t);

    EXPECT_DOUBLE_EQ( result()      , 1.0        );
    EXPECT_DOUBLE_EQ( result_kg()   , 1.0        );
    EXPECT_DOUBLE_EQ( result_g()    , 0.001      );
    EXPECT_DOUBLE_EQ( result_lb()   , 0.45359237 );
    EXPECT_DOUBLE_EQ( result_slug() , 14.5939029 );
    EXPECT_DOUBLE_EQ( result_t()    , 1000.0     );
}

TEST_F(TestXmlUtils, CanReadAngles)
{
    std::string file = "../tests/xml/data/test_xml_sample_data_values.xml";
    mc::XmlDoc doc(file.c_str());
    mc::XmlNode root = doc.getRootNode();
    mc::XmlNode node     = root.getFirstChildElement("test_angles");
    mc::XmlNode node_rad = root.getFirstChildElement("test_angles_rad");
    mc::XmlNode node_deg = root.getFirstChildElement("test_angles_deg");

    mc::Angles result     = mc::readAngles(node);
    mc::Angles result_rad = mc::readAngles(node_rad);
    mc::Angles result_deg = mc::readAngles(node_deg);

    EXPECT_DOUBLE_EQ(result.phi()(), 1.0);
    EXPECT_DOUBLE_EQ(result.tht()(), 2.0);
    EXPECT_DOUBLE_EQ(result.psi()(), 3.0);

    EXPECT_DOUBLE_EQ(result_rad.phi()(), 1.0);
    EXPECT_DOUBLE_EQ(result_rad.tht()(), 2.0);
    EXPECT_DOUBLE_EQ(result_rad.psi()(), 3.0);

    EXPECT_DOUBLE_EQ(result_deg.phi()(), 1.0 * M_PI / 180.0);
    EXPECT_DOUBLE_EQ(result_deg.tht()(), 2.0 * M_PI / 180.0);
    EXPECT_DOUBLE_EQ(result_deg.psi()(), 3.0 * M_PI / 180.0);
}

// TEST_F(TestXmlUtils, CanReadVector3d)
// {
//     std::string file = "../tests/xml/data/test_xml_sample_data_values.xml";
//     mc::XmlDoc doc(file.c_str());
//     mc::XmlNode root = doc.getRootNode();
//     mc::XmlNode node = root.getFirstChildElement("test_vector3d");

//     mc::Vector3d result = mc::readVector3d(node);

//     EXPECT_DOUBLE_EQ(result.x(), 1.0);
//     EXPECT_DOUBLE_EQ(result.y(), 2.0);
//     EXPECT_DOUBLE_EQ(result.z(), 3.0);
// }

// TEST_F(TestXmlUtils, CanReadVector3_m)
// {
//     std::string file = "../tests/xml/data/test_xml_sample_data_values.xml";
//     mc::XmlDoc doc(file.c_str());
//     mc::XmlNode root = doc.getRootNode();
//     mc::XmlNode node    = root.getFirstChildElement("test_length_vector3");
//     mc::XmlNode node_m  = root.getFirstChildElement("test_length_vector3_m");
//     mc::XmlNode node_cm = root.getFirstChildElement("test_length_vector3_cm");
//     mc::XmlNode node_mm = root.getFirstChildElement("test_length_vector3_mm");
//     mc::XmlNode node_ft = root.getFirstChildElement("test_length_vector3_ft");
//     mc::XmlNode node_in = root.getFirstChildElement("test_length_vector3_in");

//     mc::Vector3_m result    = mc::readVector3_m(node);
//     mc::Vector3_m result_m  = mc::readVector3_m(node_m);
//     mc::Vector3_m result_cm = mc::readVector3_m(node_cm);
//     mc::Vector3_m result_mm = mc::readVector3_m(node_mm);
//     mc::Vector3_m result_ft = mc::readVector3_m(node_ft);
//     mc::Vector3_m result_in = mc::readVector3_m(node_in);

//     EXPECT_DOUBLE_EQ(result.x()(), 1.0);
//     EXPECT_DOUBLE_EQ(result.y()(), 2.0);
//     EXPECT_DOUBLE_EQ(result.z()(), 3.0);

//     EXPECT_DOUBLE_EQ(result_m.x()(), 1.0);
//     EXPECT_DOUBLE_EQ(result_m.y()(), 2.0);
//     EXPECT_DOUBLE_EQ(result_m.z()(), 3.0);

//     EXPECT_DOUBLE_EQ(result_cm.x()(), 0.01);
//     EXPECT_DOUBLE_EQ(result_cm.y()(), 0.02);
//     EXPECT_DOUBLE_EQ(result_cm.z()(), 0.03);

//     EXPECT_DOUBLE_EQ(result_mm.x()(), 0.001);
//     EXPECT_DOUBLE_EQ(result_mm.y()(), 0.002);
//     EXPECT_DOUBLE_EQ(result_mm.z()(), 0.003);

//     EXPECT_DOUBLE_EQ(result_ft.x()(), 0.3048);
//     EXPECT_DOUBLE_EQ(result_ft.y()(), 0.6096);
//     EXPECT_DOUBLE_EQ(result_ft.z()(), 0.9144);

//     EXPECT_DOUBLE_EQ(result_in.x()(), 0.0254);
//     EXPECT_DOUBLE_EQ(result_in.y()(), 0.0508);
//     EXPECT_DOUBLE_EQ(result_in.z()(), 0.0762);
// }

