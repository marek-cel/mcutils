set(MODULE_NAME tests-mcutils-data)

################################################################################

set(SOURCES
    TestConstDataRef.cpp
    TestDataPathUtils.cpp
    TestDataRef.cpp
    TestDataTree.cpp
    TestGroupNode.cpp
    TestNode.cpp
    TestValueNode.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
