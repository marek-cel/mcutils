pkg load geometry;

v0 = [ 1.0 2.0 3.0 ];

l0 = vectorNorm( v0 );
fprintf('l0= %f\n', l0);

v0_norm = normalizeVector(v0);
fprintf('v1_norm= %f %f %f\n', v0_norm(1),v0_norm(2),v0_norm(3));

v1 = [ 1.0 0.0 0.0 0.0 ];
v2 = [ 0.0 1.0 0.0 0.0 ];
v3 = [ 0.0 0.0 1.0 0.0 ];
v4 = [ 0.0 0.0 0.0 1.0 ];
v5 = [ 1.0 2.0 3.0 4.0 ];

d51 = dot( v5, v1 );
d52 = dot( v5, v2 );
d53 = dot( v5, v3 );
d54 = dot( v5, v4 );
d55 = dot( v5, v5 );

fprintf('d51= %f\n', d51);
fprintf('d52= %f\n', d52);
fprintf('d53= %f\n', d53);
fprintf('d54= %f\n', d54);
fprintf('d55= %f\n', d55);


v61 = [ 1.0 0.0 0.0 0.0 0.0 0.0 ];
v62 = [ 0.0 1.0 0.0 0.0 0.0 0.0 ];
v63 = [ 0.0 0.0 1.0 0.0 0.0 0.0 ];
v64 = [ 0.0 0.0 0.0 1.0 0.0 0.0 ];
v65 = [ 1.0 2.0 3.0 4.0 5.0 6.0 ];

d61 = dot( v65, v61 );
d62 = dot( v65, v62 );
d63 = dot( v65, v63 );
d64 = dot( v65, v64 );
d65 = dot( v65, v65 );

fprintf('\n');
fprintf('d61= %f\n', d61);
fprintf('d62= %f\n', d62);
fprintf('d63= %f\n', d63);
fprintf('d64= %f\n', d64);
fprintf('d65= %f\n', d65);
