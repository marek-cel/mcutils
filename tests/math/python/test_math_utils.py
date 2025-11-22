from scipy.spatial.transform import Rotation as R
import numpy as np

################################################################################

def get_rotation_matrix(phi, tht, psi):
    rz = R.from_euler('z', psi, degrees=True)
    ry = R.from_euler('y', tht, degrees=True)
    rx = R.from_euler('x', phi, degrees=True)
    r = rz * ry * rx
    m = r.as_matrix()
    m = m.T
    return np.asarray(m)


def get_quaternion(phi, tht, psi):
    r = R.from_matrix(get_rotation_matrix(phi, tht, psi))
    return r.as_quat()