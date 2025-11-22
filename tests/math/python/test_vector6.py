#!/usr/bin/env python3

################################################################################

import numpy as np

################################################################################

v0 = np.array([1.0, 2.0, 3.0, 4.0, 5.0, 6.0])
v1 = np.array([2.0, 3.0, 4.0, 5.0, 6.0, 7.0])

v0 = v0 / np.linalg.norm(v0)
v1 = v1 / np.linalg.norm(v1)
print()
print(v0)
print(v1)
input("Press Eneter to continue")