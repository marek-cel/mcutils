pkg load quaternion
pkg load geometry

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

phi =  45;
tht =  45;
psi =  45;

m = rotz(psi) * ( roty(tht) * rotx(phi) );
m = transpose(m) % passive instead of active rotation

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

phi = -45;
tht =  45;
psi =  45;

m = rotz(psi) * ( roty(tht) * rotx(phi) );
m = transpose(m) % passive instead of active rotation

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

phi =  45;
tht = -45;
psi =  45;

m = rotz(psi) * ( roty(tht) * rotx(phi) );
m = transpose(m) % passive instead of active rotation

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

phi =  45;
tht =  45;
psi = -45;

m = rotz(psi) * ( roty(tht) * rotx(phi) );
m = transpose(m) % passive instead of active rotation
