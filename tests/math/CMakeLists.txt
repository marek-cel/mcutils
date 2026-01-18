set(MODULE_NAME tests-mcutils-math)

################################################################################

set(SOURCES
    TestAngles.cpp
    TestDegMinSec.cpp
    TestEulerRect.cpp
    TestGaussJordan.cpp
    TestMathUtils.cpp
    TestMatrix3x3.cpp
    TestMatrix3x3WithUnits.cpp
    TestMatrixMxN.cpp
    TestMatrixMxNWithUnits.cpp
    TestMatrixNxN.cpp
    TestMatrixNxNWithUnits.cpp
    TestQuaternion.cpp
    TestRotMatrix.cpp
    TestRungeKutta4.cpp
    TestSegPlaneIsect.cpp
    TestTable.cpp
    TestTable2.cpp
    TestVector3.cpp
    TestVector3WithUnits.cpp
    TestVectorN.cpp
    TestVectorNWithUnits.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
