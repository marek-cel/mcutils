set(MODULE_NAME mcutils-math)

################################################################################

set(HEADERS
    Angles.h
    DegMinSec.h
    EulerRect.h
    GaussJordan.h
    MathUtils.h
    Matrix.h
    Matrix3x3.h
    MatrixMxN.h
    MatrixNxN.h
    RotMatrix.h
    RungeKutta4.h
    SegPlaneIsect.h
    StatsUtils.h
    Table.h
    Table2.h
    Vector.h
    Vector3.h
    VectorN.h
)

set(SOURCES
    Angles.cpp
    DegMinSec.cpp
    Matrix.cpp
    Quaternion.cpp
    RotMatrix.cpp
    Vector.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})

################################################################################

set_target_properties(${MODULE_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${MODULE_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mcutils/math
)

