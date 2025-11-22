set(MODULE_NAME mcutils-geo)

################################################################################

set(HEADERS
    Ellipsoid.h
    Geo.h
    Mars2015.h
    Mercator.h
    WGS84.h
)

set(SOURCES
    ECEF.cpp
    Ellipsoid.cpp
    Mercator.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})

################################################################################

set_target_properties(${MODULE_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${MODULE_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/geo
)
