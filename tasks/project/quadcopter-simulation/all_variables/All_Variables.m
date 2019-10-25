global A

% 画一个3D模型
copter_model_3D

% 环境参数
A.g = 9.81;     
A.m = 1;      
A.Ts = .01;     
A.init = 0;     

A.b = 54.2E-6;    % 引擎转速与推力大小的比例系数
A.l = .24;        % 飞机的半径
A.d = 1.1E-6;     % 引擎转速与拉力大小的比例系数

% 引擎转速限制
A.Motors_limit = 500^2;         
A.Motors_lowerlimit = -1*((400)^2); 

% PID参数
% -----------------------------%
% 参数整定找最佳，从小到大顺序查 %
% 先是比例后积分，最后再把微分加 %
% 曲线振荡很频繁，比例度盘要放大 %
% 曲线漂浮绕大湾，比例度盘往小扳 %
% 曲线偏离回复慢，积分时间往下降 %
% 曲线波动周期长，积分时间再加长 %
% 曲线振荡频率快，先把微分降下来 %
% 动差大来波动慢。微分时间应加长 %
% 理想曲线两个波，前高后低4比1   %
% 一看二调多分析，调节质量不会低 %
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
  
%初始化
% 对地坐标
A.X = 0;        
A.Y = 0;    
A.Z = 0;

% 对机体坐标
A.X_BF = 0;        
A.Y_BF = 0;        
        
% 对地速度
A.X_dot = 0;   
A.Y_dot = 0;   
A.Z_dot = 0;

% 对机体速度
A.X_dot_BF = 0;    
A.Y_dot_BF = 0;    

% 对机体坐标系的角速率
A.p = 0;        % 绕X
A.q = 0;        % 绕Y
A.r = 0;        % 绕Z

A.phi = 0;      % 俯仰角 pitch
A.theta = 0;    % 偏航角 yaw
A.psi = 0;      % 翻滚角 roll

% 转动惯量
A.Ixx = 8.1E-3;     % 绕X
A.Iyy = 8.1E-3;     % 绕Y
A.Izz = 14.2E-3;    % 绕Z
A.Jtp = 104E-6;     % 叶片的转动惯量

% 力和扭矩
A.U1 = 0;       % 推力
A.U2 = 0;       % 绕X轴的扭矩
A.U3 = 0;       % 绕Y轴的扭矩
A.U4 = 0;       % 绕Z轴的扭矩

% 四个引擎的转速
A.O1 = 0;       % 前
A.O2 = 0;       % 右
A.O3 = 0;       % 后
A.O4 = 0;       % 左
A.O = 0;        % 四个引擎的转速之和

% 位姿目标值
A.Z_des = 0;            
A.X_des_EF = 0;         % 对地X
A.Y_des_EF = 0;         % 对地Y
A.X_des = 0;            % 对机体X
A.Y_des = 0;            % 对机体Y

A.phi_des = 0;          
A.theta_des = 0;    
A.psi_des = 0;          

% 储存用于plot的数据                
A.Z_plot = zeros(1,60*10/A.Ts);      % Z的实际响应
A.Z_ref_plot = zeros(1,60*10/A.Ts);  % Z的设置值

A.X_plot = zeros(1,60*10/A.Ts);      % X的实际响应
A.X_ref_plot = zeros(1,60*10/A.Ts);  % X的设置值

A.Y_plot = zeros(1,60*10/A.Ts);      % Y的实际响应
A.Y_ref_plot = zeros(1,60*10/A.Ts);  % Y的设置值

A.phi_plot = zeros(1,60*10/A.Ts);      % 俯仰角的实际响应
A.phi_ref_plot = zeros(1,60*10/A.Ts);  % 俯仰角的设置值

A.theta_plot = zeros(1,60*10/A.Ts);      % 偏航角的实际响应
A.theta_ref_plot = zeros(1,60*10/A.Ts);  % 偏航角的设置值

A.psi_plot = zeros(1,60*10/A.Ts);      % 翻滚角的实际响应
A.psi_ref_plot = zeros(1,60*10/A.Ts);  % 翻滚角的设置值

A.t_plot = [0:A.Ts:60*10-A.Ts];       % 时间
A.counter = 1;                        % 储存时间的数组下标

% 测量值
A.Z_meas = 0;
A.phi_meas = 0;
A.theta_meas = 0;
A.psi_meas = 0;

% 服从正态分布的位姿偏差
A.Z_error = randn(1,60*10/A.Ts)*.0;
A.phi_error = randn(1,60*10/A.Ts)*.0;
A.theta_error = randn(1,60*10/A.Ts)*.0;
A.psi_error = randn(1,60*10/A.Ts)*.0;
A.X_error = randn(1,60*10/A.Ts)*.0;
A.Y_error = randn(1,60*10/A.Ts)*.0;

% 欧拉角的正余弦值
A.C_phi = cos(A.phi);
A.C_theta = cos(A.theta);
A.C_psi = cos(A.psi);

A.S_phi = sin(A.phi);
A.S_theta = sin(A.theta);
A.S_psi = sin(A.psi);

