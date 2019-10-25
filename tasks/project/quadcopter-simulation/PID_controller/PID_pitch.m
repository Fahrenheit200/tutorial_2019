function PID_pitch_NC
global A

% ���ڸ��»�����
  persistent uik1;
  persistent errork1;
  
  % ��ʼ��
  if A.init==0, 
      uik1    = 0; 
      errork1 = 0;
  end
 
  % ƫ��
  error = A.theta_des - A.theta_meas;

  % ����
  up = A.theta_KP * error;
  
  % ����
  ui = uik1 + A.theta_KI * A.Ts/2 * (error + errork1);
  
  % ΢��
  ud = A.theta_KD*A.q;
  
  
  % �������
  A.U3 = up + ui + ud;

  % ������ĸ���
  uik1    = ui; 
  errork1 = error;
  
end