set(MODULE_NAME tests-mcutils-xml)

################################################################################

set(SOURCES
    TestXmlDoc.cpp
    TestXmlNode.cpp
    TestXmlUtils.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
