function quadmodel
global A
%�ɻ�������ģ�͡����У��߼��ٶȺ����ٶ�����ڵ��棬�Ǽ��ٶȺͽ��ٶ�����ڻ���

% ���ٶȺͽǼ��ٶ�
A.X_ddot = (sin(A.psi)*sin(A.phi) + cos(A.psi)*sin(A.theta)*cos(A.phi))*A.U1/A.m;
A.Y_ddot = (-cos(A.psi)*sin(A.phi) + sin(A.psi)*sin(A.theta)*cos(A.phi))*A.U1/A.m;
A.Z_ddot = -A.g + (cos(A.theta)*cos(A.phi))*A.U1/A.m;

A.p_dot = ((A.Iyy - A.Izz)*A.q*A.r -A.Jtp*A.q*A.O + A.U2)/A.Ixx;
A.q_dot = ((A.Izz - A.Ixx)*A.p*A.r +A.Jtp*A.p*A.O + A.U3)/A.Iyy;
A.r_dot = ((A.Ixx - A.Iyy)*A.p*A.q + A.U4)/A.Izz;

A.phi_dot   = A.p + sin(A.phi)*tan(A.theta)*A.q + cos(A.phi)*tan(A.theta)*A.r;
A.theta_dot = cos(A.phi)*A.q - sin(A.phi)*A.r;
A.psi_dot   = sin(A.phi)/cos(A.theta)*A.q + cos(A.phi)/cos(A.theta)*A.r;

% �����˿�����Ħ����
A.X_ddot = A.X_ddot - A.X_dot*1.2;
A.Y_ddot = A.Y_ddot - A.Y_dot*1.2;

% �������������ٶȺ�����
A.Z_dot = A.Z_ddot*A.Ts + A.Z_dot;
A.Z = A.Z_dot*A.Ts + A.Z;

A.X_dot = A.X_ddot*A.Ts + A.X_dot;
A.X = A.X_dot*A.Ts + A.X;

A.Y_dot = A.Y_ddot*A.Ts + A.Y_dot;
A.Y = A.Y_dot*A.Ts + A.Y;

% ���������
A.p = A.p_dot*A.Ts+A.p;
A.q = A.q_dot*A.Ts+A.q;
A.r = A.r_dot*A.Ts+A.r;

% ������̬
A.phi = A.phi_dot*A.Ts+A.phi;
A.theta = A.theta_dot*A.Ts+A.theta;
A.psi = A.psi_dot*A.Ts+A.psi;

% ����plot��ֵ
A.Z_plot(A.counter) = A.Z;
A.Z_ref_plot(A.counter) = A.Z_des;

A.X_plot(A.counter) = A.X;
A.X_ref_plot(A.counter) = A.X_des;

A.Y_plot(A.counter) = A.Y;
A.Y_ref_plot(A.counter) = A.Y_des;

A.phi_plot(A.counter) = A.phi;
A.phi_ref_plot(A.counter) = A.phi_des;

A.theta_plot(A.counter) = A.theta;
A.theta_ref_plot(A.counter) = A.theta_des;

A.psi_plot(A.counter) = A.psi;
A.psi_ref_plot(A.counter) = A.psi_des;

A.counter = A.counter + 1;
end