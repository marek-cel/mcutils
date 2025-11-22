#include <gtest/gtest.h>

#include <mcutils/xml/XmlDoc.h>

#define TEMP_XML_FILE "temp.xml"

class TestXmlDoc : public ::testing::Test
{
protected:
    TestXmlDoc() {}
    virtual ~TestXmlDoc() {}
    void SetUp() override {}
    void TearDown() override
    {
        // remove temporary file temp.xml
        std::remove(TEMP_XML_FILE);
    }
};

TEST_F(TestXmlDoc, CanConstruct)
{
    mc::XmlDoc* doc = nullptr;
    EXPECT_NO_THROW(doc = new mc::XmlDoc());
    delete doc;
}

TEST_F(TestXmlDoc, CanDestruct)
{
    mc::XmlDoc* doc = new mc::XmlDoc();
    EXPECT_NO_THROW(delete doc);
}

TEST_F(TestXmlDoc, CanInstantiate)
{
    mc::XmlDoc doc;
}

TEST_F(TestXmlDoc, CanInstantiateAndOpenFile)
{
    mc::XmlDoc doc("../tests/xml/data/test_xml_sample_data.xml");
    EXPECT_TRUE(doc.isOpen());
}

TEST_F(TestXmlDoc, CanCreateRootNode)
{
    mc::XmlDoc doc;

    mc::XmlNode rootNode = doc.createRootNode("test_root");
    EXPECT_TRUE(rootNode.isValid());
    EXPECT_STREQ(rootNode.getName().c_str(), "test_root");
}

TEST_F(TestXmlDoc, CanGetRootNode)
{
    mc::XmlDoc doc("../tests/xml/data/test_xml_sample_data.xml");
    EXPECT_TRUE(doc.isOpen());

    mc::XmlNode rootNode = doc.getRootNode();
    EXPECT_TRUE(rootNode.isValid());
    EXPECT_STREQ(rootNode.getName().c_str(), "test_root");
}

TEST_F(TestXmlDoc, CanGetPath)
{
    mc::XmlDoc doc("../tests/xml/data/test_xml_sample_data.xml");
    EXPECT_TRUE(doc.isOpen());

    std::string file = doc.getPath().string();
    EXPECT_STREQ(file.c_str(), "../tests/xml/data/test_xml_sample_data.xml");
}

TEST_F(TestXmlDoc, CanOpenFile)
{
    mc::XmlDoc doc;
    EXPECT_NO_THROW(doc.openFile("../tests/xml/data/test_xml_sample_data.xml"));
    EXPECT_TRUE(doc.isOpen());
}

TEST_F(TestXmlDoc, CanOpenFileEmpty)
{
    mc::XmlDoc doc;
    EXPECT_NO_THROW(doc.openFile("../tests/xml/data/test_xml_sample_data_empty.xml"));
    EXPECT_FALSE(doc.isOpen());
}

TEST_F(TestXmlDoc, CanOpenFileNotExisting)
{
    mc::XmlDoc doc;

    EXPECT_NO_THROW(doc.openFile("../tests/xml/data/test_xml_sample_data_not_existing.xml"));
    EXPECT_FALSE(doc.isOpen());
}

TEST_F(TestXmlDoc, CanCloseFile)
{
    mc::XmlDoc doc("../tests/xml/data/test_xml_sample_data.xml");
    EXPECT_TRUE(doc.isOpen());
    EXPECT_NO_THROW(doc.closeFile());
    EXPECT_FALSE(doc.isOpen());
}

TEST_F(TestXmlDoc, CanSaveFile)
{
    mc::XmlDoc doc;

    mc::XmlNode rootNode = doc.createRootNode("test_root");
    mc::XmlNode childNode = rootNode.addChildElement("test_child");
    mc::XmlNode textNode = childNode.addText("lorem ipsum");

    EXPECT_TRUE(mc::Result::Success == childNode.addAttribute("test_attr", "test_value"));

    EXPECT_TRUE(rootNode.isValid());
    EXPECT_STREQ(rootNode.getName().c_str(), "test_root");

    EXPECT_TRUE(childNode.isValid());
    EXPECT_TRUE(childNode.isElement());
    EXPECT_STREQ(childNode.getName().c_str(), "test_child");

    EXPECT_TRUE(textNode.isValid());
    EXPECT_TRUE(textNode.isText());
    EXPECT_STREQ(textNode.getText().c_str(), "lorem ipsum");

    EXPECT_TRUE(mc::Result::Success == doc.saveFile(TEMP_XML_FILE));
    EXPECT_TRUE(doc.isOpen());

    doc.closeFile();

    mc::XmlDoc doc2(TEMP_XML_FILE);
    EXPECT_TRUE(doc2.isOpen());
    mc::XmlNode rootNode2 = doc2.getRootNode();
    EXPECT_TRUE(rootNode2.isValid());
    EXPECT_STREQ(rootNode2.getName().c_str(), "test_root");
    mc::XmlNode childNode2 = rootNode2.getFirstChildElement("test_child");
    mc::XmlNode textNode2 = childNode2.getFirstChild();
    EXPECT_TRUE(childNode2.isValid());
    EXPECT_TRUE(childNode2.isElement());
    EXPECT_STREQ(childNode2.getName().c_str(), "test_child");
    EXPECT_TRUE(childNode2.hasAttribute("test_attr"));
    EXPECT_STREQ(childNode2.getAttribute("test_attr").c_str(), "test_value");
    EXPECT_TRUE(textNode2.isValid());
    EXPECT_TRUE(textNode2.isText());
    EXPECT_STREQ(textNode2.getText().c_str(), "lorem ipsum");
}

TEST_F(TestXmlDoc, CanSaveEmptyFile)
{
    mc::XmlDoc doc;

    EXPECT_FALSE(mc::Result::Success == doc.saveFile(TEMP_XML_FILE));
    EXPECT_FALSE(doc.isOpen());
    doc.closeFile();

    mc::XmlDoc doc2(TEMP_XML_FILE);
    EXPECT_FALSE(doc2.isOpen());
}
