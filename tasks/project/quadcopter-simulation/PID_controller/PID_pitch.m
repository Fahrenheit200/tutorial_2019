function PID_pitch_NC
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
  error = A.theta_des - A.theta_meas;

  % 比例
  up = A.theta_KP * error;
  
  % 积分
  ui = uik1 + A.theta_KI * A.Ts/2 * (error + errork1);
  
  % 微分
  ud = A.theta_KD*A.q;
  
  
  % 输出控制
  A.U3 = up + ui + ud;

  % 积分项的更新
  uik1    = ui; 
  errork1 = error;
  
end