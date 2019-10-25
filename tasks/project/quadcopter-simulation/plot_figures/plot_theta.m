global A
figure
hold on
plot(A.t_plot(1:A.counter),A.theta_plot(1:A.counter)+A.theta_error(1:A.counter),'y')
plot(A.t_plot(1:A.counter),A.theta_plot(1:A.counter),'r')
plot(A.t_plot(1:A.counter),A.theta_ref_plot(1:A.counter),'b')

legend('measured response','actual response','set value')
xlabel('time (s)')
ylabel('theta (rad)')
title('theta vs. time')