function Z_meas
global A
% ������ǰֵ
A.Z_meas = A.Z+A.Z_error(A.counter);     
end