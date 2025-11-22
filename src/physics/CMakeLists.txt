set(MODULE_NAME mcutils-physics)

################################################################################

set(SOURCES
    UnitsUtils.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})