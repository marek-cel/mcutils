set(MODULE_NAME mcutils-geo)

################################################################################

set(SOURCES
    ECEF.cpp
    Ellipsoid.cpp
    Mercator.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
