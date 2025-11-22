#!/usr/bin/env python3

################################################################################

import sympy

################################################################################

m01 = sympy.Matrix([
    [1, 2],
    [2, 4],
    [5, 6]
])

m02 = sympy.Matrix([
    [1, 2, 3],
    [4, 5, 6]
])

print((m01 * m02).tolist())
input("Press Enter to continue")

################################################################################

v3 = sympy.Matrix([1, 2, 3])
m3 = sympy.Matrix([
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
])

print((m3 * m3).tolist())
print((m3 * v3).tolist())
input("Press Enter to continue")

################################################################################

v4 = sympy.Matrix([1, 2, 3, 4])
m4 = sympy.Matrix([
    [1, 2, 3, 4],
    [5, 6, 7, 8],
    [9, 10, 11, 12],
    [13, 14, 15, 16]
])

print((m4 * v4).tolist())
input("Press Enter to continue")

################################################################################

v6 = sympy.Matrix(6, 1, lambda m, n : m + 1)
m6 = sympy.Matrix(6, 6, lambda m, n : m*6 + n + 1)

print((m6 * v6).tolist())
input("Press Enter to continue")