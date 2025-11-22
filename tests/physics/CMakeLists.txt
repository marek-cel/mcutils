set(MODULE_NAME tests-mcutils-physics)

################################################################################

set(SOURCES
    TestInertia.cpp
    TestUnitsUtils.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
