set(MODULE_NAME tests-mcutils-physics)

################################################################################

set(SOURCES
    TestInsertiaTensors.cpp
    TestPhysicsUtils.cpp
    TestUnitsUtils.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
