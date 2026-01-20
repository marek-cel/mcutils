set(MODULE_NAME tests-mcutils-physics)

################################################################################

set(SOURCES
    TestPhysicsUtils.cpp
    TestUnitsUtils.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
