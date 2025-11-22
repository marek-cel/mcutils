#!/usr/bin/env python3

################################################################################

import pyproj

################################################################################

t_geo2merc = pyproj.Transformer.from_crs(
    {"proj":'latlong', "ellps":'WGS84', "datum":'WGS84'},
    {"proj":'merc', "ellps":'WGS84', "datum":'WGS84'},
    )

t_merc2geo = pyproj.Transformer.from_crs(
    {"proj":'merc', "ellps":'WGS84', "datum":'WGS84'},
    {"proj":'latlong', "ellps":'WGS84', "datum":'WGS84'},
    )

################################################################################

nautical_mile = 1852.0
arc_deg = 60.0 * nautical_mile

arc_deg30  =  30.0 * arc_deg
arc_deg45  =  45.0 * arc_deg
arc_deg60  =  60.0 * arc_deg
arc_deg90  =  90.0 * arc_deg
arc_deg120 = 120.0 * arc_deg
arc_deg150 = 150.0 * arc_deg
arc_deg180 = 180.0 * arc_deg

################################################################################
print("\n CALCULATE LON,LAT \n")
################################################################################

x = 0.0
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################
print("\n CALCULATE LAT \n")
################################################################################

x = 0.0
y = arc_deg30

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = 0.0
y = arc_deg45

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = 0.0
y = arc_deg60

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = 0.0
y = arc_deg90

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = 0.0
y = -arc_deg30

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = 0.0
y = -arc_deg45

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = 0.0
y = -arc_deg60

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = 0.0
y = -arc_deg90

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################
print("\n CALCULATE LON \n")
################################################################################

x = arc_deg30
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = arc_deg45
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = arc_deg60
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = arc_deg90
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = arc_deg120
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = arc_deg150
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = arc_deg180
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = -arc_deg30
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = -arc_deg45
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = -arc_deg60
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = -arc_deg90
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = -arc_deg120
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = -arc_deg150
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################

x = -arc_deg180
y = 0.0

lon, lat = t_merc2geo.transform(x, y, radians=True)
print("x= ", x, " y= ", y, "\t", lon, lat)

################################################################################
print("\n CALCULATE X,Y \n")
################################################################################

lon = 0.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################
print("\n CALCULATE X \n")
################################################################################

lon = 30.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = 45.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = 60.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = 90.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = 120.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = 150.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = 180.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = -30.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = -45.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = -60.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = -90.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = -120.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = -150.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = -180.0
lat = 0.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################
print("\n CALCULATE Y \n")
################################################################################

lon = 0.0
lat = 30.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = 0.0
lat = 45.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = 0.0
lat = 60.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = 0.0
lat = 85.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = 0.0
lat = -30.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = 0.0
lat = -45.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = 0.0
lat = -60.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)

################################################################################

lon = 0.0
lat = -85.0

x, y = t_geo2merc.transform(lon, lat, radians=False)
print("lon= ", lon, " lat= ", lat, "\t", x, y)
