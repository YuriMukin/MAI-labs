model laba1extra
import Modelica.SIunits;

Modelica.SIunits.Angle phi(start = 1);
Modelica.SIunits.AngularVelocity omega(start = 0);
parameter Modelica.SIunits.Mass M = 2;
parameter Modelica.SIunits.Length L=3;
parameter Modelica.SIunits.Acceleration g = 9.8;
parameter Modelica.Mechanics.MultiBody.Frames.Orientation R1 = Modelica.Mechanics.MultiBody.Frames.axesRotations({1, 2, 3},{0,0,0},{0,0,0});
Modelica.Mechanics.MultiBody.Visualizers.Advanced.Shape rod(shapeType = "cylinder", length = L, width = L/50, height = L/50, lengthDirection = {sin(phi), -cos(phi), 0}, widthDirection = {0,0,1}, color = {255, 0, 0}, specularCoefficient = 0.5, R = R1, r = {0, 0, 0});
Modelica.Mechanics.MultiBody.Visualizers.Advanced.Shape sphere(shapeType = "sphere", length = L/3, width = L/3, height = L/3, lengthDirection = {sin(phi), -cos(phi), 0}, widthDirection = {0,0,1}, color = {255, 0, 0}, specularCoefficient = 0.5, R = R1, r = {L*sin(phi), -cos(phi)*L, 0});

equation

  der(phi) = omega;
  der(omega) = -M*g*L*sin(phi)/(M*L*L);

end laba1extra;
