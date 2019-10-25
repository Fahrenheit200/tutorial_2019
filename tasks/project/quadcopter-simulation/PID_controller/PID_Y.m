global A

% 将对地的预设坐标转换为相对于机体坐标
A.Y_des = A.Y_des_EF*cos(A.psi_meas)-A.X_des_EF*sin(A.psi_meas);    

% 将对地的当前坐标转换为相对于机体坐标系
A.Y_BF = A.Y_meas*cos(A.psi_meas)-A.X_meas*sin(A.psi_meas);           
A.Y_dot_BF = A.Y_dot*cos(A.psi_meas)-A.X_dot*sin(A.psi_meas);    

% PD控制
A.phi_des = -1*(A.Y_KP*(A.Y_des - A.Y_BF) + A.Y_KD*A.Y_dot);

% 限制倾角不能超过45°
if(abs(A.phi_des) > 45*(pi/180))        % limiter
    A.phi_des = sign(A.phi_des)*45*(pi/180);
end
