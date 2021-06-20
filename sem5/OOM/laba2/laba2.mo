package laba2
  model func1
    Real x(start = 10);
    Real v(start = 0);
    Real F;
    parameter Real K = 10;
    parameter Real k1 = 2;
    parameter Real k2 = 1;
    parameter Real k3 = 4;
    parameter Real k4 = 5;
  equation
    if x < 0.00001 then
      F = -K;
    elseif x > 0.00001 then
      F = K;
    else
      F = k3 * sin(k4 * time);
    end if;
    der(v) = (-F) - k2 * x + k3 * sin(k4 * time);
    der(x) = v;
  end func1;

  model func2
    Real x(start = 10);
    Real v(start = 0);
    Real F;
    Real flag(start = 0);
    parameter Real K = 10;
    parameter Real k1 = 2;
    parameter Real k2 = 1;
    parameter Real k3 = 4;
    parameter Real k4 = 5;
    parameter Real a = 2;
  equation
    if flag < 0.5 then
      if x < a then
        flag = 0;
        F = -K;
      else
        flag = 1;
        F = K;
      end if;
    else
      if x > (-a) then
        flag = 1;
        F = K;
      else
        flag = 0;
        F = -K;
      end if;
    end if;
    der(v) = (-F) - k2 * x + k3 * sin(k4 * time);
    der(x) = v;
    annotation(
      DymolaStoredErrors(thetext = "model func2

  Real x(start = 10);
  Real v(start = 0);
  Real F;

  parameter Real K = 10;
  parameter Real k1 = 2;
  parameter Real k2 = 1;
  parameter Real k3 = 4;
  parameter Real k4 = 5;
  parameter Real a = 2;
  parameter Real b = 4;

equation 
  if (x<-b)
    F = -K;
  elseif (x>-b and x<-a and ) then
    

der(v) = -F - k2*x+k3*sin(k4*time);
der(x) = v;

end func2;
      "));
  end func2;

  model func3
  Real x(start=10);
  Real v(start=0);
  Real F;
  Real flag(start=0);
  
  parameter Real K = 5;
  parameter Real k2=2;
  parameter Real k3=20;
  parameter Real k4=1;
  parameter Real a=4;
  parameter Real b=1;
  equation
  
  if flag<0.5 then
  
     if x<-b then
       F=-K;
       flag=0;
     else
       flag=1;
       F=0;
     end if;
  else
  if flag>0.5 and flag<1.5 then
     if (x>-a and x<a) then
       F=0;
       flag=1;
     else
     if (x>a) then
       F=K;
       flag=2;
    else
       F=-K;
       flag=0;
     end if;
  end if;
  else
     if (x>b) then
       F=K;
       flag=2;
     else
       F=0;
       flag=1;
     end if;
  end if;
  end if;
   der(v)=-F-k2*x+k3*sin(k4*time);
   der(x)=v;
  end func3;

  model func4
    Real x(start = 5);
    Real v(start = 1);
    Real F;
    parameter Real K = 6;
    parameter Real k2 = 3;
    parameter Real k3 = 4;
    parameter Real k4 = 5;
    parameter Real a = 2;
    parameter Real b = 3;
    parameter Real d = 5;
  
  equation
    if x < (-d) then
      F = -K;
    elseif x < (-a) then
      F = (K - b) / (d - a) * (x + a) - b;
    elseif x < a then
      F = 0;
    elseif x < d then
      F = (K - b) / (d - a) * (x - a) + b;
    else
      F = K;
    end if;
    der(x) = v;
    der(v) = (-F) - k2 * x + k3 * sin(k4 * time);
    
  end func4;
  annotation(
    uses(Modelica(version = "3.2")));
end laba2;
