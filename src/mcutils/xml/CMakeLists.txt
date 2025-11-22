set(MODULE_NAME mcutils-xml)

################################################################################

set(HEADERS
    XmlDoc.h
    XmlNode.h
    XmlUtils.h
)

set(SOURCES
    XmlDoc.cpp
    XmlNode.cpp
    XmlUtils.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})

################################################################################

set_target_properties(${MODULE_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${MODULE_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/xml
)

