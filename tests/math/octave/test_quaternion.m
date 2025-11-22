pkg load geometry
pkg load linear-algebra
pkg load quaternion

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% assigning value to the quaternion
q1 = quaternion( 1.0, 2.0, 3.0, 4.0 );
printf('q1 assigning value\n');
disp(q1.w),disp(q1.x),disp(q1.y),disp(q1.z);
fprintf(1, '\n');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% quaternion from angles (yaw,pitch,roll)

x = deg2rad( 30 ); 
y = deg2rad( 45 );  
z = deg2rad( 60 ); 
mx = createRotationOx( x ); 
my = createRotationOy( y );  
mz = createRotationOz( z );
m44 = mz*my*mx;
m33 = [m44(1,1),m44(1,2),m44(1,3);...
       m44(2,1),m44(2,2),m44(2,3);...
       m44(3,1),m44(3,2),m44(3,3)];
q2 = rotm2q( (m33) );
printf('q2 rotm2q\n');
disp(q2.w),disp(q2.x),disp(q2.y),disp(q2.z);
fprintf(1, '\n');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% quaternion from axis and angle

v111 = [1.0 1.0 1.0];
v111n = normalizeVector(v111);

q31 = rot2q([1 0 0], pi/4);
printf('q31 rot2q\n');
disp(q31.w),disp(q31.x),disp(q31.y),disp(q31.z);
fprintf(1, '\n');

q32 = rot2q([0 1 0], pi/4);
printf('q32 rot2q\n');
disp(q32.w),disp(q32.x),disp(q32.y),disp(q32.z);
fprintf(1, '\n');

q33 = rot2q([0 0 1], pi/4);
printf('q33 rot2q\n');
disp(q33.w),disp(q33.x),disp(q33.y),disp(q33.z);
fprintf(1, '\n');

q34 = rot2q(v111n, pi/4);
printf('q34 rot2q\n');
disp(q34.w),disp(q34.x),disp(q34.y),disp(q34.z);
fprintf(1, '\n');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% conjugate of a quaternion
% The conjugate of a quaternion is formed by negating each of the non-real parts.
q4 = conj(q1);
printf('q4 conjugate\n');
disp(q4.w),disp(q4.x),disp(q4.y),disp(q4.z);
fprintf(1, '\n');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% inverse of quaternion
q5 = inv(q34);
printf('q6 inverse\n');
disp(q5.w),disp(q5.x),disp(q5.y),disp(q5.z);
fprintf(1, '\n');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% normalize
q6 = quaternion( 1.0, 2.0, 3.0, 4.0 );
q6_unit = unit(q6);
printf('q6 unit\n');
disp(q6_unit.w),disp(q6_unit.x),disp(q6_unit.y),disp(q6_unit.z);
fprintf(1, '\n');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Norm of a quaternion. (length)
q71 = quaternion( 1.0, 1.0, 1.0, 1.0 );
q72 = quaternion( 0.5, 0.5, 0.5, 0.5 );
q71_norm = norm(q71);
q72_norm = norm(q72);
printf('q7x norm\n');
disp(q71_norm),disp(q72_norm);
fprintf(1, '\n');

% length^2
printf('q7x length^2\n');
q71_norm2 = q71_norm * q71_norm;
q72_norm2 = q72_norm * q72_norm;
disp(q71_norm2),disp(q72_norm2);
fprintf(1, '\n');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% quaternion derivative (passive convention)
ang = pi/4;
omega_b = [ 1.0; 2.0; 3.0 ];
q8 = rot2q( v111n, ang );
mf = rotv( v111n, ang );
mi = inv(mf);
omega_i = mi * omega_b;
omega = [omega_i(1,1) omega_i(2,1) omega_i(3,1)];
q9 = diff(q8, omega);
printf('q9 derivative\n');
disp(q9.w),disp(q9.x),disp(q9.y),disp(q9.z);
fprintf(1, '\n');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% multiplication
v1 = [1.0, 0.0, 0.0];
v2 = [0.0, 1.0, 0.0];
a1 = pi/2;
a2 = pi/4;
q10a = rot2q( v1, a1 );
q10b = rot2q( v2, a2 );
q10 = q10a * q10b;
printf('q10 multiplication\n');
disp(q10.w),disp(q10.x),disp(q10.y),disp(q10.z);
fprintf(1, '\n');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
