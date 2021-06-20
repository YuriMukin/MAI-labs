model laba1

Real x[5];
Real y[5];
initial equation
  for i in 1:5 loop
    x[i] = 2-(2/5)*(i-1);
    y[i] = 0;
  end for;

equation

  for i in 1:5 loop
    der(x[i]) = -5*y[i] - (3/2)*x[i];
    der(y[i]) = 7*x[i];
  end for;

end laba1;
