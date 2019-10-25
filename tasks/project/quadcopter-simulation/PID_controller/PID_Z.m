function PID_Z_NC
global A

%���ڸ��»�����
persistent ui;
persistent errork1;

  %��ʼ��
  if A.init==0
      ui    = 0; 
      errork1 = 0;
  end
 
  % ƫ��
  error = A.Z_des-A.Z_meas;
  
  % ����
  up = A.Z_KP * error;
  
  % ����
  ui = ui + A.Z_KI * A.Ts/2 * (error + errork1);
  
  % ΢��
  ud = A.Z_KD*A.Z_dot;
  
  % �������
  F = up + ui - ud;
  A.U1 = (A.m*A.g + F)/cos(A.phi_meas)/cos(A.theta_meas);
  
  % ����ƫ��
  errork1 = error;
  
end