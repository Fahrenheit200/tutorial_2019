global A

% ���Եص�Ԥ������ת��Ϊ����ڻ�������
A.Y_des = A.Y_des_EF*cos(A.psi_meas)-A.X_des_EF*sin(A.psi_meas);    

% ���Եصĵ�ǰ����ת��Ϊ����ڻ�������ϵ
A.Y_BF = A.Y_meas*cos(A.psi_meas)-A.X_meas*sin(A.psi_meas);           
A.Y_dot_BF = A.Y_dot*cos(A.psi_meas)-A.X_dot*sin(A.psi_meas);    

% PD����
A.phi_des = -1*(A.Y_KP*(A.Y_des - A.Y_BF) + A.Y_KD*A.Y_dot);

% ������ǲ��ܳ���45��
if(abs(A.phi_des) > 45*(pi/180))        % limiter
    A.phi_des = sign(A.phi_des)*45*(pi/180);
end
