global A
figure
hold on
plot(A.t_plot(1:A.counter),A.psi_plot(1:A.counter)+A.psi_error(1:A.counter),'y')
plot(A.t_plot(1:A.counter),A.psi_plot(1:A.counter),'r')
plot(A.t_plot(1:A.counter),A.psi_ref_plot(1:A.counter),'b')

legend('measured response','actual response','set value')
xlabel('time (s)')
ylabel('psi (rad)')
title('psi vs. time')