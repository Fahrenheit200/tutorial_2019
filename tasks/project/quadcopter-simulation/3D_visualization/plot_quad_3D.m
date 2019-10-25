global A
% ·É»úµÄ3DÏÔÊ¾
[A.X22,A.Y22,A.Z22]=rotateXYZ(A.Body1X,A.Body1Y,A.Body1Z,A.phi,A.theta,A.psi);
set(A.Body1,'xdata',A.X22+A.X,'ydata',A.Y22+A.Y,'zdata',A.Z22+A.Z)

[A.X22,A.Y22,A.Z22]=rotateXYZ(A.Body2X,A.Body2Y,A.Body2Z,A.phi,A.theta,A.psi);
set(A.Body2,'xdata',A.X22+A.X,'ydata',A.Y22+A.Y,'zdata',A.Z22+A.Z)

[A.X22,A.Y22,A.Z22]=rotateXYZ(A.RotorFX,A.RotorFY,A.RotorFZ,A.phi,A.theta,A.psi);
set(A.RotorF,'xdata',A.X22+A.X,'ydata',A.Y22+A.Y,'zdata',A.Z22+A.Z)

[A.X22,A.Y22,A.Z22]=rotateXYZ(A.RotorBX,A.RotorBY,A.RotorBZ,A.phi,A.theta,A.psi);
set(A.RotorB,'xdata',A.X22+A.X,'ydata',A.Y22+A.Y,'zdata',A.Z22+A.Z)

[A.X22,A.Y22,A.Z22]=rotateXYZ(A.RotorLX,A.RotorLY,A.RotorLZ,A.phi,A.theta,A.psi);
set(A.RotorL,'xdata',A.X22+A.X,'ydata',A.Y22+A.Y,'zdata',A.Z22+A.Z)

[A.X22,A.Y22,A.Z22]=rotateXYZ(A.RotorRX,A.RotorRY,A.RotorRZ,A.phi,A.theta,A.psi);
set(A.RotorR,'xdata',A.X22+A.X,'ydata',A.Y22+A.Y,'zdata',A.Z22+A.Z)