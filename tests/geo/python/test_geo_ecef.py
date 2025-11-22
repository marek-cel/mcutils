#!/usr/bin/env python3

################################################################################

import pyproj

################################################################################

t_geo2ecef = pyproj.Transformer.from_crs(
    {"proj":'latlong', "ellps":'WGS84', "datum":'WGS84'},
    {"proj":'geocent', "ellps":'WGS84', "datum":'WGS84'},
    )

################################################################################

lat =  0.0
lon = 30.0
alt =  0.0

x, y, z = t_geo2ecef.transform(lon, lat, alt, radians=False)
print(x, y, z)

################################################################################

lat =  0.0
lon = 45.0
alt =  0.0

x, y, z = t_geo2ecef.transform(lon, lat, alt, radians=False)
print(x, y, z)

################################################################################

lat =  0.0
lon = 60.0
alt =  0.0

x, y, z = t_geo2ecef.transform(lon, lat, alt, radians=False)
print(x, y, z)

################################################################################

lat =  45.0
lon =  45.0
alt = 100.0

x, y, z = t_geo2ecef.transform(lon, lat, alt, radians=False)
print(x, y, z)

