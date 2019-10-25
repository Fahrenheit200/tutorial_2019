function Z_meas
global A
% 测量当前值
A.Z_meas = A.Z+A.Z_error(A.counter);     
end