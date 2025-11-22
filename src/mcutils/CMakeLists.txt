set(TARGET_NAME ${PROJECT_NAME})

################################################################################

if(WIN32)
    if(BUILD_SHARED_LIBS)
        add_definitions(-DMCUTILS_DLL_EXPORTS)
    endif()
endif()

################################################################################

add_subdirectory(geo)
add_subdirectory(math)
add_subdirectory(misc)
add_subdirectory(physics)
add_subdirectory(time)
add_subdirectory(xml)

################################################################################

set(HEADERS
    doxygen.h
    extra_units.h
    mcutils_api.h
    Result.h
)

################################################################################

add_library(${TARGET_NAME} ${SOURCES}
    $<TARGET_OBJECTS:mcutils-geo>
    $<TARGET_OBJECTS:mcutils-math>
    $<TARGET_OBJECTS:mcutils-misc>
    $<TARGET_OBJECTS:mcutils-physics>
    $<TARGET_OBJECTS:mcutils-xml>
)

################################################################################

set_target_properties(${TARGET_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION_STRING}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils
)

################################################################################

if(WIN32)
    set(LIBS ${LIBXML2_LIBRARIES})
endif()

target_link_libraries(${TARGET_NAME} ${LIBS})
