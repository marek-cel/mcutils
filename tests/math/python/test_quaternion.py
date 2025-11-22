#!/usr/bin/env python3

################################################################################

import numpy as np

from scipy.spatial.transform import Rotation as R

from test_math_utils import get_quaternion

################################################################################

r = R.from_quat([1.0, 2.0, 3.0, 4.0])
print()
print(r.as_quat())
input("Press Eneter to continue")

################################################################################

phi = 30; 
tht = 45;  
psi = 60; 
print()
print(get_quaternion(phi, tht, psi))
input("Press Eneter to continue")

################################################################################

r = R.from_rotvec(np.array([np.pi / 4, 0, 0]))
print()
print(r.as_quat())
input("Press Eneter to continue")

r = R.from_rotvec(np.array([0, np.pi / 4, 0]))
print()
print(r.as_quat())
input("Press Eneter to continue")

r = R.from_rotvec(np.array([0, 0, np.pi / 4]))
print()
print(r.as_quat())
input("Press Eneter to continue")

v = np.array([1, 1, 1])
v = v / np.linalg.norm(v)
r = R.from_rotvec(v * (np.pi / 4))
print()
print(r.as_quat())
input("Press Eneter to continue")

################################################################################

r = R.from_quat([1.0, 2.0, 3.0, 4.0])
print()
print(r.inv().as_quat())
input("Press Eneter to continue")