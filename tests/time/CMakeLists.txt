set(MODULE_NAME tests-mcutils-time)

################################################################################

set(SOURCES
    TestClockTime.cpp
    TestISO8601.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
