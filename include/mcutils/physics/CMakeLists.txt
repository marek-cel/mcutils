set(MODULE_NAME mcutils-physics)

################################################################################

set(HEADERS
    Inertia.h
    UnitsUtils.h
)

set(SOURCES
    UnitsUtils.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})

################################################################################

set_target_properties(${MODULE_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${MODULE_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/physics
)
