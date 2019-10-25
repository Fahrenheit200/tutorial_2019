function PID_heading_NC
global A

% 用于更新积分项
  persistent uik1;
  persistent errork1;
  
  % 初始化 
  if A.init==0, 
      uik1    = 0; 
      errork1 = 0;
  end
 
  % 偏差
 error = A.psi_des - A.psi_meas ;
  
  % 比例
  up = A.psi_KP * error;
  
  % 积分
  ui = uik1 + A.psi_KI * A.Ts/2 * (error + errork1);
  
  % 微分
  ud = A.psi_KD*A.r;
  
  
  % 输出控制
  A.U4 = up + ui + ud;

  % 更新积分项
  uik1    = ui; 
  errork1 = error;