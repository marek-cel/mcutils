# mcutils

**mcutils** is a modern C++ utilities library providing a collection of reusable components for scientific, engineering, and general-purpose applications. The library is modular, well-documented, and designed for performance and ease of use.

## Features

- **Geodetic computations**: ECEF transformations, ellipsoid/datum definitions (WGS84, Mars2015), map projections (Mercator), and geodetic conversions.
- **Math utilities**: Vectors, matrices, quaternions, rotation matrices, numerical integration (Euler, Runge-Kutta), interpolation tables, statistical functions, and angle/coordinate representations.
- **Physics utilities**: First-order inertia, dynamic system models, physical constants, and unit conversions.
- **Logging**: Console and file logging, configurable verbosity, stream-based and custom logger implementations.
- **Time utilities**: Date/time structures, ISO-8601 formatting/parsing, high-resolution timers.
- **XML utilities**: XML document/node manipulation, reading/writing structured data, and helper functions.
- **Miscellaneous**: String manipulation, input validation, and helper functions for common programming tasks.

## Test Coverage

mcutils is developed with a strong focus on reliability and correctness. The project maintains high unit test coverage across all modules.

## Getting Started

### Prerequisites

- C++20 or newer compiler
- [CMake](https://cmake.org/) 3.22+
- [GoogleTest](https://github.com/google/googletest) (for tests)
- [nholthaus/units](https://github.com/nholthaus/units) (included via CMake)
- [libxml2](http://xmlsoft.org/)
- [PROJ](https://proj.org/)

### Building

```sh
git clone https://github.com/marek-cel/mcutils.git
cd mcutils
mkdir build && cd build
cmake ..