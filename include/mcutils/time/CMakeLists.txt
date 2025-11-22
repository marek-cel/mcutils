set(MODULE_NAME mcutils-time)

################################################################################

set(HEADERS
    ClockTime.h
    DateTime.h
    ISO8601.h
    Timer.h
)

################################################################################

add_library(${MODULE_NAME} INTERFACE)

################################################################################

set_target_properties(${MODULE_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${MODULE_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/time
)
