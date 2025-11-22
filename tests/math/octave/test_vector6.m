pkg load geometry;

v0 = [ 1.0 2.0 3.0 4.0 5.0 6.0 ];
v1 = [ 2.0 3.0 4.0 5.0 6.0 7.0 ];

v0_norm = normalizeVector(v0);
v1_norm = normalizeVector(v1);
fprintf('v0_norm= %f %f %f %f %f %f\n', v0_norm(1),v0_norm(2),v0_norm(3),v0_norm(4),v0_norm(5),v0_norm(6));
fprintf('v1_norm= %f %f %f %f %f %f\n', v1_norm(1),v1_norm(2),v1_norm(3),v1_norm(4),v1_norm(5),v1_norm(6));

