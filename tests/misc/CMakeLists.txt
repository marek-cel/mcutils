set(MODULE_NAME tests-mcutils-misc)

################################################################################

set(SOURCES
    TestCheck.cpp
    TestStringUtils.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
