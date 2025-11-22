set(MODULE_NAME mcutils-data)

################################################################################

set(SOURCES
    DataPathUtils.cpp
    DataTree.cpp
    GroupNode.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
