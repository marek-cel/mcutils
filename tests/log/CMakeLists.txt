set(MODULE_NAME tests-mcutils-log)

################################################################################

set(SOURCES
    TestLog.cpp
    TestStreamLogger.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
