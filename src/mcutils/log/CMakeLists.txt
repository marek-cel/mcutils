set(MODULE_NAME mcutils-log)

################################################################################

set(HEADERS
    ILogger.h
    Log.h
    LoggerBase.h
    StreamLogger.h
    SysLogger.h
    VerboseLevel.h
)

set(SOURCES
    Log.cpp
    StreamLogger.cpp
    SysLogger.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})

################################################################################

set_target_properties(${MODULE_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${MODULE_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/misc
)

