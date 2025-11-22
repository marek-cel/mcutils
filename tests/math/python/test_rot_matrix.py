#!/usr/bin/env python3

################################################################################

from test_math_utils import get_rotation_matrix

################################################################################

print()
print(get_rotation_matrix(45, 45, 45))

print()
print(get_rotation_matrix(-45, 45, 45))

print()
print(get_rotation_matrix(45, -45, 45))

print()
print(get_rotation_matrix(45, 45, -45))