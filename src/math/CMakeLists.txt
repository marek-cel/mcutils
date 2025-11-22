set(MODULE_NAME mcutils-math)

################################################################################

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
