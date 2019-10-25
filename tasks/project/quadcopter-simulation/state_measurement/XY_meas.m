function XY_meas
global A
% 测量当前值
A.X_meas = A.X+A.X_error(A.counter);     
A.Y_meas = A.Y+A.Y_error(A.counter);     
end