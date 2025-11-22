set(TARGET_NAME tests-mcutils)

################################################################################

# find_package(GTest REQUIRED)

# if(WIN32)
#     if (TARGET GTest::gtest)
#         message(STATUS "GTest imported target found: GTest::gtest")
#     else()
#         message(WARNING "GTest imported target NOT found; check installation")
#     endif()

#     if (TARGET GTest::gtest)
#         get_target_property(_gtest_includes GTest::gtest INTERFACE_INCLUDE_DIRECTORIES)
#         if (_gtest_includes)
#             message(STATUS "Adding GTest include directories: ${_gtest_includes}")
#             include_directories(${_gtest_includes})
#         endif()
#     endif()
# endif()

################################################################################

include_directories(.)

################################################################################

add_subdirectory(data)
add_subdirectory(geo)
add_subdirectory(log)
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
    GTest::gtest
    GTest::gtest_main
    ${Iconv_LIBRARIES}
    ${LIBXML2_LIBRARIES}
    PROJ::proj
)

if (UNIX)
    set(LIBS ${LIBS} gcov)
elseif(WIN32)
    set(LIBS ${LIBS} ws2_32)
endif()

target_link_libraries(${TARGET_NAME}
    $<TARGET_OBJECTS:tests-mcutils-data>
    $<TARGET_OBJECTS:tests-mcutils-geo>
    $<TARGET_OBJECTS:tests-mcutils-log>
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
