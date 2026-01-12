set(MODULE_NAME tests-mcutils-units)

################################################################################

set(SOURCES
    TestUnits.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
