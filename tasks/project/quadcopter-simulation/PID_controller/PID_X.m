global A

% 将对地的预设坐标转换为相对于机体坐标
A.X_des = A.X_des_EF*cos(A.psi_meas)+A.Y_des_EF*sin(A.psi_meas);    

% 将对地的当前坐标转换为相对于机体坐标系
A.X_BF = A.X_meas*cos(A.psi_meas)+A.Y_meas*sin(A.psi_meas);            
A.X_dot_BF = A.X_dot*cos(A.psi_meas)+A.Y_dot*sin(A.psi_meas);    

% PD控制
A.theta_des = A.X_KP*(A.X_des - A.X_BF) + A.X_KD*A.X_dot;

% 限制倾角不能超过45°
if(abs(A.theta_des) > 45*(pi/180))        
    A.theta_des = sign(A.theta_des)*45*pi/180;
end
