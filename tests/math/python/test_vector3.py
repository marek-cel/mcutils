#!/usr/bin/env python3

################################################################################

import numpy as np

################################################################################

v1 = np.array([1, 2, 3])
v2 = np.array([2, 3, 4])
print()
print(np.linalg.norm(v1))
print(np.linalg.norm(v2))
input("Press Eneter to continue")

################################################################################

v1 = v1 / np.linalg.norm(v1)
v2 = v2 / np.linalg.norm(v2)
print()
print(v1)
print(v2)
input("Press Eneter to continue")

################################################################################

v1 = np.array([1.0, 0.0, 0.0])
v2 = np.array([0.0, 1.0, 0.0])
v3 = np.array([0.0, 0.0, 1.0])
v4 = np.array([1.0, 2.0, 3.0])

v4_v1 = np.cross(v4, v1)
v4_v2 = np.cross(v4, v2)
v4_v3 = np.cross(v4, v3)
v2_v4 = np.cross(v2, v4)
v3_v4 = np.cross(v3, v4)

print()
print(v4_v1)
print(v4_v2)
print(v4_v3)
print(v2_v4)
print(v3_v4)
input("Press Eneter to continue")

################################################################################

v1 = np.array([1.0, 0.0, 0.0])
v2 = np.array([0.0, 1.0, 0.0])
v3 = np.array([0.0, 0.0, 1.0])
v4 = np.array([1.0, 2.0, 3.0])

v4_v1 = np.dot( v4, v1 )
v4_v2 = np.dot( v4, v2 )
v4_v3 = np.dot( v4, v3 )
v4_v4 = np.dot( v4, v4 )

print()
print(v4_v1)
print(v4_v2)
print(v4_v3)
print(v4_v4)

v1_v4 = np.dot( v1, v4 )
v2_v4 = np.dot( v2, v4 )
v3_v4 = np.dot( v3, v4 )
v4_v4 = np.dot( v4, v4 )

print()
print(v1_v4)
print(v2_v4)
print(v3_v4)
print(v4_v4)
input("Press Eneter to continue")

################################################################################

v1 = np.array([1.0, 2.0, 3.0])
v2 = np.array([4.0, 5.0, 6.0])

v1_v2 = np.dot( v1, v2 )
v2_v1 = np.dot( v2, v1 )

print()
print(v1_v2)
print(v2_v1)
input("Press Eneter to continue")