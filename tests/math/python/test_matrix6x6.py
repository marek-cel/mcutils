#!/usr/bin/env python3

################################################################################

import numpy as np
import sympy

################################################################################

v1 = sympy.Matrix(6, 1, lambda m, n : m + 1)
m1 = sympy.Matrix(6, 6, lambda m, n : m*6 + n + 1)
m2 = sympy.Matrix(np.flipud(np.asarray(m1)))

# print(np.array(m1.tolist()))
# print(np.array(m2.tolist()))

print()
print(np.array(m1.transpose().tolist()))

print()
print(np.array((m1 * m2).tolist()))

print()
print(np.array((m1 * v1).tolist()))