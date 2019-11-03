function Forces
global A
%计算力和扭矩

% 推力
A.U1 = A.b*(sign(A.O1)*A.O1^2 + sign(A.O2)*A.O2^2 + sign(A.O3)*A.O3^2 + sign(A.O4)*A.O4^2);
  A.U1_plot(A.counter) = A.U1;
  
% 绕X轴的扭矩
A.U2 = A.b*A.l*(sign(A.O4)*A.O4^2 - sign(A.O2)*A.O2^2);
  A.U2_plot(A.counter) = A.U2;
  
% 绕Y轴的扭矩
A.U3 = A.b*A.l*(sign(A.O3)*A.O3^2 - sign(A.O1)*A.O1^2);
  A.U3_plot(A.counter) = A.U3;
  
% 绕Z轴的扭矩
A.U4 = A.d*(sign(A.O2)*A.O2^2 + sign(A.O4)*A.O4^2 - sign(A.O1)*A.O1^2 - sign(A.O3)*A.O3^2);
  A.U4_plot(A.counter) = A.U4;

% 引擎转速之和
A.O = (-A.O1 + A.O2 - A.O3 + A.O4);
  A.O_plot(A.counter) = A.O;


end