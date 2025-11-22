set(MODULE_NAME mcutils-log)

################################################################################

set(SOURCES
    Log.cpp
    StreamLogger.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
