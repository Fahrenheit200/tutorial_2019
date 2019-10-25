function PID_roll_NC
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
  error = A.phi_des - A.phi_meas;

  % ����
  up = A.phi_KP * error;
  
  % ����
  ui = uik1 + A.phi_KI * A.Ts/2 * (error + errork1);
  
  % ΢��
  ud = A.phi_KD*A.p;
  
  % �������
  A.U2 = up + ui + ud;

  % ���»�����
  uik1    = ui; 
  errork1 = error;