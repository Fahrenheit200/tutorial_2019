function Forces
global A
%��������Ť��

% ����
A.U1 = A.b*(sign(A.O1)*A.O1^2 + sign(A.O2)*A.O2^2 + sign(A.O3)*A.O3^2 + sign(A.O4)*A.O4^2);
  A.U1_plot(A.counter) = A.U1;
  
% ��X���Ť��
A.U2 = A.b*A.l*(sign(A.O4)*A.O4^2 - sign(A.O2)*A.O2^2);
  A.U2_plot(A.counter) = A.U2;
  
% ��Y���Ť��
A.U3 = A.b*A.l*(sign(A.O3)*A.O3^2 - sign(A.O1)*A.O1^2);
  A.U3_plot(A.counter) = A.U3;
  
% ��Z���Ť��
A.U4 = A.d*(sign(A.O2)*A.O2^2 + sign(A.O4)*A.O4^2 - sign(A.O1)*A.O1^2 - sign(A.O3)*A.O3^2);
  A.U4_plot(A.counter) = A.U4;

% ����ת��֮��
A.O = (-A.O1 + A.O2 - A.O3 + A.O4);
  A.O_plot(A.counter) = A.O;


end