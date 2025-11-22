set(TARGET_NAME tests-mcutils)

################################################################################

find_package(GTest REQUIRED)

################################################################################

include_directories(.)

################################################################################

add_subdirectory(geo)
add_subdirectory(math)
add_subdirectory(misc)
add_subdirectory(time)
add_subdirectory(physics)
add_subdirectory(xml)

################################################################################

set(SOURCES
    main.cpp
    CsvFileReader.cpp
    XcosBinFileReader.cpp
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS
    mcutils
    gtest
    gtest_main
    ${LIBXML2_LIBRARIES}
)

if (UNIX)
    set(LIBS ${LIBS} gcov)
elseif(WIN32)
    set(LIBS ${LIBS} ws2_32)
endif()

target_link_libraries(${TARGET_NAME}
    $<TARGET_OBJECTS:tests-mcutils-geo>
    $<TARGET_OBJECTS:tests-mcutils-math>
    $<TARGET_OBJECTS:tests-mcutils-misc>
    $<TARGET_OBJECTS:tests-mcutils-physics>
    $<TARGET_OBJECTS:tests-mcutils-time>
    $<TARGET_OBJECTS:tests-mcutils-xml>
    ${LIBS}
)

################################################################################

set_target_properties(${TARGET_NAME} PROPERTIES
    EXCLUDE_FROM_ALL True
)

################################################################################

gtest_discover_tests(${TARGET_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
