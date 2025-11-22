set(MODULE_NAME mcutils-misc)

################################################################################

set(SOURCES
    StringUtils.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
