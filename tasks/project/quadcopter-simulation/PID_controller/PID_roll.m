function PID_roll_NC
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
  error = A.phi_des - A.phi_meas;

  % 比例
  up = A.phi_KP * error;
  
  % 积分
  ui = uik1 + A.phi_KI * A.Ts/2 * (error + errork1);
  
  % 微分
  ud = A.phi_KD*A.p;
  
  % 输出控制
  A.U2 = up + ui + ud;

  % 更新积分项
  uik1    = ui; 
  errork1 = error;