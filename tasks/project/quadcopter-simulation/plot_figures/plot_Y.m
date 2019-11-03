global A
figure
hold on
plot(A.t_plot(1:A.counter),A.Y_plot(1:A.counter)+A.Y_error(1:A.counter),'y')
plot(A.t_plot(1:A.counter),A.Y_plot(1:A.counter),'r','linewidth',1)
plot(A.t_plot(1:A.counter),A.Y_ref_plot(1:A.counter),'b')
legend('measured response','actual response','set value')

xlabel('time (s)')
ylabel('Y (m)')
title('Y vs. time')