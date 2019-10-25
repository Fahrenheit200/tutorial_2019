function IMU_meas
% ≤‚¡ø≈∑¿≠Ω«
global A

A.phi_meas = A.phi+A.phi_error(A.counter);     
A.theta_meas = A.theta+A.theta_error(A.counter);     
A.psi_meas = A.psi+A.psi_error(A.counter);     

end