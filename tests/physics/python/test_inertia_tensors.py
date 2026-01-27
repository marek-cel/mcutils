#!/usr/bin/env python3


import trimesh

mass = 1.0

mesh_sphere = trimesh.load("sphere_r_1.stl")
print(mesh_sphere.mass)
inertia_tensor_sphere = mesh_sphere.moment_inertia / mesh_sphere.mass
print(inertia_tensor_sphere)


# mesh_cylinder = trimesh.load("cylinder_r_1_h_1.stl")
# inertia_tensor_cylinder = mesh_cylinder.moment_inertia * mass
# print(inertia_tensor_cylinder)


# mesh_cube = trimesh.load("cube_1x1x1.stl")
# inertia_tensor_cube = mesh_cube.moment_inertia * mass
# print(inertia_tensor_cube)
