global A

% ��һ��3Dģ��
copter_model_3D

% ��������
A.g = 9.81;     
A.m = 1;      
A.Ts = .01;     
A.init = 0;     

A.b = 54.2E-6;    % ����ת����������С�ı���ϵ��
A.l = .24;        % �ɻ��İ뾶
A.d = 1.1E-6;     % ����ת����������С�ı���ϵ��

% ����ת������
A.Motors_limit = 500^2;         
A.Motors_lowerlimit = -1*((400)^2); 

% PID����
% -----------------------------%
% ������������ѣ���С����˳��� %
% ���Ǳ�������֣�����ٰ�΢�ּ� %
% �����񵴺�Ƶ������������Ҫ�Ŵ� %
% ����Ư���ƴ��壬����������С�� %
% ����ƫ��ظ���������ʱ�����½� %
% ���߲������ڳ�������ʱ���ټӳ� %
% ������Ƶ�ʿ죬�Ȱ�΢�ֽ����� %
% ���������������΢��ʱ��Ӧ�ӳ� %
% ����������������ǰ�ߺ��4��1   %
% һ�������������������������� %
% -----------------------------%
A.Z_KP = 30;                    
A.Z_KI = .5;                   
A.Z_KD = 7.6;  

A.X_KP = .09;          
A.X_KD = -.02;         

A.Y_KP = .09;          
A.Y_KD = -.02;         

A.phi_KP = 12;      
A.phi_KI = .02;     
A.phi_KD = -.9;    

A.theta_KP = 12;    
A.theta_KI = .02;     
A.theta_KD = -.9;   

A.psi_KP = 10;     
A.psi_KI = .15;     
A.psi_KD = -.9;     
  
%��ʼ��
% �Ե�����
A.X = 0;        
A.Y = 0;    
A.Z = 0;

% �Ի�������
A.X_BF = 0;        
A.Y_BF = 0;        
        
% �Ե��ٶ�
A.X_dot = 0;   
A.Y_dot = 0;   
A.Z_dot = 0;

% �Ի����ٶ�
A.X_dot_BF = 0;    
A.Y_dot_BF = 0;    

% �Ի�������ϵ�Ľ�����
A.p = 0;        % ��X
A.q = 0;        % ��Y
A.r = 0;        % ��Z

A.phi = 0;      % ������ pitch
A.theta = 0;    % ƫ���� yaw
A.psi = 0;      % ������ roll

% ת������
A.Ixx = 8.1E-3;     % ��X
A.Iyy = 8.1E-3;     % ��Y
A.Izz = 14.2E-3;    % ��Z
A.Jtp = 104E-6;     % ҶƬ��ת������

% ����Ť��
A.U1 = 0;       % ����
A.U2 = 0;       % ��X���Ť��
A.U3 = 0;       % ��Y���Ť��
A.U4 = 0;       % ��Z���Ť��

% �ĸ������ת��
A.O1 = 0;       % ǰ
A.O2 = 0;       % ��
A.O3 = 0;       % ��
A.O4 = 0;       % ��
A.O = 0;        % �ĸ������ת��֮��

% λ��Ŀ��ֵ
A.Z_des = 0;            
A.X_des_EF = 0;         % �Ե�X
A.Y_des_EF = 0;         % �Ե�Y
A.X_des = 0;            % �Ի���X
A.Y_des = 0;            % �Ի���Y

A.phi_des = 0;          
A.theta_des = 0;    
A.psi_des = 0;          

% ��������plot������                
A.Z_plot = zeros(1,60*10/A.Ts);      % Z��ʵ����Ӧ
A.Z_ref_plot = zeros(1,60*10/A.Ts);  % Z������ֵ

A.X_plot = zeros(1,60*10/A.Ts);      % X��ʵ����Ӧ
A.X_ref_plot = zeros(1,60*10/A.Ts);  % X������ֵ

A.Y_plot = zeros(1,60*10/A.Ts);      % Y��ʵ����Ӧ
A.Y_ref_plot = zeros(1,60*10/A.Ts);  % Y������ֵ

A.phi_plot = zeros(1,60*10/A.Ts);      % �����ǵ�ʵ����Ӧ
A.phi_ref_plot = zeros(1,60*10/A.Ts);  % �����ǵ�����ֵ

A.theta_plot = zeros(1,60*10/A.Ts);      % ƫ���ǵ�ʵ����Ӧ
A.theta_ref_plot = zeros(1,60*10/A.Ts);  % ƫ���ǵ�����ֵ

A.psi_plot = zeros(1,60*10/A.Ts);      % �����ǵ�ʵ����Ӧ
A.psi_ref_plot = zeros(1,60*10/A.Ts);  % �����ǵ�����ֵ

A.t_plot = [0:A.Ts:60*10-A.Ts];       % ʱ��
A.counter = 1;                        % ����ʱ��������±�

% ����ֵ
A.Z_meas = 0;
A.phi_meas = 0;
A.theta_meas = 0;
A.psi_meas = 0;

% ������̬�ֲ���λ��ƫ��
A.Z_error = randn(1,60*10/A.Ts)*.0;
A.phi_error = randn(1,60*10/A.Ts)*.0;
A.theta_error = randn(1,60*10/A.Ts)*.0;
A.psi_error = randn(1,60*10/A.Ts)*.0;
A.X_error = randn(1,60*10/A.Ts)*.0;
A.Y_error = randn(1,60*10/A.Ts)*.0;

% ŷ���ǵ�������ֵ
A.C_phi = cos(A.phi);
A.C_theta = cos(A.theta);
A.C_psi = cos(A.psi);

A.S_phi = sin(A.phi);
A.S_theta = sin(A.theta);
A.S_psi = sin(A.psi);

