set(MODULE_NAME mcutils-data)

################################################################################

set(HEADERS
    ConstDataRef.h
    DataPathUtils.h
    DataRef.h
    DataTree.h
    GroupNode.h
    Node.h
    ValueNode.h
)

set(SOURCES
    DataPathUtils.cpp
    DataTree.cpp
    GroupNode.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})

################################################################################

set_target_properties(${MODULE_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${MODULE_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/data
)
