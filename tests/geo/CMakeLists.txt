set(MODULE_NAME tests-mcutils-geo)

################################################################################

set(SOURCES
    TestECEF.cpp
    TestEllipsoid.cpp
    TestMercator.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
