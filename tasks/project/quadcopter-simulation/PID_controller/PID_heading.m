function PID_heading_NC
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
 error = A.psi_des - A.psi_meas ;
  
  % ����
  up = A.psi_KP * error;
  
  % ����
  ui = uik1 + A.psi_KI * A.Ts/2 * (error + errork1);
  
  % ΢��
  ud = A.psi_KD*A.r;
  
  
  % �������
  A.U4 = up + ui + ud;

  % ���»�����
  uik1    = ui; 
  errork1 = error;