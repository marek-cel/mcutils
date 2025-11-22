#!/usr/bin/env python3

################################################################################

import numpy as np

################################################################################

v0 = np.array([1.0, 2.0, 3.0, 4.0])

v0 = v0 / np.linalg.norm(v0)
print()
print(v0)
input("Press Eneter to continue")