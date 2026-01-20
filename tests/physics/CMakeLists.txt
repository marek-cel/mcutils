set(MODULE_NAME tests-mcutils-physics)

################################################################################

set(SOURCES
    TestFirstOrderInertia.cpp
    TestUnitsUtils.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
