global A

% ���Եص�Ԥ������ת��Ϊ����ڻ�������
A.X_des = A.X_des_EF*cos(A.psi_meas)+A.Y_des_EF*sin(A.psi_meas);    

% ���Եصĵ�ǰ����ת��Ϊ����ڻ�������ϵ
A.X_BF = A.X_meas*cos(A.psi_meas)+A.Y_meas*sin(A.psi_meas);            
A.X_dot_BF = A.X_dot*cos(A.psi_meas)+A.Y_dot*sin(A.psi_meas);    

% PD����
A.theta_des = A.X_KP*(A.X_des - A.X_BF) + A.X_KD*A.X_dot;

% ������ǲ��ܳ���45��
if(abs(A.theta_des) > 45*(pi/180))        
    A.theta_des = sign(A.theta_des)*45*pi/180;
end
