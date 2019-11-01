function PID_Z_NC
global A

%用于更新积分项
persistent ui;
persistent errork1;

  %初始化
  if A.init==0
      ui    = 0; 
      errork1 = 0;
  end
 
  % 偏差
  error = A.Z_des-A.Z_meas;
  
  % 比例
  up = A.Z_KP * error;
  
  % 积分
  ui = ui + A.Z_KI * A.Ts/2 * (error + errork1);
  
  % 微分
  ud = A.Z_KD*A.Z_dot;
  
  % 输出控制
  F = up + ui - ud;
  A.U1 = (A.m*A.g + F)/cos(A.phi_meas)/cos(A.theta_meas);
  
  % 更新偏差
  errork1 = error;
  
end