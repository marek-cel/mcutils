set(MODULE_NAME mcutils-xml)

################################################################################

set(SOURCES
    XmlDoc.cpp
    XmlNode.cpp
    XmlUtils.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
